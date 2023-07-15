#pragma once

#include "Skill.h"

class CFireSkill :
    public CSkill
{
protected:
	explicit CFireSkill(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	virtual ~CFireSkill();

public:
	virtual HRESULT			Ready_Skill() override;
	virtual void			Update_Skill() override;
	virtual void			LateUpdate_Skill() override;

public:
	virtual HRESULT			Cast(); // 스킬 시전 (가상화)

private:
	HRESULT					Add_SkillEffect();

protected:
	LPDIRECT3DDEVICE9		m_pGraphicDev;

public:
	static CFireSkill* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

private:
	virtual void			Free();
};

