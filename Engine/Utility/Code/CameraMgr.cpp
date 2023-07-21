#include "..\..\Header\CameraMgr.h"

#include "..\..\Header\GameObject.h"

IMPLEMENT_SINGLETON(CCameraMgr)

CCameraMgr::CCameraMgr()
	: m_pCurCamera(nullptr)
	, m_pPreCamera(nullptr)
	, m_bBlending(false)
{
}

CCameraMgr::~CCameraMgr()
{
	Free();
}

CCameraObject * CCameraMgr::Get_Camera(const _tchar * pCameraTag)
{
	return nullptr;
}

HRESULT CCameraMgr::Add_Camera(const _tchar * pCameraTag, CCameraObject * pCameraObject)
{
	CCameraObject* pCamera = Find_Camera(pCameraTag);

	if (nullptr != pCamera) return E_FAIL;

	m_mapCamera.emplace(pCameraTag, pCameraObject);

	return S_OK;
}

HRESULT CCameraMgr::Set_MainCamera(const _tchar * pCameraTag)
{
	CCameraObject* pChangeCamera = Find_Camera(pCameraTag);

	NULL_CHECK_RETURN(pChangeCamera, E_FAIL);

	if (1 == m_mapCamera.size())
		m_pCurCamera = m_pPreCamera = pChangeCamera;
	else
	{
		FAILED_CHECK_RETURN(Change_Camera(pCameraTag), E_FAIL);
		return S_OK;
	}

	FAILED_CHECK_RETURN(Set_ViewSpace()	, E_FAIL);
	FAILED_CHECK_RETURN(Set_Projection(), E_FAIL);
	FAILED_CHECK_RETURN(Set_Viewport()	, E_FAIL);

	return S_OK;
}

HRESULT CCameraMgr::Change_Camera(const _tchar * pCameraTag)
{
	CCameraObject* pChangeCamera = Find_Camera(pCameraTag);

	NULL_CHECK_RETURN(pChangeCamera, E_FAIL);

	m_pPreCamera = m_pCurCamera;

	m_pCurCamera = pChangeCamera;

	m_bBlending = true;

	FAILED_CHECK_RETURN(Set_ViewSpace()	, E_FAIL);
	FAILED_CHECK_RETURN(Set_Projection(), E_FAIL);
	FAILED_CHECK_RETURN(Set_Viewport()	, E_FAIL);

	return S_OK;
}

const _matrix& CCameraMgr::Get_Billboard_X()
{
	NULL_CHECK_RETURN(m_pCurCamera, _matrix{});

	NULL_CHECK_RETURN(m_pCurCamera->Get_CameraCom(), _matrix{});

	return m_pCurCamera->Get_CameraCom()->m_matBillboardX;
}

const _matrix& CCameraMgr::Get_Billboard_Y()
{
	NULL_CHECK_RETURN(m_pCurCamera, _matrix{});

	NULL_CHECK_RETURN(m_pCurCamera->Get_CameraCom(), _matrix{});

	return m_pCurCamera->Get_CameraCom()->m_matBillboardY;
}

const _matrix& CCameraMgr::Get_WorldMat()
{
	NULL_CHECK_RETURN(m_pCurCamera, _matrix{});

	NULL_CHECK_RETURN(m_pCurCamera->Get_CameraCom(), _matrix{});

	return m_pCurCamera->Get_CameraCom()->m_matWorld;
}

HRESULT CCameraMgr::Set_ViewSpace()
{
	NULL_CHECK_RETURN(m_pCurCamera, E_FAIL);

	m_pCurCamera->Get_CameraCom()->Set_ViewSpace();

	return S_OK;
}

HRESULT CCameraMgr::Set_Projection()
{
	NULL_CHECK_RETURN(m_pCurCamera, E_FAIL);

	m_pCurCamera->Get_CameraCom()->Set_Projection();

	return S_OK;
}

HRESULT CCameraMgr::Set_Viewport()
{
	NULL_CHECK_RETURN(m_pCurCamera, E_FAIL);

	m_pCurCamera->Get_CameraCom()->Set_Viewport();

	return S_OK;
}

HRESULT CCameraMgr::Set_LookAt(CGameObject* pLookAt)
{
	NULL_CHECK_RETURN(m_pCurCamera, E_FAIL);

	m_pCurCamera->Get_CameraCom()->Set_LookAt(pLookAt);

	return S_OK;
}

