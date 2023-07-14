#pragma once
#include "Item.h"

BEGIN(Engine)

class CTexture;

END


class CItem_Weapon : public CItem
{
protected:
	explicit CItem_Weapon(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CItem_Weapon(const CItem& rhs);
	virtual ~CItem_Weapon();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT					Add_Component();


protected:

	virtual void		Free() override;


};

