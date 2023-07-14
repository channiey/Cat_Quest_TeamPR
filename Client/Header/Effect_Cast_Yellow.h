#pragma once

#include "SkillEffect.h"


class CCast_Yellow :
	public CSkillEffect
{
protected:
	explicit CCast_Yellow(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CCast_Yellow(const CEffect& rhs);
	virtual ~CCast_Yellow();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	HRESULT					Add_Component();

public:
	static CCast_Yellow* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

protected:
	virtual void			Free() override;
};

