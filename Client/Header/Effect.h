#pragma once

#include "GameObject.h"

BEGIN(Engine)

END

class CEffect :
	public CGameObject
{
private:
	explicit CEffect(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CEffect(const CEffect& rhs);
	virtual ~CEffect();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	HRESULT					Add_Component();

public:
	static CEffect*			Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void			Free() override;
};

