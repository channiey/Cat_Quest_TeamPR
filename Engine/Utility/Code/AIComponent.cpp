#include "..\..\Header\AIComponent.h"
#include "GameObject.h"



CAIComponent::CAIComponent(LPDIRECT3DDEVICE9 pGraphicDev)
{
}

CAIComponent::CAIComponent(const CAIComponent& rhs, CGameObject* _pOwnerObject)
{
}

CAIComponent::~CAIComponent()
{
}

void CAIComponent::Chase_Target(const CGameObject* _pTargetObject, const _float& fTimeDelta, const _float& fSpeed)
{

}

void CAIComponent::Random_Move(const _float& fTimeDelta, const _float& fSpeed)
{


}

CAIComponent* CAIComponent::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return nullptr;
}

CComponent* CAIComponent::Clone(CGameObject* _pOwnerObject)
{
	return nullptr;
}

void CAIComponent::Free()
{
}
