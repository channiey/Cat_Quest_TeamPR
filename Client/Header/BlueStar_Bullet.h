#pragma once
#include "BasicProjectile.h"
class CBlueStar_Bullet : public CBasicProjectile   //  Shooting Star Pattern Use
{
protected:
	explicit CBlueStar_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner);
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

	static					CBlueStar_Bullet* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner);

private:
	_vec3			m_vOriginPos;
	_bool			m_bChase;

	_bool			m_bInit;

	LERP_FLOAT_INFO m_tAlpha;

protected:
	virtual void		Free() override;


};

