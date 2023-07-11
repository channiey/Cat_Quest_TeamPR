#pragma once
#include "Environment.h"

BEGIN(Engine)

class CTexture;

END

class CTower : public CEnvironment
{
protected:
	explicit CTower(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTower(const CTower& rhs);
	virtual ~CTower();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	HRESULT					Add_Component();

protected:
	CTexture* m_pTextureCom;

protected:
	virtual void			Free() override;

};
