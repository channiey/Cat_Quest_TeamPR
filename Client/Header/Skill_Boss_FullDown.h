#pragma once
#include "Skill.h"
class CSkill_Boss_FullDown : public CSkill
{
protected:
	explicit CSkill_Boss_FullDown(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSkill_Boss_FullDown(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CSkill_Boss_FullDown(const CSkill_Boss_FullDown& rhs);
	virtual ~CSkill_Boss_FullDown();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT					Add_Component();


public:
	virtual HRESULT			Play();
	virtual HRESULT			LatePlay();
	virtual HRESULT			End();


public:

	static CSkill_Boss_FullDown* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

private:

	CEffect_Range_Quater*				m_pBaseRangeEffect;

protected:
	virtual void			Free();



};

