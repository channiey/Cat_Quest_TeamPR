#pragma once
#include "Flag.h"

BEGIN(Engine)

END

class CFlagStart : public CFlag
{
protected:
	explicit CFlagStart(LPDIRECT3DDEVICE9 pGraphicDev, CFlagOwner* _owner);
	explicit CFlagStart(const CFlag& rhs);
	virtual ~CFlagStart();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	void					Set_Texture(const FLAG_TAG& _eID);

private:
	HRESULT		Add_Component();


private:

public:
	static				CFlagStart* Create(LPDIRECT3DDEVICE9 pGraphicDev, CFlagOwner* _owner);

protected:
	virtual void		Free() override;


};

