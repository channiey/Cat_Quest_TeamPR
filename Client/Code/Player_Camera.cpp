#include "stdafx.h"
#include "..\Header\Player_Camera.h"

#include "Export_Function.h"

CPlayer_Camera::CPlayer_Camera(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CCameraObject(pGraphicDev)
{

}
CPlayer_Camera::CPlayer_Camera(const CPlayer_Camera& rhs)
	: Engine::CCameraObject(rhs)
{

}
CPlayer_Camera::~CPlayer_Camera()
{
}

HRESULT CPlayer_Camera::Ready_Object(void)
{
	CCameraObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_fDefaultHeight	= 80.f;
	m_fNearZoom			= 20.f;
	m_fFarZoom			= 60.f;
	m_pCameraCom->m_fDistance = m_fNearZoom;

	m_pTransformCom->Set_Pos(_vec3{ 0.f, m_fDefaultHeight, -m_pCameraCom->m_fDistance });
	m_pCameraCom->m_fSpeedZoom = 100.f;

	return S_OK;
}

Engine::_int CPlayer_Camera::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Move(fTimeDelta);

	return iExit;
}

void CPlayer_Camera::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();
}

HRESULT CPlayer_Camera::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	return S_OK;
}

void CPlayer_Camera::Move(const _float & fTimeDelta)
{
	_long dwMouse = 0;

	// 01. Zoom Setting
	if (dwMouse = CInputDev::GetInstance()->Get_DIMouseMove(DIMS_Z))
	{
		if (0 < dwMouse)
			m_pCameraCom->m_fDistance = m_fNearZoom;
		else
			m_pCameraCom->m_fDistance = m_fFarZoom;
	}

	// 02. Update View Space Data
	NULL_CHECK(m_pCameraCom->m_pLookAt);
	NULL_CHECK(m_pCameraCom->m_pFollow);
	_vec3 vFollowPos = m_pCameraCom->m_pFollow->Get_Transform()->Get_Info(INFO_POS);

	// 03. Ÿ�ٱ����� ���Ͻ��� ���� ī�޶��� ���̰��� ���Ѵ�.
	_vec3 vDir1 = m_pTransformCom->Get_Info(INFO_POS) - m_pCameraCom->m_pLookAt->Get_Transform()->Get_Info(INFO_POS);
	_vec3 vDir2 = { vDir1.x, 0.f, vDir1.z };
	D3DXVec3Normalize(&vDir1, &vDir1);
	D3DXVec3Normalize(&vDir2, &vDir2);
	_float fTheta = D3DXVec3Dot(&vDir1, &vDir2);
	_float fY = sinf(fTheta) * m_pCameraCom->m_fDistance * 2.f;
	
	m_pTransformCom->Set_Pos(_vec3{ vFollowPos.x,
									fY,
									vFollowPos.z - m_pCameraCom->m_fDistance });

	m_pCameraCom->m_tVspace.Eye		=	m_pTransformCom->Get_Info(INFO_POS);
	m_pCameraCom->m_tVspace.LookAt	=	m_pCameraCom->m_pLookAt->Get_Transform()->Get_Info(INFO_POS);
	m_pCameraCom->m_tVspace.Up		=	vec3.up;
}

void CPlayer_Camera::Free()
{
	__super::Free();
}

CPlayer_Camera* CPlayer_Camera::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayer_Camera*	pInstance = new CPlayer_Camera(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Player Camera Create Failed");
		return nullptr;
	}

	return pInstance;
}