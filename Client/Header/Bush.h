#pragma once
#include "Environment.h"

BEGIN(Engine)

class CTexture;

END

class CBush : public CEnvironment
{
protected:
	explicit CBush(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBush(const CBush& rhs);
	virtual ~CBush();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	HRESULT					Add_Component();

protected:
	virtual void			Free() override;

};

