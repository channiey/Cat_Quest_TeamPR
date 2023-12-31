#pragma once
#include "stdafx.h"
#include "State.h"
#include "Monster.h"

BEGIN(Engine)

END

class CHedgehogState_Patrol : public CState
{
public:
	explicit			CHedgehogState_Patrol(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CHedgehogState_Patrol();


public:
	virtual HRESULT		Ready_State(CStateMachine* pOwner);
	virtual STATE_TYPE  Update_State(const _float& fTimeDelta);
	virtual void		LateUpdate_State();
	virtual void		Render_State();


	// 사용 안함
	virtual STATE_TYPE		Key_Input(const _float& fTimeDelta);


public:
	static CHedgehogState_Patrol* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);


private:
	virtual void Free();

private:

	_float m_fAccTime;  // 누적시간

	_float  m_fPatrolRange;
	_float  m_fChaseRange;
	_float  m_fAttackRange;
	_float  m_fComeBackRange;
	_float  m_fPlayerTargetRange;



};

