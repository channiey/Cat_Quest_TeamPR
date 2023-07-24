#include "..\..\Header\CameraMgr.h"

#include "..\..\Header\GameObject.h"

#include "Transform.h"
#include "Management.h"

IMPLEMENT_SINGLETON(CCameraMgr)

CCameraMgr::CCameraMgr()
	: m_pCurCamera(nullptr)
	, m_pPreCamera(nullptr)
	, m_bBlending(false)
	, m_eCurAction(CAMERA_ACTION::NONE)
	, m_bFix(FALSE)
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

void CCameraMgr::Start_Fade(const FADE_MODE& _eMode)
{
	NULL_CHECK(m_pCurCamera);

	m_pCurCamera->Start_Fade(_eMode);
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

HRESULT CCameraMgr::Start_Action(const CAMERA_ACTION& _eMode, const _vec3& _vStartPos, const _vec3& _vEndPos, const _bool& _bFix)
{	
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	NULL_CHECK_RETURN(m_pCurCamera, E_FAIL);

	m_bFix = _bFix;

	if (CAMERA_TYPE::PLAYER_CAMERA == m_pCurCamera->Get_CameraCom()->Get_CameraType())
	{
		_float fCurFOV = m_pCurCamera->Get_CameraCom()->Get_Projection().FOV;

		switch (_eMode)
		{

#pragma region PLAYER

		// IDLE -> OTHER
		case Engine::CAMERA_ACTION::PLAYER_IDL_TO_ATK : m_pCurCamera->Get_CameraCom()->Lerp_FOV(
				0.15f, fCurFOV, CAM_FOV_PLAYER_ATTACK, LERP_MODE::SMOOTHERSTEP); break;

		case Engine::CAMERA_ACTION::PLAYER_IDL_TO_FLY : m_pCurCamera->Get_CameraCom()->Lerp_FOV(
				1.f, fCurFOV, CAM_FOV_PLAYER_FLIGHT, LERP_MODE::SMOOTHERSTEP); break;

		case Engine::CAMERA_ACTION::PLAYER_IDL_TO_RANATK : m_pCurCamera->Get_CameraCom()->Lerp_FOV(
				0.15f, fCurFOV, CAM_FOV_PLAYER_RANGE, LERP_MODE::SMOOTHERSTEP); break;

		// OTHER -> OTHER
		case Engine::CAMERA_ACTION::PLAYER_ATK_TO_IDL : m_pCurCamera->Get_CameraCom()->Lerp_FOV(
				0.15f, fCurFOV, CAM_FOV_DEFAULT, LERP_MODE::SMOOTHERSTEP); break;

		case Engine::CAMERA_ACTION::PLAYER_FLY_TO_IDL : m_pCurCamera->Get_CameraCom()->Lerp_FOV(
				1.f, fCurFOV, CAM_FOV_DEFAULT, LERP_MODE::SMOOTHERSTEP); break;

		case Engine::CAMERA_ACTION::PLAYER_RANATK_TO_IDL : m_pCurCamera->Get_CameraCom()->Lerp_FOV(
				0.2f, fCurFOV, CAM_FOV_DEFAULT, LERP_MODE::SMOOTHERSTEP); break; 
		
		// OTHER -> IDLE
		case Engine::CAMERA_ACTION::PLAYER_ATK_TO_RANATK :
			break;

		case Engine::CAMERA_ACTION::PLAYER_RANATK_TO_ATK :
			break;

#pragma endregion

#pragma region SCENE

		case Engine::CAMERA_ACTION::SCENE_ENTER_INGAME:
		{
		/*
		
			*	필드씬 입장시 플레이어 위에서 카메라가 내려오는 연출
			

			1. 카메라를 플레이어 + y20을 타겟으로 하는 Eye에 위치시킨다.

			2. Look의 y를 보간하여 플레이어까지 내린다.

			3. 플레이어 y와 일치되면 게임을 시작한다.

		*/
			_vec3 vPlayerPos;		// 플레이어 시작 포지션
			_vec3 vLerpStartLookAt; // 플레이어 시작 포지션 y + fHeight
			_float fHeight = 30.f;
			_vec3 vCamInitEye;		// 플레이어 시작포지션에서의 카메라 포지션

			CGameObject* pPlayer = m_pCurCamera->Get_CameraCom()->Get_Follow();

			NULL_CHECK_RETURN(pPlayer, E_FAIL);

			vPlayerPos = pPlayer->Get_Transform()->Get_Info(INFO_POS);
			vLerpStartLookAt = _vec3{ vPlayerPos.x, vPlayerPos.y + fHeight, vPlayerPos.z };


			// 플레이어 시작 포지션 y + 20 위치에 카메라를 위치시킨다.
			vCamInitEye = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Calculate_Nonelerp_Eye(vLerpStartLookAt).Eye;
			CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Set_Eye(vCamInitEye);

			// 룩의 y값에 대한 보간을 시작하고, 카메라의 업데이터에서는 해당 y 포지션을 룩으로 하여 포지션을 결정 할 수 있도록 한다.
			m_pCurCamera->Get_CameraCom()->Lerp_Height(5.f, fHeight, 0, LERP_MODE::SMOOTHERSTEP);
		}
			break;
		case Engine::CAMERA_ACTION::SCENE_LOOK_WORLD:
		{
		
		}
			break;

		case Engine::CAMERA_ACTION::SCENE_ENTER_FIELD:
		{
			_vec3 vPlayerPos;		// 플레이어 시작 포지션
			_vec3 vLerpStartLookAt; // 플레이어 시작 포지션 y + fHeight
			_float fHeight = 30.f;
			_vec3 vCamInitEye;		// 플레이어 시작포지션에서의 카메라 포지션

			CGameObject* pPlayer = m_pCurCamera->Get_CameraCom()->Get_Follow();

			NULL_CHECK_RETURN(pPlayer, E_FAIL);

			vPlayerPos = pPlayer->Get_Transform()->Get_Info(INFO_POS);
			vLerpStartLookAt = _vec3{ vPlayerPos.x, vPlayerPos.y + fHeight, vPlayerPos.z };


			// 플레이어 시작 포지션 y + 20 위치에 카메라를 위치시킨다.
			vCamInitEye = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Calculate_Nonelerp_Eye(vLerpStartLookAt).Eye;
			CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Set_Eye(vCamInitEye);

			// 룩의 y값에 대한 보간을 시작하고, 카메라의 업데이터에서는 해당 y 포지션을 룩으로 하여 포지션을 결정 할 수 있도록 한다.
			m_pCurCamera->Get_CameraCom()->Lerp_Height(5.f, fHeight, 0, LERP_MODE::SMOOTHERSTEP);
		}
		break;

#pragma endregion

#pragma region OBJECT

		case Engine::CAMERA_ACTION::OBJ_CHANGE_TARGET:
		{
			/*
				시작 위치 -> 종료 위치 -> 시작 위치

				팔로우 및 룩앳의 위치를 보간한다.

				시작 위치와 종료위치는 디폴트 매개변수로 설정한다.
			*/

			// 두 지점 사이의 거리에 비례하여 보간 시간을 정하도록 한다.
			_float fDistance = D3DXVec3Length(&(_vStartPos - _vEndPos));
			_float fMag = 0.03f;

			// y에 대한 보간은 빼도록 한다.
			_vec3 vOrigin = _vStartPos;
			_vec3 vDest = _vEndPos;

			m_pCurCamera->Get_CameraCom()->Lerp_Vec3(fDistance * fMag, vOrigin, vDest, LERP_MODE::SMOOTHERSTEP);


		}
		break;

#pragma endregion

		
		
		
		
		
		
		
		default:
			break;
		}
		
	}

	Set_CurCameraAction(_eMode);

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
