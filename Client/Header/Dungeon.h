#pragma once
#include "GameObject.h"
#include "Enviornment.h"

BEGIN(Engine)
class CRcCol;
class CCollider;
END

class CDungeon : public CEnviornment
{
protected:
	explicit CDungeon(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CDungeon(const CEnviornment& rhs);
	virtual ~CDungeon();

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
	static				CDungeon* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;


};

