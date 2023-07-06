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

public:
	void					Set_LookAt(CGameObject* _pLookAt) { m_pLookAt = _pLookAt; }
	void					Set_Follow(CGameObject*	_pFollow) { m_pFollow = _pFollow; }

	CGameObject*			Get_LookAt() const { return m_pLookAt; }
	CGameObject*			Get_Follow() const { return m_pFollow; }

	const VIEWSPACE&		Get_ViewSpace() const { return m_tVspace; }
	const PROJECTION&		Get_Projection() const { return m_tProj; }
	const D3DVIEWPORT9&		Get_ViewPort() const { return m_tVport; }
	const _matrix&			Get_MatWorld() const { return m_matWorld; }

	const _bool				Is_LookAt() const { NULL_CHECK_RETURN(m_pLookAt, FALSE); return TRUE; }
	const _bool				Is_Follow() const { NULL_CHECK_RETURN(m_pFollow, FALSE); return TRUE; }

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
	_matrix					m_matWorld;

private:
	virtual void			Free();
};

END