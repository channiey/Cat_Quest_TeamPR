#pragma once
#include "stdafx.h"
#include "State.h" 
#include "Player.h"

BEGIN(Engine)

END

class CPlayerState_bRoll : public CState
{
public:
	explicit						CPlayerState_bRoll(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CPlayerState_bRoll();

public:
	virtual HRESULT					Ready_State(CStateMachine* pOwner);
	virtual STATE_TYPE				Update_State(const _float& fTimeDelta);
	virtual void					LateUpdate_State();
	virtual void					Render_State();

	virtual STATE_TYPE				Key_Input(const _float& fTimeDelta);

	static CPlayerState_bRoll* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);

private:
	_vec3			m_vDir;

private:
	virtual void	Free();
};

