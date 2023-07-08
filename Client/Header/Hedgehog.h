#pragma once
#include "GameObject.h"
#include "Monster.h"

BEGIN(Engine)

class CCubeCol;
class CCollider;

END

class CHedgehog : public CMonster
{

protected:
		
	explicit CHedgehog(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CHedgehog(const CMonster& rhs);
	virtual ~CHedgehog();


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

private:
	void				Move(const _float& fTimeDelta);

public:
	static				CHedgehog* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;


};

