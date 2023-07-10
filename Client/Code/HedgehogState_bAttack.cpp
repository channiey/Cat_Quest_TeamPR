#include "HedgehogState_bAttack.h"
#include "Export_Function.h"


CHedgehogState_bAttack::CHedgehogState_bAttack(LPDIRECT3DDEVICE9 pGraphicDev)
    :CState(pGraphicDev)
{
}

CHedgehogState_bAttack::~CHedgehogState_bAttack()
{
}

HRESULT CHedgehogState_bAttack::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
	{
		m_pOwner = pOwner;
	}

	m_eState = STATE_TYPE::BACK_ATTACK;

	return S_OK;
}

STATE_TYPE CHedgehogState_bAttack::Update_State(const _float& fTimeDelta)
{
	// юс╫ц
	STATE_TYPE eState = Key_Input(fTimeDelta);



	if (m_pOwner->Is_AnimationEnd())
	{
		return STATE_TYPE::BACK_IDLE;
	}


	return eState;
}

void CHedgehogState_bAttack::LateUpdate_State()
{
}

void CHedgehogState_bAttack::Render_State()
{
}

STATE_TYPE CHedgehogState_bAttack::Key_Input(const _float& fTimeDelta)
{

	return m_eState;
}

CHedgehogState_bAttack* CHedgehogState_bAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CHedgehogState_bAttack* pInstance = new CHedgehogState_bAttack(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Hedgehog bAttackState Create Failed");
		return nullptr;

	}

	return pInstance;
}

void CHedgehogState_bAttack::Free()
{
	__super::Free();
}
