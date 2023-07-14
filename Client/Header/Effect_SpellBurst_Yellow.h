#pragma once

#include "SkillEffect.h"

class CSpellBrust_Yellow :
	public CSkillEffect
{
protected:
	explicit CSpellBrust_Yellow(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CSpellBrust_Yellow(const CEffect& rhs);
	virtual ~CSpellBrust_Yellow();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	HRESULT					Add_Component();

public:
	static CSpellBrust_Yellow* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

protected:
	virtual void			Free() override;
};

