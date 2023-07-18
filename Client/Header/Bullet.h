#pragma once
#include "GameObject.h"

BEGIN(Engine)

class RcTex;
class CTexture;
class CAnimator;

END

class CBullet : public Engine:: CGameObject
{
protected:
	explicit CBullet(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CBullet(const CBullet& rhs);
	virtual ~CBullet();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT					Add_Component();

public:

	static					CBullet* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;


};

