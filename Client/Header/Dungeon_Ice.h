#pragma once
#include "GameObject.h"
#include "Dungeon.h"

BEGIN(Engine)

class CCollider;

END

class CDungeon_Ice : public CDungeon
{
protected:
	explicit CDungeon_Ice(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CDungeon_Ice(const CDungeon& rhs);
	virtual ~CDungeon_Ice();

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
	static				CDungeon_Ice* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

