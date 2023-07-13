#pragma once
#include "stdafx.h"
#include "State.h"
#include "Monster.h"

BEGIN(Engine)

END

class CBatState_Patrol : public CState
{
public:
	explicit			CBatState_Patrol(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CBatState_Patrol();


public:
	virtual HRESULT		Ready_State(CStateMachine* pOwner);
	virtual STATE_TYPE  Update_State(const _float& fTimeDelta);
	virtual void		LateUpdate_State();
	virtual void		Render_State();


	// ��� ����
	virtual STATE_TYPE		Key_Input(const _float& fTimeDelta);



public:
	static CBatState_Patrol* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);


private:

	_float fPatrol_Range;
	_float fChase_Range;
	_float fComeBack_Range;
	_float fAttack_Range;


private:
	virtual void Free();

private:

	_float m_fAccTime;


};

