#pragma once
#include "BossProjectile.h"

BEGIN(Engine)

class CTexture;
class CCollider;

END
class CConvergingFire_Bullet :  public CBossProjectile
{
protected:
	explicit CConvergingFire_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner , _float fTimeDelta);
	explicit CConvergingFire_Bullet(const CProjectile& rhs);
	virtual ~CConvergingFire_Bullet();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT					Add_Component();

public:

	static					CConvergingFire_Bullet* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner, _float fTimeDelta);




protected:
	virtual void		Free() override;




};

