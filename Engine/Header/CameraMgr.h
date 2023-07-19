#pragma once

#include "Engine_Define.h"
#include "Base.h"

#include "CameraObject.h"
#include "Camera.h"

BEGIN(Engine)

class CGameObject;

class ENGINE_DLL CCameraMgr : public CBase
{
	DECLARE_SINGLETON(CCameraMgr)

private:
	explicit CCameraMgr();
	virtual ~CCameraMgr();

public:
	CCameraObject*							Get_Camera		(const _tchar* pCameraTag);
	CCameraObject*							Get_CurCamera	()															{ return m_pCurCamera; }
	HRESULT									Add_Camera		(const _tchar* pCameraTag, CCameraObject* pCameraObject);
	HRESULT									Set_MainCamera	(const _tchar* pCameraTag);
	HRESULT									Change_Camera	(const _tchar* pCameraTag);
	const _bool&							Is_Blending		() const													{ return m_bBlending; }
	const _matrix&							Get_Billboard_X();
	const _matrix&							Get_Billboard_Y();
	const _matrix&							Get_WorldMat();

public:
	HRESULT									Set_ViewSpace	();
	HRESULT									Set_Projection	();
	HRESULT									Set_Viewport	();

	HRESULT									Set_LookAt		(CGameObject* pLookAt);
	HRESULT									Set_Follow		(CGameObject* pFollow);

	void									Shake_Camera(const _float& _fTime = DF_CAMERA_SHAKE_TIME, const _float& _fIntensity = DF_CAMERA_SHAKE_INTENSITY);
	const _bool&							Is_Shake_Camera() const;
	void									Stop_Shake();

private:
	CCameraObject*							Find_Camera		(const _tchar* pCameraTag);
	void									Blend_Camera	();

private:
	map<const _tchar*, CCameraObject*>		m_mapCamera;
	CCameraObject*							m_pCurCamera; // 현재 카메라
	CCameraObject*							m_pPreCamera; // 이전 카메라

	_bool									m_bBlending;

public:
	virtual void Free();
};

END