#pragma once

#include "SkillEffect.h"

class CCast_Blue :
    public CSkillEffect
{
protected:
	explicit CCast_Blue(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CCast_Blue(const CEffect& rhs);
	virtual ~CCast_Blue();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	HRESULT					Add_Component();

public:
	static CCast_Blue* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

protected:
	virtual void			Free() override;
};

