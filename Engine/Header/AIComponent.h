#pragma once
#include "Component.h"
#include "GameObject.h"

BEGIN(Engine)


class ENGINE_DLL CAIComponent : public CComponent
{
private: 
	
	explicit CAIComponent(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CAIComponent(const CAIComponent& rhs, CGameObject* _pOwnerObject);
	virtual ~CAIComponent();


public:

	// ai 이동 구현

	void	Chase_Target(const CGameObject* _pOwnerObject, const _float& fTimeDelta, const _float& fSpeed);
	void	Random_Move(const _float& fTimeDelta, const _float& fSpeed);



public:
	static	CAIComponent*			Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*		Clone(CGameObject* _pOwnerObject);


private:

	virtual void Free();


};

END