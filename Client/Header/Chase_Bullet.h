#pragma once
#include "BasicProjectile.h"

BEGIN(Engine)

class CTexture;
class CCollider;

END

class CChase_Bullet : public CBasicProjectile    // Ÿ���� ����ٴϸ� �̵� �ϴ� Bullet
{
protected:
	explicit CChase_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget);
	explicit CChase_Bullet(const CProjectile& rhs);
	virtual ~CChase_Bullet();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT					Add_Component();

public:

	static					CChase_Bullet* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget);




protected:
	virtual void		Free() override;


};
