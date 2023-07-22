#pragma once
#include "BasicProjectile.h"
class CDagger : public CBasicProjectile   // ȸ���ϴ� bullet 
{
protected:
	explicit CDagger(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget);
	explicit CDagger(const CProjectile& rhs);
	virtual  ~CDagger();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT					Add_Component();

public:

	static					CDagger* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget);




protected:
	virtual void		Free() override;


};

