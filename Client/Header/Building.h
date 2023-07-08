#pragma once

#include "GameObject.h"
#include "Enviornment.h"

BEGIN(Engine)

class CRcCol;
class CCollider;

END

class CBuilding : public CEnviornment
{
protected:
	explicit CBuilding(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos = {4.f, 4.f, 4.f});
	explicit CBuilding(const CEnviornment& rhs);
	virtual ~CBuilding();

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
	static				CBuilding* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static				CBuilding* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos);

protected:
	virtual void		Free() override;

};

