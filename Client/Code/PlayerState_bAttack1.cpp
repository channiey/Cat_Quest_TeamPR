#include "PlayerState_bAttack1.h"

#include "Export_Function.h"

#include "PlayerSlash.h"

CPlayerState_bAttack1::CPlayerState_bAttack1(LPDIRECT3DDEVICE9 pGraphicDev)
	: CState(pGraphicDev), m_bAttackContinue(false)
{
}

CPlayerState_bAttack1::~CPlayerState_bAttack1()
{
}

HRESULT CPlayerState_bAttack1::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
		m_pOwner = pOwner;

	m_eState = STATE_TYPE::BACK_ATTACK1;
	m_bIsTarget = false;
	return S_OK;
}

STATE_TYPE CPlayerState_bAttack1::Update_State(const _float& fTimeDelta)
{
	if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_StatInfo().bDead)
	{
		m_bEnter = false;
		return STATE_TYPE::FRONT_DIE;
	}

	if (!m_bEnter)
	{
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_Attack(true);
		CEventMgr::GetInstance()->Add_Obj(L"Player_Slash_Rising", CPlayerSlash::Create(
			m_pGraphicDev, m_pOwner->Get_OwnerObject(), true
		));

		if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_MonsterThere())
			m_bIsTarget = true;
		else
			m_bIsTarget = false;

		m_bAttackContinue = false;

		m_bEnter = true;
	}

	if (!m_bIsTarget)
		m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * 6.f);
	else
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetDir(), fTimeDelta * 6.f);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetDir());
	}

	STATE_TYPE eState = Key_Input(fTimeDelta);

	if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Hit())
	{
		m_bEnter = false;
		return STATE_TYPE::FRONT_HIT;
	}

	if (m_pOwner->Is_AnimationEnd() && !m_bAttackContinue)
	{
		m_bEnter = false;
		return STATE_TYPE::BACK_IDLE;
	}
	else if (m_pOwner->Is_AnimationEnd() && m_bAttackContinue && m_bIsTarget &&
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetDir().z < 0)
	{
		m_bEnter = false;
		return STATE_TYPE::FRONT_ATTACK2;
	}
	else if (m_pOwner->Is_AnimationEnd() && m_bAttackContinue)
	{
		m_bEnter = false;
		return STATE_TYPE::BACK_ATTACK2;
	}
		

	return eState;
}

void CPlayerState_bAttack1::LateUpdate_State()
{
}

void CPlayerState_bAttack1::Render_State()
{
	//cout << "지금은 뒤공격1" << endl;
}

STATE_TYPE CPlayerState_bAttack1::Key_Input(const _float& fTimeDelta)
{
	if (!m_pOwner->Is_AnimationEnd() && CInputDev::GetInstance()->Key_Down(VK_LBUTTON))
		m_bAttackContinue = true;

	return m_eState;
}

CPlayerState_bAttack1* CPlayerState_bAttack1::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CPlayerState_bAttack1* pInstance = new CPlayerState_bAttack1(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Player bAttack1State Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerState_bAttack1::Free()
{
	__super::Free();
}
