#pragma once

#include "CameraObject.h"

BEGIN(Engine)

END

class CTool_Camera : public Engine::CCameraObject
{
private:
	explicit CTool_Camera(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTool_Camera(const CTool_Camera& rhs);
	virtual ~CTool_Camera();

public:
	virtual HRESULT			Ready_Object(void) override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object(void) override;

private:
	HRESULT					Add_Component(void);
	void					Key_Input(const _float& fTimeDelta);

public:
	static CTool_Camera*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	MOVEINFO				m_tMoveInfo;

private:
	virtual void			Free() override;

};