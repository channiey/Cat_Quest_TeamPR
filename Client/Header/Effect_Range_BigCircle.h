#pragma once

#include "SkillEffect.h"

class CEffect_Range_BigCircle :
	public CSkillEffect
{
protected:
	explicit CEffect_Range_BigCircle(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CEffect_Range_BigCircle(const CEffect& rhs);
	virtual ~CEffect_Range_BigCircle();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	HRESULT					Add_Component();

public:
	static CEffect_Range_BigCircle* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

protected:
	virtual void			Free() override;
};

