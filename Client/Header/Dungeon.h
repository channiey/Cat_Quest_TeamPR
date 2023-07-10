#pragma once
#include "Environment.h"

BEGIN(Engine)

class CTexture;

END

class CDungeon : public CEnvironment
{
protected:
	explicit CDungeon(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CDungeon(const CDungeon& rhs);
	virtual ~CDungeon();

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

