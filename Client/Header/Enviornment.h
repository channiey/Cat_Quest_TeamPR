#pragma once

#include "GameObject.h"

BEGIN(Engine)

class CTexture;

END

class CEnviornment : public Engine::CGameObject
{
protected:
	explicit CEnviornment(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CEnviornment(const CEnviornment& rhs);
	virtual ~CEnviornment();

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
	// static CEnviornment* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void			Free() override;

};

