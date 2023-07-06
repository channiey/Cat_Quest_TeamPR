#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CAnimator : public CComponent
{
private:
	explicit CAnimator();
	explicit CAnimator(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CAnimator(const CAnimator& rhs, CGameObject* _pOwnerObject);
	virtual ~CAnimator();

public:


public:
	HRESULT					Ready_Animator();
	virtual _int			Update_Component(const _float& fTimeDelta);


private:

public:
	static CAnimator*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*		Clone(CGameObject* _pOwnerObject);

private:
	virtual void			Free();

};

END