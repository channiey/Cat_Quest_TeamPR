#pragma once
#include "Skill.h"


class CSkill_Monster_Beam : public CSkill
{
protected:
	explicit CSkill_Monster_Beam(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSkill_Monster_Beam(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CSkill_Monster_Beam(const CSkill_Monster_Beam& rhs);
	virtual ~CSkill_Monster_Beam();

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

	static CSkill_Monster_Beam* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);


protected:
	virtual void			Free();

};

