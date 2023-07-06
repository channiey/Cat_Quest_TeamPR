#include "stdafx.h"
#include "..\Header\Tool_Camera.h"

#include "Export_Function.h"

CTool_Camera::CTool_Camera(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CCameraObject(pGraphicDev)
{

}
CTool_Camera::CTool_Camera(const CTool_Camera& rhs)
	: Engine::CCameraObject(rhs)
	, m_tMoveInfo(rhs.m_tMoveInfo)
{

}
CTool_Camera::~CTool_Camera()
{
}

HRESULT CTool_Camera::Ready_Object(void)
{
	CCameraObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ VTXCNTX * 0.5f, 50.f, VTXCNTZ * 0.5f });

	m_tMoveInfo.fMoveSpeed *= 2.f;
	return S_OK;
}

Engine::_int CTool_Camera::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Key_Input(fTimeDelta);

	return iExit;
}

void CTool_Camera::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();
}

HRESULT CTool_Camera::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	return S_OK;
}

void CTool_Camera::Key_Input(const _float& fTimeDelta)
{
	_long dwMouse = 0;

	// Translate
	if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
		m_pTransformCom->Translate(vec3.forward + vec3.right, fTimeDelta * m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
		m_pTransformCom->Translate(vec3.forward + -vec3.right, fTimeDelta * m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
		m_pTransformCom->Translate(-vec3.forward + vec3.right, fTimeDelta * m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
		m_pTransformCom->Translate(-vec3.forward - vec3.right, fTimeDelta * m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
		m_pTransformCom->Translate(DIR_FORWARD, fTimeDelta * m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
		m_pTransformCom->Translate(DIR_FORWARD, fTimeDelta * -m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
		m_pTransformCom->Translate(DIR_RIGHT, fTimeDelta * m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
		m_pTransformCom->Translate(DIR_RIGHT, fTimeDelta * -m_tMoveInfo.fMoveSpeed);

	// Zoom
	if (dwMouse = CInputDev::GetInstance()->Get_DIMouseMove(DIMS_Z))
	{
		// 최대 최소 예외 처리 필요 (굳이 툴이니까 보간까지 필요 X)

		if (0 < dwMouse)
			m_pCameraCom->m_fDistance += m_pCameraCom->m_fSpeedZoom * fTimeDelta;
		else
			m_pCameraCom->m_fDistance -= m_pCameraCom->m_fSpeedZoom * fTimeDelta;
	}



	m_pCameraCom->m_tVspace.Eye		= m_pTransformCom->Get_Info(INFO_POS);
	m_pCameraCom->m_tVspace.LookAt  = m_pTransformCom->Get_Info(INFO_POS) + _vec3{ 0.f, -1.f, 1.f };
	m_pCameraCom->m_tVspace.Up		= vec3.up;
}

void CTool_Camera::Free()
{
	__super::Free();
}

CTool_Camera* CTool_Camera::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTool_Camera* pInstance = new CTool_Camera(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Tool Camera Create Failed");
		return nullptr;
	}

	return pInstance;
}
