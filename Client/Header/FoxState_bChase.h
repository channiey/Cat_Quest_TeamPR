#pragma once
#include "stdafx.h"
#include "State.h"
#include "Monster.h"

BEGIN(Engine)

END

class CFoxState_bChase : public CState
{
public:
	explicit			CFoxState_bChase(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CFoxState_bChase();


public:
	virtual HRESULT		Ready_State(CStateMachine* pOwner);
	virtual STATE_TYPE  Update_State(const _float& fTimeDelta);
	virtual void		LateUpdate_State();
	virtual void		Render_State();


	// ��� ����
	virtual STATE_TYPE		Key_Input(const _float& fTimeDelta);



public:
	static CFoxState_bChase* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);


private:
	virtual void Free();

private:

	_float m_fAccTime;

	_float  m_fPatrolRange;
	_float  m_fChaseRange;
	_float  m_fAttackRange;
	_float  m_fComeBackRange;
	_float  m_fPlayerTargetRange;

};

