#include "..\..\Header\Camera.h"

#include "GameObject.h"
#include "Transform.h"

CCamera::CCamera()
	: m_pLookAt(nullptr)
	, m_pFollow(nullptr)
	, m_eProjectID(PERSPECTIVE)
	, m_fSpeedZoom(100.f)
	, m_fDistance(0.f)
	, m_pHwnd(nullptr)
{
	ZeroMemory(&m_tVspace, sizeof(VIEWSPACE));
	ZeroMemory(&m_tProj, sizeof(PROJECTION));
	ZeroMemory(&m_tVport, sizeof(D3DVIEWPORT9));
	ZeroMemory(&m_matBillboardX, sizeof(_matrix));
	ZeroMemory(&m_matWorld, sizeof(_matrix));
	ZeroMemory(&m_matProj, sizeof(_matrix));
	ZeroMemory(&m_matView, sizeof(_matrix));

}

CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphicDev, HWND* _pHwnd)
	: CComponent(pGraphicDev, COMPONENT_TYPE::CAMERA)
	, m_pLookAt(nullptr)
	, m_pFollow(nullptr)
	, m_eProjectID(PERSPECTIVE)
	, m_fSpeedZoom(100.f)
	, m_fDistance(10.f)
	, m_pHwnd(_pHwnd)
{
	ZeroMemory(&m_tVspace, sizeof(VIEWSPACE));
	ZeroMemory(&m_tProj, sizeof(PROJECTION));
	ZeroMemory(&m_tVport, sizeof(D3DVIEWPORT9));
	ZeroMemory(&m_matBillboardX, sizeof(_matrix));
	ZeroMemory(&m_matWorld, sizeof(_matrix));
	ZeroMemory(&m_matProj, sizeof(_matrix));
	ZeroMemory(&m_matView, sizeof(_matrix));
}

CCamera::CCamera(const CCamera & rhs, CGameObject* _pOwnerObject)
	: CComponent(rhs, _pOwnerObject)
	, m_pLookAt(nullptr)
	, m_pFollow(nullptr)
	, m_eProjectID(rhs.m_eProjectID)
	, m_fSpeedZoom(rhs.m_fSpeedZoom)
	, m_tVspace(rhs.m_tVspace)
	, m_tProj(rhs.m_tProj)
	, m_tVport(rhs.m_tVport)
	, m_fDistance(rhs.m_fDistance)
	, m_pHwnd(rhs.m_pHwnd)
{
}

CCamera::~CCamera()
{
}

HRESULT CCamera::Ready_Camera()
{
	NULL_CHECK_RETURN(m_pHwnd, E_FAIL);

	RECT rc;
	GetClientRect(*m_pHwnd, &rc);

	// View Space
	m_tVspace.Eye		= vec3.zero;
	m_tVspace.LookAt	= vec3.forward;
	m_tVspace.Up		= vec3.up;

	// Projection
	m_tProj.FOV			= D3DXToRadian(60.f);
	m_tProj.Aspect		= (float)rc.right / (float)rc.bottom;
	m_tProj.Near		= 0.1f;
	m_tProj.Far			= 1000.0f;

	// View Port
	m_tVport.X			= 0;
	m_tVport.Y			= 0;
	m_tVport.Width		= (rc.right - rc.left);
	m_tVport.Height		= (rc.bottom - rc.top);
	m_tVport.MinZ		= 0.f; // Default
	m_tVport.MaxZ		= 1.f; // Default

	return S_OK;
}

_int CCamera::Update_Component(const _float & fTimeDelta)
{
	return 0;
}

HRESULT CCamera::Set_ViewSpace()
{
	// 뷰스페이스에 대한 데이터 m_tVspace는 클라에서 구현한 개별 카메라에서 세팅한다. (컴포넌트의 필드는 퍼블릭이다.)
	
	NULL_CHECK_RETURN(m_pGraphicDev, E_FAIL);

	D3DXMatrixIdentity(&m_matView);
	
	m_pGraphicDev->SetTransform(D3DTS_VIEW,
		D3DXMatrixLookAtLH(&m_matView, &m_tVspace.Eye, &m_tVspace.LookAt, &m_tVspace.Up));


	// 여러 곳에서 카메라의 월드행렬을 사용하기 위해 세팅
	D3DXMatrixInverse(&m_matWorld, NULL, &m_matView);

	// 뷰스페이스 설정 때 빌보드 행렬을 세팅해둔다 (셋트랜스폼 최소화)
	D3DXMatrixIdentity(&m_matBillboardX);

	m_matBillboardX._22 = m_matView._22;
	m_matBillboardX._23 = m_matView._23;
	m_matBillboardX._32 = m_matView._32;
	m_matBillboardX._33 = m_matView._33;

	D3DXMatrixInverse(&m_matBillboardX, NULL, &m_matBillboardX);

	return S_OK;
}

HRESULT CCamera::Set_Projection()
{
	NULL_CHECK_RETURN(m_pGraphicDev, E_FAIL);
	NULL_CHECK_RETURN(m_pHwnd, E_FAIL);

	RECT rc{};
	GetClientRect(*m_pHwnd, &rc);

	D3DXMatrixIdentity(&m_matProj);

	if (PERSPECTIVE == m_eProjectID)
	{
		m_pGraphicDev->SetTransform(D3DTS_PROJECTION, 
			D3DXMatrixPerspectiveFovLH(&m_matProj, m_tProj.FOV, m_tProj.Aspect, m_tProj.Near, m_tProj.Far));
	}
	else if (ORTHOGRAPHIC == m_eProjectID)
	{
		/*m_pGraphicDev->SetTransform(D3DTS_PROJECTION, 
			D3DXMatrixPerspectiveFovLH(&matProj, m_tProj.FOV, m_tProj.Aspect, m_tProj.Near, m_tProj.Far));*/
	}
	return S_OK;
}

HRESULT CCamera::Set_Viewport()
{
	NULL_CHECK_RETURN(m_pGraphicDev, E_FAIL);
	NULL_CHECK_RETURN(m_pHwnd, E_FAIL);

	RECT rc{};
	GetClientRect(*m_pHwnd, &rc);

	m_pGraphicDev->SetViewport(&m_tVport);

	return S_OK;
}

CCamera * CCamera::Create(LPDIRECT3DDEVICE9 pGraphicDev, HWND* const _pHwnd)
{
	CCamera*		pInstance = new CCamera(pGraphicDev, _pHwnd);

	if (FAILED(pInstance->Ready_Camera()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Camera Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent * CCamera::Clone(CGameObject* _pOwnerObject)
{
	return new CCamera(*this, _pOwnerObject);
}

void CCamera::Free()
{
	CComponent::Free();
}
