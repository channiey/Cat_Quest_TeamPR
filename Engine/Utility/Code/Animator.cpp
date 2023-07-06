#include "..\..\Header\Animator.h"

CAnimator::CAnimator()
{

}

CAnimator::CAnimator(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev, COMPONENT_TYPE::ANIMATOR)
{
}

CAnimator::CAnimator(const CAnimator& rhs, CGameObject* _pOwnerObject)
	: CComponent(rhs, _pOwnerObject)
{
	Ready_Animator();
}

CAnimator::~CAnimator()
{
}


HRESULT CAnimator::Ready_Animator()
{


	return S_OK;
}

_int CAnimator::Update_Component(const _float& fTimeDelta)
{
	return 0;
}

CAnimator* CAnimator::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CAnimator* pInstance = new CAnimator(pGraphicDev);

	if (FAILED(pInstance->Ready_Animator()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Animator Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent* CAnimator::Clone(CGameObject* _pOwnerObject)
{
	return new CAnimator(*this, _pOwnerObject);
}

void CAnimator::Free()
{
	CComponent::Free();
}
