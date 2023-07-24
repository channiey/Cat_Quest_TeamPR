#pragma once
#include "State.h"



class CVioletDragonState_ConvergingFire : public CState
{
public:
	explicit			CVioletDragonState_ConvergingFire(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CVioletDragonState_ConvergingFire();


public:
	virtual HRESULT		Ready_State(CStateMachine* pOwner);
	virtual STATE_TYPE  Update_State(const _float& fTimeDelta);
	virtual void		LateUpdate_State();
	virtual void		Render_State();


	// 사용 안함
	virtual STATE_TYPE		Key_Input(const _float& fTimeDelta);



public:
	static CVioletDragonState_ConvergingFire* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);


private:

	_float  m_fAccTime;

	_bool   m_bFirst;
	_bool   m_bSecond;
	_bool   m_bThird;
	_bool   m_bFourth;
	_bool   m_bFivth;
	_bool   m_bSixth;
	_bool   m_bSeventh;
	_bool   m_Eighth;


private:
	virtual void Free();




};

