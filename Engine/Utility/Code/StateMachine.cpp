#include "..\..\Header\StateMachine.h"
#include "..\..\Header\State.h"
#include "..\..\Header\Animator.h"

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
	m_StateMap = rhs.m_StateMap;
	m_pCurState = rhs.m_pCurState;
	m_pAnimator = rhs.m_pAnimator;
	m_pTransform = rhs.m_pTransform;
}	

CStateMachine::~CStateMachine()
{
}


HRESULT CStateMachine::Ready_StateMachine()
{
	return S_OK;
}

void CStateMachine::Update_StateMachine(const _float& fTimeDelta)
{
	STATE_TYPE eState = m_pCurState->Update_State(fTimeDelta);

	m_pAnimator->Update_Animator(fTimeDelta);

	if (eState != m_eCurState)
		Set_State(eState);
}

void CStateMachine::LateUpdate_StateMachine()
{
	m_pCurState->LateUpdate_State();
}

void CStateMachine::Render_StateMachine()
{
	m_pCurState->Render_State();
	m_pAnimator->Render_Animator();
}

_bool CStateMachine::Is_AnimationEnd()
{
	if (m_pAnimator->Get_CurAniamtion()->Is_End())
		return true;

	else
		return false;
}

void CStateMachine::Set_State(STATE_TYPE eState)
{
	auto	iter = find_if(m_StateMap.begin(), m_StateMap.end(), [&](const pair<STATE_TYPE, CState*>& pair) {
		return eState == pair.first;
		});

	if (iter == m_StateMap.end())
		return;

	m_pCurState = iter->second;
	m_eCurState = eState;

	if (m_pAnimator != nullptr)
		m_pAnimator->Set_Animation(eState);
}

HRESULT CStateMachine::Add_State(STATE_TYPE eState, CState* pState)
{
	if (nullptr == pState)
		return E_FAIL;

	m_StateMap.insert({ eState, pState });

	return S_OK;
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
	for_each(m_StateMap.begin(), m_StateMap.end(), CDeleteMap());
	m_StateMap.clear();

	CComponent::Free();
}
