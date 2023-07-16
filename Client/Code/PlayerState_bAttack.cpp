#include "PlayerState_bAttack.h"

#include "Export_Function.h"

CPlayerState_bAttack::CPlayerState_bAttack(LPDIRECT3DDEVICE9 pGraphicDev)
	: CState(pGraphicDev), m_bAttackContinue(false)
{
}

CPlayerState_bAttack::~CPlayerState_bAttack()
{
}

HRESULT CPlayerState_bAttack::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
		m_pOwner = pOwner;

	m_eState = STATE_TYPE::BACK_ATTACK;

	return S_OK;
}

STATE_TYPE CPlayerState_bAttack::Update_State(const _float& fTimeDelta)
{
	if (!m_bEnter)
	{
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_Attack(true);
		m_bEnter = true;
	}

	m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * 6.f);

	STATE_TYPE eState = Key_Input(fTimeDelta);

	if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Hit())
	{
		m_bAttackContinue = false;
		m_bEnter = false;
		return STATE_TYPE::FRONT_HIT;
	}

	if (m_pOwner->Is_AnimationEnd() && !m_bAttackContinue)
	{
		m_bEnter = false;
		return STATE_TYPE::BACK_IDLE;
	}

	else if (m_pOwner->Is_AnimationEnd() && m_bAttackContinue)
	{
		m_bAttackContinue = false;
		m_bEnter = false;
		return STATE_TYPE::BACK_ATTACK1;
	}
		

	return eState;
}

void CPlayerState_bAttack::LateUpdate_State()
{
}

void CPlayerState_bAttack::Render_State()
{
	//cout << "지금은 뒤공격" << endl;
}

STATE_TYPE CPlayerState_bAttack::Key_Input(const _float& fTimeDelta)
{
	if (!m_pOwner->Is_AnimationEnd() && CInputDev::GetInstance()->Key_Down(VK_LBUTTON))
		m_bAttackContinue = true;

	return m_eState;
}

CPlayerState_bAttack* CPlayerState_bAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CPlayerState_bAttack* pInstance = new CPlayerState_bAttack(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Player bAttackState Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerState_bAttack::Free()
{
	__super::Free();
}

