#pragma once
#include "GameObject.h"
#include "Pillar.h"

BEGIN(Engine)

class CCollider;

END

class CRock_Pillar2 : public CPillar
{
protected:
	explicit CRock_Pillar2(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRock_Pillar2(const CPillar& rhs);
	virtual ~CRock_Pillar2();

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
	static				CRock_Pillar2* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

