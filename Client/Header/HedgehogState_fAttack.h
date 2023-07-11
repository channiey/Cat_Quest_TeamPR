#pragma once
#include "stdafx.h"
#include "Monster.h"
#include "State.h"


class CHedgehogState_fAttack :public CState
{

public:
	explicit			CHedgehogState_fAttack(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CHedgehogState_fAttack();


public:
	virtual HRESULT		Ready_State(CStateMachine* pOwner);
	virtual STATE_TYPE  Update_State(const _float& fTimeDelta);
	virtual void		LateUpdate_State();
	virtual void		Render_State();


	// 사용 안함
	virtual STATE_TYPE		Key_Input(const _float& fTimeDelta);

public:
	static CHedgehogState_fAttack* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);


private:
	virtual void Free();




};

