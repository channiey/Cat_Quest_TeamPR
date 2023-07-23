#pragma once
#include "BasicProjectile.h"
class CBlueStar_Bullet : public CBasicProjectile   // ȸ���ϴ� bullet 
{
protected:
	explicit CBlueStar_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget);
	explicit CBlueStar_Bullet(const CProjectile& rhs);
	virtual  ~CBlueStar_Bullet();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT					Add_Component();

public:

	static					CBlueStar_Bullet* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget);

private:
	_vec3			m_vOriginPos;


protected:
	virtual void		Free() override;


};

