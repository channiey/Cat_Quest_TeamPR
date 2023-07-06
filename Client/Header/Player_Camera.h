#pragma once

#include "CameraObject.h"

BEGIN(Engine)

END

class CPlayer_Camera : public Engine::CCameraObject
{
private:
	explicit CPlayer_Camera(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPlayer_Camera(const CPlayer_Camera& rhs);
	virtual ~CPlayer_Camera();

public:
	virtual HRESULT			Ready_Object(void) override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object(void) override;

private:
	HRESULT					Add_Component(void);
	void					Move(const _float& fTimeDelta);

public:
	static CPlayer_Camera*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	_float					m_fDefaultHeight;

	_float					m_fNearZoom;		// ¡‹ √÷¥Î ∞≈∏Æ (»Ÿ ¡∂¿€Ω√)	
	_float					m_fFarZoom;			// ¡‹ √÷º“ ∞≈∏Æ (")
	_float					m_fLerpTime;		

private:
	virtual void			Free() override;

};