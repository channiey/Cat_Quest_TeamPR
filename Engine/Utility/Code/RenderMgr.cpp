#include "..\..\Header\RenderMgr.h"

IMPLEMENT_SINGLETON(CRenderMgr)

CRenderMgr::CRenderMgr()
{

}

CRenderMgr::~CRenderMgr()
{
	Free();
}

void CRenderMgr::Add_RenderGroup(RENDERID eType, CGameObject * pGameObject)
{
	if (RENDER_END <= eType || nullptr == pGameObject)
		return;

	m_RenderGroup[eType].push_back(pGameObject);

	pGameObject->AddRef(); // 디바이스가 복사되었으므로 레퍼런스카운트를 증가시킨다.
}

void CRenderMgr::Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev)
{
	// 렌더 우선 순위에 따라 각 렌더 함수를 호출한다.
	Render_Priority(pGraphicDev);
	Render_Nonalpha(pGraphicDev);
	Render_Alpha(pGraphicDev);
	Render_UI(pGraphicDev);

	// 렌더 그룹을 비운다.
	Clear_RenderGroup();
}

void CRenderMgr::Clear_RenderGroup()
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{
		for_each(m_RenderGroup[i].begin(), m_RenderGroup[i].end(), CDeleteObj()); // 삭제가 아니라 추가 때 올렸던 레퍼런스 카운트 내리기
		m_RenderGroup[i].clear();
	}
}

void CRenderMgr::Render_Priority(LPDIRECT3DDEVICE9& pGraphicDev)
{
	for (auto iter : m_RenderGroup[RENDER_PRIORITY])
		iter->Render_Object();
}

void CRenderMgr::Render_Nonalpha(LPDIRECT3DDEVICE9& pGraphicDev)
{
	for (auto iter : m_RenderGroup[RENDER_NONALPHA])
		iter->Render_Object();
}

void CRenderMgr::Render_Alpha(LPDIRECT3DDEVICE9& pGraphicDev)
{
	// 알파소팅 강사님 코드 참고

	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE); // z 버퍼 자동 정렬 해제 (알파 소팅 위해서)
	//pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // 컬링도

	m_RenderGroup[RENDER_ALPHA].sort([](CGameObject* pDst, CGameObject* pSrc) { return pDst->Get_ViewZ() > pSrc->Get_ViewZ(); });

	for (auto iter : m_RenderGroup[RENDER_ALPHA])
		iter->Render_Object();

	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE); // 다시 z 버퍼 자동정렬 켠다.

	//pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); // 컬링도


}

void CRenderMgr::Render_UI(LPDIRECT3DDEVICE9& pGraphicDev)
{
	D3DVIEWPORT9 m_BackupViewPort;
	pGraphicDev->GetViewport(&m_BackupViewPort); // 현재 뷰 포트 백업

	// UI용 새로운 뷰 포트 생성 및 적용
	D3DVIEWPORT9 UiViewPort;
	UiViewPort.X = 0;
	UiViewPort.Y = 0;
	UiViewPort.Width = WINCX;
	UiViewPort.Height = WINCY;
	UiViewPort.MinZ = -1;
	UiViewPort.MaxZ = 1;
	pGraphicDev->SetViewport(&UiViewPort);

	_matrix matView;
	pGraphicDev->SetTransform(D3DTS_VIEW, D3DXMatrixIdentity(&matView)); // 항등행렬로 적용된 뷰 행렬 초기화.

	_matrix    m_matProj;

	D3DXMatrixOrthoOffCenterLH(&m_matProj, 0, WINCX, 0, WINCY, -1.f, 1.f);
	
	pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);   // 직교투영 행렬 적용.


	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);    // Z버퍼 OFF
	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // 알파렌더링 ON

	pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	for (auto iter : m_RenderGroup[RENDER_UI])
	{
		if(iter->Get_Type() == )
	}
		iter->Render_Object();


	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE); // 알파렌더링 OFF
	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);      // Z버퍼 ON




	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DXToRadian(60.f), (_float)WINCX / WINCY, 0.1f, 1000.f);

	pGraphicDev->SetViewport(&m_BackupViewPort);                // UI 전체 출력 후 백업해둔 이전 뷰포트로 되돌림.
	pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);    // UI 전체 출력 후 다시 원근투영 행렬 적용.

	for (auto iter : m_RenderGroup[RENDER_UI])
		iter->Render_Object();
}

void CRenderMgr::Free()
{
	Clear_RenderGroup();
}
