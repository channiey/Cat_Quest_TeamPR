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

	pGameObject->AddRef(); // ����̽��� ����Ǿ����Ƿ� ���۷���ī��Ʈ�� ������Ų��.
}

void CRenderMgr::Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev)
{
	// ���� �켱 ������ ���� �� ���� �Լ��� ȣ���Ѵ�.
	Render_Priority(pGraphicDev);
	Render_Nonalpha(pGraphicDev);
	Render_Alpha(pGraphicDev);
	Render_UI(pGraphicDev);

	// ���� �׷��� ����.
	Clear_RenderGroup();
}

void CRenderMgr::Clear_RenderGroup()
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{
		for_each(m_RenderGroup[i].begin(), m_RenderGroup[i].end(), CDeleteObj()); // ������ �ƴ϶� �߰� �� �÷ȴ� ���۷��� ī��Ʈ ������
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
	// ���ļ��� ����� �ڵ� ����

	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE); // z ���� �ڵ� ���� ���� (���� ���� ���ؼ�)
	//pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // �ø���

	m_RenderGroup[RENDER_ALPHA].sort([](CGameObject* pDst, CGameObject* pSrc) { return pDst->Get_ViewZ() > pSrc->Get_ViewZ(); });

	for (auto iter : m_RenderGroup[RENDER_ALPHA])
		iter->Render_Object();

	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE); // �ٽ� z ���� �ڵ����� �Ҵ�.

	//pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); // �ø���


}

void CRenderMgr::Render_UI(LPDIRECT3DDEVICE9& pGraphicDev)
{
	D3DVIEWPORT9 m_BackupViewPort;
	pGraphicDev->GetViewport(&m_BackupViewPort); // ���� �� ��Ʈ ���

	// UI�� ���ο� �� ��Ʈ ���� �� ����
	D3DVIEWPORT9 UiViewPort;
	UiViewPort.X = 0;
	UiViewPort.Y = 0;
	UiViewPort.Width = WINCX;
	UiViewPort.Height = WINCY;
	UiViewPort.MinZ = -1;
	UiViewPort.MaxZ = 1;
	pGraphicDev->SetViewport(&UiViewPort);

	_matrix matView;
	pGraphicDev->SetTransform(D3DTS_VIEW, D3DXMatrixIdentity(&matView)); // �׵���ķ� ����� �� ��� �ʱ�ȭ.

	_matrix    m_matProj;

	D3DXMatrixOrthoOffCenterLH(&m_matProj, 0, WINCX, 0, WINCY, -1.f, 1.f);
	
	pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);   // �������� ��� ����.


	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);    // Z���� OFF
	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // ���ķ����� ON

	pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	for (auto iter : m_RenderGroup[RENDER_UI])
	{
		if(iter->Get_Type() == )
	}
		iter->Render_Object();


	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE); // ���ķ����� OFF
	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);      // Z���� ON




	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DXToRadian(60.f), (_float)WINCX / WINCY, 0.1f, 1000.f);

	pGraphicDev->SetViewport(&m_BackupViewPort);                // UI ��ü ��� �� ����ص� ���� ����Ʈ�� �ǵ���.
	pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);    // UI ��ü ��� �� �ٽ� �������� ��� ����.

	for (auto iter : m_RenderGroup[RENDER_UI])
		iter->Render_Object();
}

void CRenderMgr::Free()
{
	Clear_RenderGroup();
}
