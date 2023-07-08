#pragma once
#include "GameObject.h"
#include "Enviornment.h"

BEGIN(Engine)

class CRcCol;
class CCollider;

END

class CMountain : public CEnviornment
{
protected:
	explicit CMountain(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMountain(const CEnviornment& rhs);
	virtual ~CMountain();

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
	static				CMountain* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;
};
