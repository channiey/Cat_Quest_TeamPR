#include "PlayerState_bAttack.h"

#include "Export_Function.h"

#include "PlayerSlash.h"

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
	m_bIsTarget = false;

	return S_OK;
}

STATE_TYPE CPlayerState_bAttack::Update_State(const _float& fTimeDelta)
{
	if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_StatInfo().bDead)
	{
		m_bEnter = false;
		
		return STATE_TYPE::FRONT_DIE;
	}

	if (!m_bEnter)
	{
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_Attack(true);
		CEventMgr::GetInstance()->Add_Obj(L"Player_Slash_Chopping", CPlayerSlash::Create(
			m_pGraphicDev, m_pOwner->Get_OwnerObject(), false
		));

		if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_MonsterThere())
			m_bIsTarget = true;
		else
			m_bIsTarget = false;

		m_bAttackContinue = false;

		m_pOwner->Get_OwnerObject()->Get_Transform()->Reset_Lerp();

		m_bEnter = true;
	}

	if (!m_bIsTarget)
		m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * 6.f);
	else
	{
		if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTarget() != nullptr)
		{
			_vec3 vOut = m_pOwner->Get_OwnerObject()->Get_Transform()->Lerp(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Info(INFO::INFO_POS),
				static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTarget()->Get_Transform()->Get_Info(INFO::INFO_POS), 0.5f, fTimeDelta);
			if (vOut.y != -99)
			{
				m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Pos(_vec3{ vOut.x, m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Info(INFO::INFO_POS).y, vOut.z });
				static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetDir());
			}
		}

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
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetDir().z < 0.5f)
	{
		m_bEnter = false;
		return STATE_TYPE::FRONT_ATTACK1;
	}
	else if (m_pOwner->Is_AnimationEnd() && m_bAttackContinue)
	{
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

