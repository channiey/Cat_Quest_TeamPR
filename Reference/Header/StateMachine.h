#pragma once

#include "Component.h"
#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CStateMachine : public CComponent
{
private:
	explicit CStateMachine();
	explicit CStateMachine(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CStateMachine(const CStateMachine& rhs, CGameObject* _pOwnerObject);
	virtual ~CStateMachine();

public:
	

public:
	HRESULT					Ready_StateMachine();
	virtual _int			Update_Component(const _float& fTimeDelta);


private:

public:
	static CStateMachine*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*		Clone(CGameObject* _pOwnerObject);

private:
	virtual void			Free();

};

END