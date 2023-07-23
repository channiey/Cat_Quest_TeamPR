#include "stdafx.h"
#include "..\Header\Player_Camera.h"

#include "Export_Function.h"

#include "FadeUI.h"

CPlayer_Camera::CPlayer_Camera(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CCameraObject(pGraphicDev)
	, m_pFadeUI(nullptr)
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
	m_fNearZoom			= CAM_DISTANCE_DEFAULT;
	m_fFarZoom			= 90.f;
	m_pCameraCom->m_fDistance = m_fNearZoom;

	m_pTransformCom->Set_Pos(_vec3{ 0.f, m_fDefaultHeight, -m_pCameraCom->m_fDistance });
	m_pCameraCom->m_fSpeedZoom = 100.f;

	m_bMaintain = true; // 씬 변경시 유지 (사용시 팀장 보고)

	m_szName = L"Player_Camera";

	m_pCameraCom->Set_CameraType(CAMERA_TYPE::PLAYER_CAMERA);

	m_pFadeUI = CFadeUI::Create(m_pGraphicDev);
	CEventMgr::GetInstance()->Add_Obj(m_pFadeUI->Get_Name(), m_pFadeUI);

	return S_OK;
}

Engine::_int CPlayer_Camera::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	/*if (m_pCameraCom->m_tZoomLerp.bActive)
	{
		m_pCameraCom->m_tZoomLerp.Update_Lerp(fTimeDelta);
		m_pCameraCom->m_fDistance = m_pCameraCom->m_tZoomLerp.fCurValue;
	}
	else
	{
		Set_Zoom(fTimeDelta);
	}*/

	if (m_pCameraCom->m_tFOVLerp.bActive)
	{
		m_pCameraCom->m_tFOVLerp.Update_Lerp(fTimeDelta);
		m_pCameraCom->m_tProj.FOV = m_pCameraCom->m_tFOVLerp.fCurValue;
		m_pCameraCom->Set_Projection();
	}

	if (m_pCameraCom->m_tHeightLerp.bActive)
	{
		m_pCameraCom->m_tHeightLerp.Update_Lerp(fTimeDelta);
	}

	if (m_pCameraCom->m_tVec3Lerp.bActive)
	{
		m_pCameraCom->m_tVec3Lerp.Update_Lerp(fTimeDelta);
	}

	return iExit;
}

void CPlayer_Camera::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();

	Set_ViewSpace();
}

void CPlayer_Camera::Start_Fade(const FADE_MODE& _eMode)
{
	switch (_eMode)
	{
	case Engine::FADE_MODE::ENTER_WORLD:
	{
		m_pFadeUI->Start_Fade(3.f, 255.f, 0.f, true, LERP_MODE::EASE_IN);
	}
		break;
	case Engine::FADE_MODE::BLACK_FADE_IN:
		break;
	case Engine::FADE_MODE::BLACK_FADE_OUT:
		break;
	case Engine::FADE_MODE::WHITE_FADE_OUT:
		break;
	case Engine::FADE_MODE::WHITE_FADE_IN:
		break;

	default:
		break;
	}
	
}

HRESULT CPlayer_Camera::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	return S_OK;
}


void CPlayer_Camera::Set_Zoom(const _float& fTimeDelta)
{
	_long dwMouse = 0;

	// 01. Zoom Setting
	if (dwMouse = CInputDev::GetInstance()->Get_DIMouseMove(DIMS_Z))
	{
		if (0 < dwMouse)
			m_pCameraCom->m_fDistance -= m_pCameraCom->m_fSpeedZoom * fTimeDelta;
		else
			m_pCameraCom->m_fDistance += m_pCameraCom->m_fSpeedZoom * fTimeDelta;
	/*	if (0 < dwMouse)
		{
		}
		else
		{
			m_pCameraCom->m_fDistance = m_fFarZoom;
		}*/
	}
}

