#pragma once

#include "GameObject.h"

BEGIN(Engine)

class CTexture;

END

class CArgObject : public Engine::CGameObject
{
protected:
	explicit CArgObject(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CArgObject(const CArgObject& rhs);
	virtual ~CArgObject();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	HRESULT					Add_Component();

protected:
	CTexture* m_pTextureCom = nullptr;

public:
	// static CArgObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void			Free() override;

};

