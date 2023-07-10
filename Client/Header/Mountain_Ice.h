#pragma once
#include "GameObject.h"
#include "Mountain.h"

BEGIN(Engine)

class CCollider;

END

class CMountain_Ice : public CMountain
{
protected:
	explicit CMountain_Ice(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMountain_Ice(const CMountain& rhs);
	virtual ~CMountain_Ice();

public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;

public:
	virtual void		OnCollision_Enter(CGameObject* _pColObj);
	virtual void		OnCollision_Stay(CGameObject* _pColObj);
	virtual void		OnCollision_Exit(CGameObject* _pColObj);

private:
	HRESULT				Add_Component();

public:
	static				CMountain_Ice* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

