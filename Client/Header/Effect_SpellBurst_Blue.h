#pragma once

#include "SkillEffect.h"


class CSpellBrust_Blue :
	public CSkillEffect
{
protected:
	explicit CSpellBrust_Blue(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CSpellBrust_Blue(const CEffect& rhs);
	virtual ~CSpellBrust_Blue();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	HRESULT					Add_Component();

public:
	static CSpellBrust_Blue* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

protected:
	virtual void			Free() override;
};

