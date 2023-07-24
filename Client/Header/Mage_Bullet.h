#pragma once
#include "BasicProjectile.h"

BEGIN(Engine)

class CTexture;
class CCollider;

END

class CMage_Bullet : public CBasicProjectile    // 타겟을 따라다니며 이동 하는 Bullet
{
protected:
	explicit CMage_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget,CGameObject* pOwner);
	explicit CMage_Bullet(const CProjectile& rhs);
	virtual ~CMage_Bullet();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

	CGameObject*			Get_MageBall_Owner() { return m_pBallOwner; }
	_float&					Get_BallDamage()	{ return m_fDamage; }

public:
	virtual void			OnCollision_Enter(CGameObject* _pColObj);
	virtual void			OnCollision_Stay(CGameObject* _pColObj);
	virtual void			OnCollision_Exit(CGameObject* _pColObj);

private:
	HRESULT					Add_Component();

private:
	_float					m_fDamage;
	CGameObject*			m_pBallOwner;

public:

	static					CMage_Bullet* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner);




protected:
	virtual void		Free() override;


};

