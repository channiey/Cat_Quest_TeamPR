#pragma once
#include "BossProjectile.h"

BEGIN(Engine)

class CTexture;
class CCollider;

END
class CComBack_Bullet :  public CBossProjectile
{
protected:
	explicit CComBack_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner , _float fCombackTime);
	explicit CComBack_Bullet(const CProjectile& rhs);
	virtual ~CComBack_Bullet();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


	void					Comeback(const _float& fTimeDelta);

public:
	virtual void			OnCollision_Enter(CGameObject* _pColObj);
	virtual void			OnCollision_Stay(CGameObject* _pColObj);
	virtual void			OnCollision_Exit(CGameObject* _pColObj);



private:
	HRESULT					Add_Component();

public:

	static					CComBack_Bullet* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner, _float fCombackTime);


private:
	_vec3			m_vOriginPos;
	_bool			m_bComeBack;
	_bool			m_bStop;


	

	_float			m_fChaseTime;


	LERP_VEC3_INFO			m_tPosValue;




	_float					m_fDamage;  // Projectile Damage




	// Lerp Alpha
	_bool			m_bInit;
	LERP_FLOAT_INFO m_tAlpha;



protected:
	virtual void		Free() override;




};

