#pragma once
#include "BasicProjectile.h"

BEGIN(Engine)

class CTexture;
class CCollider;

END

class CFoxFire : public CBasicProjectile    // 정해진 방향으로 이동 하는 Bullet
{
protected:
	explicit CFoxFire(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, _vec3 _vDir, CGameObject* pOwner);
	explicit CFoxFire(const CProjectile& rhs);
	virtual ~CFoxFire();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT					Add_Component();

public:

	static					CFoxFire* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, _vec3 _vDir, CGameObject* pOwner);

private:

	LERP_FLOAT_INFO      m_tAlpha;

	_bool				m_bInit;
	_bool				m_bEnd;
protected:
	virtual void		Free() override;


};