HRESULT CCameraMgr::Set_Follow(CGameObject* pFollow)
{
	NULL_CHECK_RETURN(m_pCurCamera, E_FAIL);

	m_pCurCamera->Get_CameraCom()->Set_Follow(pFollow);

	return S_OK;
}

void CCameraMgr::Shake_Camera(const _float& _fTime, const _float& _fIntensity)
{
	m_pCurCamera->Get_CameraCom()->Shake_Camera(_fTime, _fIntensity);
}

const _bool& CCameraMgr::Is_Shake_Camera() const
{
	return m_pCurCamera->Get_CameraCom()->Is_Shake_Camera();
}

void CCameraMgr::Stop_Shake()
{
	m_pCurCamera->Get_CameraCom()->Stop_Shake();
}

HRESULT CCameraMgr::Start_Lerp(const CAMERA_LEPR_MODE& _eMode)
{	
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	NULL_CHECK_RETURN(m_pCurCamera, E_FAIL);

	if (CAMERA_TYPE::PLAYER_CAMERA == m_pCurCamera->Get_CameraCom()->Get_CameraType())
	{
		_float fCurFOV = m_pCurCamera->Get_CameraCom()->Get_Projection().FOV;

		switch (_eMode)
		{
			// IDLE -> OTHER
		case Engine::CAMERA_LEPR_MODE::PLAYER_IDL_TO_ATK:  
		{
			m_pCurCamera->Get_CameraCom()->Lerp_FOV(
				0.15f, fCurFOV, CAM_PLAYER_ATTACK_FOV, LERP_MODE::SMOOTHERSTEP);
		}
			break;
		case Engine::CAMERA_LEPR_MODE::PLAYER_IDL_TO_FLY:
		{
			m_pCurCamera->Get_CameraCom()->Lerp_FOV(
				1.f, fCurFOV, CAM_PLAYER_FLIGHT_FOV, LERP_MODE::SMOOTHERSTEP);
		}
		break;
		case Engine::CAMERA_LEPR_MODE::PLAYER_IDL_TO_RANATK:
		{
			m_pCurCamera->Get_CameraCom()->Lerp_FOV(
			0.15f, fCurFOV, CAM_PLAYER_RANGE_FOV, LERP_MODE::SMOOTHERSTEP);
		}
		break;


		// OTHER -> OTHER
		case Engine::CAMERA_LEPR_MODE::PLAYER_ATK_TO_IDL:
		{
			m_pCurCamera->Get_CameraCom()->Lerp_FOV(
				0.15f, fCurFOV, CAM_DEFAULT_FOV, LERP_MODE::SMOOTHERSTEP);
		}
			break;
		case Engine::CAMERA_LEPR_MODE::PLAYER_FLY_TO_IDL:
		{
			m_pCurCamera->Get_CameraCom()->Lerp_FOV(
				1.f, fCurFOV, CAM_DEFAULT_FOV, LERP_MODE::SMOOTHERSTEP);
		}
			break;
		case Engine::CAMERA_LEPR_MODE::PLAYER_RANATK_TO_IDL:
		{
			m_pCurCamera->Get_CameraCom()->Lerp_FOV(
				0.2f, fCurFOV, CAM_DEFAULT_FOV, LERP_MODE::SMOOTHERSTEP);
		}
		break; 
		
		
		// OTHER -> IDLE
		case Engine::CAMERA_LEPR_MODE::PLAYER_ATK_TO_RANATK:
		{
		}
		break;
		case Engine::CAMERA_LEPR_MODE::PLAYER_RANATK_TO_ATK:
		{
		}
		break;
		
		
		
		
		
		
		
		
		default:
			break;
		}
		
	}

	return S_OK;
}

CCameraObject * CCameraMgr::Find_Camera(const _tchar * pCameraTag)
{
	auto		iter = find_if(m_mapCamera.begin(), m_mapCamera.end(), CTag_Finder(pCameraTag));

	if (iter == m_mapCamera.end())
		return nullptr;

	return iter->second;
}

void CCameraMgr::Blend_Camera()
{

}

void CCameraMgr::Free()
{
	//for_each(m_mapCamera.begin(), m_mapCamera.end(), CDeleteMap());
	//m_mapCamera.clear();
}
