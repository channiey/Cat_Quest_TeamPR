#include "PlayerState_fAttack2.h"

#include "Export_Function.h"

#include "PlayerSlash.h"

CPlayerState_fAttack2::CPlayerState_fAttack2(LPDIRECT3DDEVICE9 pGraphicDev)
	: CState(pGraphicDev)
{
}

CPlayerState_fAttack2::~CPlayerState_fAttack2()
{
}

HRESULT CPlayerState_fAttack2::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
		m_pOwner = pOwner;

	m_eState = STATE_TYPE::FRONT_ATTACK2;
	m_bIsTarget = false;
	return S_OK;
}

STATE_TYPE CPlayerState_fAttack2::Update_State(const _float& fTimeDelta)
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
			m_pGraphicDev, m_pOwner->Get_OwnerObject(), false
		));

		if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_MonsterThere())
			m_bIsTarget = true;
		else
			m_bIsTarget = false;

		m_bEnter = true;
	}

	if (!m_bIsTarget)
		m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * 6.f);
	else
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetDir(), fTimeDelta * 0.15f);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetDir());
	}
		


	if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Hit())
	{
		m_bEnter = false;		
		CCameraMgr::GetInstance()->Start_Lerp(CAMERA_LEPR_MODE::PLAYER_ATK_TO_IDL); // << Test
		return STATE_TYPE::FRONT_HIT;
	}

	if (m_pOwner->Is_AnimationEnd())
	{
		m_bEnter = false;
		CCameraMgr::GetInstance()->Start_Lerp(CAMERA_LEPR_MODE::PLAYER_ATK_TO_IDL); // << Test
		return STATE_TYPE::FRONT_IDLE;
	}



	CCameraMgr::GetInstance()->Start_Lerp(CAMERA_LEPR_MODE::PLAYER_ATK_TO_IDL); // << Test
	return m_eState;
}

void CPlayerState_fAttack2::LateUpdate_State()
{
}

void CPlayerState_fAttack2::Render_State()
{
	//cout << "지금은 앞공격2" << endl;
}

STATE_TYPE CPlayerState_fAttack2::Key_Input(const _float& fTimeDelta)
{
	return m_eState;
}

CPlayerState_fAttack2* CPlayerState_fAttack2::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CPlayerState_fAttack2* pInstance = new CPlayerState_fAttack2(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Player fAttack2State Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerState_fAttack2::Free()
{
	__super::Free();
}
