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

public:
	virtual void			Set_InvenTrans(_float _fPosX, _float _fPosY)
	{
		m_ItemMatWorld._11 = 58.f * 0.3f;
		m_ItemMatWorld._22 = 118.f * 0.3f;
		m_ItemMatWorld._41 = _fPosX;
		m_ItemMatWorld._42 = _fPosY;
	}

private:
	HRESULT					Add_Component();

protected:
	
	STATINFO				m_eItemInfo;
	_matrix					m_ItemMatWorld;

protected:

	virtual void		Free() override;


};