void CPlayer_Camera::Set_ViewSpace() 
{
	// 플레이어의 최종 포지션 결정 이후에 해당 함수가 호출되어야 한다!
	
	NULL_CHECK(m_pCameraCom->m_pLookAt);
	NULL_CHECK(m_pCameraCom->m_pFollow);

	// Enter Scene Lerp
	if (m_pCameraCom->m_tHeightLerp.bActive && CAMERA_ACTION::SCENE_ENTER_FIELD == CCameraMgr::GetInstance()->Get_CurCameraAction())
	{
		Lerp_Enter_Scene();
		return;
	}
	// Change Target Lerp
	else if (CAMERA_ACTION::OBJ_CHANGE_TARGET == CCameraMgr::GetInstance()->Get_CurCameraAction())
	{
		Lerp_Change_Target();
		return;
	}

	_vec3 vFollowPos = m_pCameraCom->m_pFollow->Get_Transform()->Get_Info(INFO_POS);
	_vec3 vLookPos = m_pCameraCom->m_tVspace.LookAt;
	_vec3 vLerpPos{};

	const _float fLerpValue = 8.f;
	
	D3DXVec3Lerp(&vLerpPos, &vLookPos, &vFollowPos, Engine::Get_TimeDelta(L"Timer_FPS65") * fLerpValue);
	vLerpPos.y = vFollowPos.y; // 플레이어 추적시 y 값 흔들림 보정
	
	vLerpPos.y = m_pCameraCom->m_fInitLookY; // 이거 예외처리 필요

	// 02. 타겟까지의 디스턴스에 따른 카메라의 높이값을 구한다.
	_vec3 vDir1 = m_pTransformCom->Get_Info(INFO_POS) - vLerpPos;
	_vec3 vDir2 = { vDir1.x, 0.f, vDir1.z };
	D3DXVec3Normalize(&vDir1, &vDir1);
	D3DXVec3Normalize(&vDir2, &vDir2);
	_float fTheta = D3DXVec3Dot(&vDir1, &vDir2);
	_float fY = sinf(fTheta) * m_pCameraCom->m_fDistance * CAM_HEIGHT_MAG;

	m_pTransformCom->Set_Pos(_vec3{ vLerpPos.x,
									fY,
									vLerpPos.z - m_pCameraCom->m_fDistance });



	m_pCameraCom->m_tVspace.Eye = m_pTransformCom->Get_Info(INFO_POS);
	m_pCameraCom->m_tVspace.LookAt = vLerpPos;  // m_pCameraCom->m_pLookAt->Get_Transform()->Get_Info(INFO_POS); //vLerpPos;
	m_pCameraCom->m_tVspace.Up = vec3.up;
}

void CPlayer_Camera::Lerp_Enter_Scene()
{ 
	_vec3 vFollowPos = m_pCameraCom->m_pFollow->Get_Transform()->Get_Info(INFO_POS);
	_vec3 vLookPos = vFollowPos;

	vLookPos.y += m_pCameraCom->m_tHeightLerp.fCurValue;

	_vec3 vDir1 = m_pTransformCom->Get_Info(INFO_POS) - vLookPos;
	_vec3 vDir2 = { vDir1.x, 0.f, vDir1.z };
	D3DXVec3Normalize(&vDir1, &vDir1);
	D3DXVec3Normalize(&vDir2, &vDir2);
	_float fTheta = D3DXVec3Dot(&vDir1, &vDir2);
	_float fY = sinf(fTheta) * m_pCameraCom->m_fDistance * CAM_HEIGHT_MAG;

	m_pTransformCom->Set_Pos(_vec3{ vLookPos.x,
									fY,
									vLookPos.z - m_pCameraCom->m_fDistance });



	m_pCameraCom->m_tVspace.Eye = m_pTransformCom->Get_Info(INFO_POS);
	m_pCameraCom->m_tVspace.LookAt = vLookPos;  
	m_pCameraCom->m_tVspace.Up = vec3.up;

	if (!m_pCameraCom->m_tHeightLerp.bActive)
		CCameraMgr::GetInstance()->Set_CurCameraAction(CAMERA_ACTION::NONE);
}

void CPlayer_Camera::Lerp_Change_Target()
{
	_vec3 vFollowPos = m_pCameraCom->m_tVec3Lerp.vCurVec;
	_vec3 vLookPos = vFollowPos;

	// 02. 타겟까지의 디스턴스에 따른 카메라의 높이값을 구한다.
	_vec3 vDir1 = m_pTransformCom->Get_Info(INFO_POS) - vLookPos;
	_vec3 vDir2 = { vDir1.x, 0.f, vDir1.z };
	D3DXVec3Normalize(&vDir1, &vDir1);
	D3DXVec3Normalize(&vDir2, &vDir2);
	_float fTheta = D3DXVec3Dot(&vDir1, &vDir2);
	_float fY = sinf(fTheta) * m_pCameraCom->m_fDistance * CAM_HEIGHT_MAG;

	m_pTransformCom->Set_Pos(_vec3{ vLookPos.x,
									fY,
									vLookPos.z - m_pCameraCom->m_fDistance });


	m_pCameraCom->m_tVspace.Eye = m_pTransformCom->Get_Info(INFO_POS);
	m_pCameraCom->m_tVspace.LookAt = vLookPos;  // m_pCameraCom->m_pLookAt->Get_Transform()->Get_Info(INFO_POS); //vLerpPos;
	m_pCameraCom->m_tVspace.Up = vec3.up;

	if (!m_pCameraCom->m_tVec3Lerp.bActive && !CCameraMgr::GetInstance()->Is_Fix())
		CCameraMgr::GetInstance()->Set_CurCameraAction(CAMERA_ACTION::NONE);
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


