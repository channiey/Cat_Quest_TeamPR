#pragma once

#include "Component.h"

BEGIN(Engine)

class CGameObject;

class ENGINE_DLL CCamera : public CComponent
{
private:
	explicit CCamera();
	explicit CCamera(LPDIRECT3DDEVICE9 pGraphicDev, HWND* _pHwnd); // HWND는 원본 생성시 한번만 넣어준다.
	explicit CCamera(const CCamera& rhs, CGameObject* _pOwnerObject);
	virtual ~CCamera();

public:
	HRESULT					Ready_Camera();
	virtual _int			Update_Component(const _float& fTimeDelta);	


public:						
	HRESULT					Set_ViewSpace();	// 뷰스페이스 변환
	HRESULT					Set_Projection();	// 투영 변환
	HRESULT					Set_Viewport();		// 뷰포트 변환

	HRESULT					Set_ViewSpace(const _matrix& _matView);
	HRESULT					Set_Projection(const _matrix& _matProj);	
	HRESULT					Set_Viewport(const D3DVIEWPORT9& _tViewport);
	HRESULT					Set_InitLook_Y(const _float& _fY) { m_fInitLookY = _fY;	return S_OK; }
	void					Set_CameraType(const CAMERA_TYPE& _eType) { m_eCameraType = _eType; }

public:
	void					Set_LookAt(CGameObject* _pLookAt) { m_pLookAt = _pLookAt; }
	void					Set_Follow(CGameObject*	_pFollow) { m_pFollow = _pFollow; }

	CGameObject*			Get_LookAt() const { return m_pLookAt; }
	CGameObject*			Get_Follow() const { return m_pFollow; }

	const VIEWSPACE&		Get_ViewSpace() const { return m_tVspace; }
	const PROJECTION&		Get_Projection() const { return m_tProj; }
	const D3DVIEWPORT9&		Get_ViewPort() const { return m_tVport; }
	const _matrix&			Get_MatWorld() const { return m_matWorld; }
	const _matrix&			Get_MatProj() const { return m_matProj; }
	const _matrix&			Get_MatView() const { return m_matView; }
	const CAMERA_TYPE&		Get_CameraType() const { return m_eCameraType; }
	const CAMERA_ACTION&	Get_CurCameraAction() const { return m_eCameraAction; }

	const _bool				Is_LookAt() const { NULL_CHECK_RETURN(m_pLookAt, FALSE); return TRUE; }
	const _bool				Is_Follow() const { NULL_CHECK_RETURN(m_pFollow, FALSE); return TRUE; }
	const _bool				Is_Action() const { return m_bAction; }
	void					Lerp_Distance(const _float& _fTime, const _float _fStartDist, const _float _fEndDist, const LERP_MODE& _eMode = LERP_MODE::DEFAULT);
	void					Lerp_FOV(const _float& _fTime, const _float _fStartDist, const _float _fEndDist, const LERP_MODE& _eMode = LERP_MODE::DEFAULT);

public:
	void					Shake_Camera(const _float& _fTime, const _float& _fIntensity);
	const _bool&			Is_Shake_Camera() const { return m_bShake; }
	void					Stop_Shake();

private:
	void					Apply_Shake();

public:
	static CCamera*			Create(LPDIRECT3DDEVICE9 pGraphicDev, HWND* const _pHwnd);
	virtual CComponent*		Clone(CGameObject* _pOwnerObject);

public:
	VIEWSPACE				m_tVspace;	// View Space
	PROJECTION				m_tProj;	// Projection
	D3DVIEWPORT9			m_tVport;	// View Port

	CGameObject*			m_pLookAt;
	CGameObject*			m_pFollow;
	
	_float					m_fSpeedZoom;

	PROJECTID				m_eProjectID;

	_float					m_fDistance;

	HWND*					m_pHwnd;

	_matrix					m_matBillboardX;
	_matrix					m_matBillboardY;
	_matrix					m_matWorld;
	_matrix					m_matProj;
	_matrix                 m_matView;

	// Shake
	_bool					m_bShake;
	_float					m_fShakeTime;
	_float					m_fAccTime;
	_float					m_fIntensity;

	_float					m_fInitLookY; // 플레이어등 점프 전 초기 y값을 받아둔다.

	LERP_FLOAT_INFO			m_tZoomLerp;
	LERP_FLOAT_INFO			m_tFOVLerp;

	CAMERA_TYPE				m_eCameraType;

	CAMERA_ACTION			m_eCameraAction;
	_bool					m_bAction;

private:
	virtual void			Free();

};

END