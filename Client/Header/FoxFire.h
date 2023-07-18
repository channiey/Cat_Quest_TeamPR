#pragma once
#include "Bullet.h"

BEGIN(Engine)

class CTexture;

END

class CFoxFire : public CBullet
{
protected:
	explicit CFoxFire(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CFoxFire(const CBullet& rhs);
	virtual ~CFoxFire();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT					Add_Component();

public:

	static					CFoxFire* Create(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);

protected:
	virtual void		Free() override;


};

