#pragma once
#include "stdafx.h"
#include "State.h"
#include "Monster.h"

BEGIN(Engine)

END

class CSquirrelState_Chase : public CState
{
public:
	explicit			CSquirrelState_Chase(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CSquirrelState_Chase();


public:
	virtual HRESULT		Ready_State(CStateMachine* pOwner);
	virtual STATE_TYPE  Update_State(const _float& fTimeDelta);
	virtual void		LateUpdate_State();
	virtual void		Render_State();


	// ��� ����
	virtual STATE_TYPE		Key_Input(const _float& fTimeDelta);



public:
	static CSquirrelState_Chase* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);


private:
	virtual void Free();

private:

	_float m_fAccTime;


};

