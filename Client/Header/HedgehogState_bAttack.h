#pragma once
#include "State.h"
#include "Monster.h"
#include "stdafx.h"

BEGIN(Engine)

END

class CHedgehogState_bAttack :  public CState
{


public:
	explicit			CHedgehogState_bAttack(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CHedgehogState_bAttack();


public:
	virtual HRESULT		Ready_State(CStateMachine* pOwner);
	virtual STATE_TYPE  Update_State(const _float& fTimeDelta);
	virtual void		LateUpdate_State();
	virtual void		Render_State();


	// ��� ����
	virtual STATE_TYPE		Key_Input(const _float& fTimeDelta);

public:
	static CHedgehogState_bAttack* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);


private:
	virtual void Free();





};

