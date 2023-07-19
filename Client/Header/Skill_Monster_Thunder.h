#pragma once
#include "Skill.h"


class CSkill_Monster_Thunder : public CSkill
{
protected:
	explicit CSkill_Monster_Thunder(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSkill_Monster_Thunder(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CSkill_Monster_Thunder(const CSkill_Monster_Thunder& rhs);
	virtual ~CSkill_Monster_Thunder();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT					Add_Component();


public:
	virtual HRESULT			Play();
	virtual HRESULT			End();


public:

	static CSkill_Monster_Thunder* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);


protected:
	virtual void			Free();

};

