#pragma once

#include "GameObject.h"

BEGIN(Engine)

class CTexture;

END

class CEnvironment : public Engine::CGameObject
{
protected:
	explicit CEnvironment(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CEnvironment(const CEnvironment& rhs);
	virtual ~CEnvironment();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

	virtual void			Play_ColLogic(const _float& fTimeDelta) {} // 충돌 로직
public:
	CTexture*				Get_Texture() { return m_pTextureCom; }
	ENTER_TYPE				Get_EnterType() { return m_eEnter; }
	INTERACTION_TYPE		Get_InteractionType() { return m_eInteraction; }

	void					Set_IsEnter(_bool _switch) { m_bEnter = _switch; }
	void					Set_EventSwitch(_bool _switch) { m_bEventSwitch = _switch; }
private:
	HRESULT					Add_Component();

protected:
	CTexture*				m_pTextureCom = nullptr;

	ENTER_TYPE				m_eEnter;
	INTERACTION_TYPE		m_eInteraction;
	_bool					m_bEventSwitch = false;
	_bool					m_bEnter = false;

protected:
	virtual void			Free() override;
};

