#pragma once

#include "CameraObject.h"

BEGIN(Engine)

END

class CFadeUI;

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

public:
	virtual void						Start_Fade(const FADE_MODE& _eMode) override;


private:
	HRESULT					Add_Component(void);
	void					Set_Zoom(const _float& fTimeDelta);
	void					Set_ViewSpace();

	void					Lerp_Enter_Scene();
	void					Lerp_Change_Target();

public:
	static CPlayer_Camera*	Create(LPDIRECT3DDEVICE9 pGraphicDev);



private:
	_float					m_fDefaultHeight;

	_float					m_fNearZoom;		// ¡‹ √÷¥Î ∞≈∏Æ (»Ÿ ¡∂¿€Ω√)	
	_float					m_fFarZoom;			// ¡‹ √÷º“ ∞≈∏Æ (")
	_float					m_fLerpTime;		

	CFadeUI*				m_pFadeUI;

private:
	virtual void			Free() override;

};