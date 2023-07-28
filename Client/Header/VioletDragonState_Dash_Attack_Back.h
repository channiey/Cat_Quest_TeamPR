#pragma once
#include "D:\SR_Team\Reference\Header\State.h"

class CVioletDragonState_Dash_Attack_Back : public CState
{

public:
	explicit			CVioletDragonState_Dash_Attack_Back(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CVioletDragonState_Dash_Attack_Back();


public:
	virtual HRESULT		Ready_State(CStateMachine* pOwner);
	virtual STATE_TYPE  Update_State(const _float& fTimeDelta);
	virtual void		LateUpdate_State();
	virtual void		Render_State();


	// ��� ����
	virtual STATE_TYPE		Key_Input(const _float& fTimeDelta);



public:
	static CVioletDragonState_Dash_Attack_Back* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);


private:

	_float			m_fAccTime;
	_bool			m_bAssault;

	
private:
	virtual void Free();



};

