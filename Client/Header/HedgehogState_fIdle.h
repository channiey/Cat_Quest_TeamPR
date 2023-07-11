#pragma once
#include "stdafx.h"
#include "State.h"
#include "Monster.h"

BEGIN(Engine)

END

class CHedgehogState_fIdle : public CState
{
public:
	explicit			CHedgehogState_fIdle(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CHedgehogState_fIdle();


public:
	virtual HRESULT		Ready_State(CStateMachine* pOwner);
	virtual STATE_TYPE  Update_State(const _float& fTimeDelta);
	virtual void		LateUpdate_State();
	virtual void		Render_State();


	// 사용 안함
	virtual STATE_TYPE		Key_Input(const _float& fTimeDelta);

public:
	static CHedgehogState_fIdle* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);


private:
	virtual void Free();



};

