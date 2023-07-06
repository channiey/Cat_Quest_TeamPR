#pragma once

#include "GameObject.h"

BEGIN(Engine)

END

class CNpc :
	public CGameObject
{
private:
	explicit CNpc(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CNpc(const CNpc& rhs);
	virtual ~CNpc();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	HRESULT					Add_Component();

public:
	static CNpc*			Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void			Free() override;
};

