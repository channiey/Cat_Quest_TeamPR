#include "PlayerState_fAttack1.h"

#include "Export_Function.h"

#include "PlayerSlash.h"

CPlayerState_fAttack1::CPlayerState_fAttack1(LPDIRECT3DDEVICE9 pGraphicDev)
	: CState(pGraphicDev), m_bAttackContinue(false)
{
}

CPlayerState_fAttack1::~CPlayerState_fAttack1()
{
}

HRESULT CPlayerState_fAttack1::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
		m_pOwner = pOwner;

	m_eState = STATE_TYPE::FRONT_ATTACK1;
	m_bIsTarget = false;
	return S_OK;
}

STATE_TYPE CPlayerState_fAttack1::Update_State(const _float& fTimeDelta)
{
	if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_StatInfo().bDead)
	{
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_ATK_TO_IDL);
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
		m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetDir(), fTimeDelta * 0.1f);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetDir());
	}

	STATE_TYPE eState = Key_Input(fTimeDelta);

	if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Hit())
	{
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_ATK_TO_IDL);
		m_bEnter = false;
		return STATE_TYPE::FRONT_HIT;
	}

	if (m_pOwner->Is_AnimationEnd() && !m_bAttackContinue)
	{
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_ATK_TO_IDL);
		m_bEnter = false;
		return STATE_TYPE::FRONT_IDLE;
	}
	else if (m_pOwner->Is_AnimationEnd() && m_bAttackContinue && m_bIsTarget &&
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetDir().z > 0.5f)
	{
		m_bEnter = false;
		return STATE_TYPE::BACK_ATTACK2;
	}
	else if (m_pOwner->Is_AnimationEnd() && m_bAttackContinue)
	{
		m_bEnter = false;
		return STATE_TYPE::FRONT_ATTACK2;
	}
		
	

	return eState;
}

void CPlayerState_fAttack1::LateUpdate_State()
{
}

void CPlayerState_fAttack1::Render_State()
{
	//cout << "지금은 앞공격1" << endl;
}

STATE_TYPE CPlayerState_fAttack1::Key_Input(const _float& fTimeDelta)
{
	if (!m_pOwner->Is_AnimationEnd() && CInputDev::GetInstance()->Key_Down(VK_LBUTTON))
		m_bAttackContinue = true;


	return m_eState;
}

CPlayerState_fAttack1* CPlayerState_fAttack1::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CPlayerState_fAttack1* pInstance = new CPlayerState_fAttack1(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Player fAttack1State Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerState_fAttack1::Free()
{
	__super::Free();
}

