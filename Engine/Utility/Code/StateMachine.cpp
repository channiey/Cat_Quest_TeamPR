#include "..\..\Header\StateMachine.h"

CStateMachine::CStateMachine()
{

}

CStateMachine::CStateMachine(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev, COMPONENT_TYPE::STATEMACHINE)
{
}

CStateMachine::CStateMachine(const CStateMachine& rhs, CGameObject* _pOwnerObject)
	: CComponent(rhs, _pOwnerObject)
{
	Ready_StateMachine();
}

CStateMachine::~CStateMachine()
{
}


HRESULT CStateMachine::Ready_StateMachine()
{


	return S_OK;
}

_int CStateMachine::Update_Component(const _float& fTimeDelta)
{
	return 0;
}

CStateMachine* CStateMachine::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CStateMachine* pInstance = new CStateMachine(pGraphicDev);

	if (FAILED(pInstance->Ready_StateMachine()))
	{
		Safe_Release(pInstance);
		MSG_BOX("StateMachine Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent* CStateMachine::Clone(CGameObject* _pOwnerObject)
{
	return new CStateMachine(*this, _pOwnerObject);
}

void CStateMachine::Free()
{
	CComponent::Free();
}
