#include "PlayerState_fAttack.h"

#include "Export_Function.h"

#include "PlayerSlash.h"

CPlayerState_fAttack::CPlayerState_fAttack(LPDIRECT3DDEVICE9 pGraphicDev)
	: CState(pGraphicDev), m_bAttackContinue(false)
{
}

CPlayerState_fAttack::~CPlayerState_fAttack()
{
}

HRESULT CPlayerState_fAttack::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
		m_pOwner = pOwner;

	m_eState = STATE_TYPE::FRONT_ATTACK;

	return S_OK;
}

STATE_TYPE CPlayerState_fAttack::Update_State(const _float& fTimeDelta)
{
	if (!m_bEnter)
	{
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_Attack(true);
		CEventMgr::GetInstance()->Add_Obj(L"Player_Slash_Chopping", CPlayerSlash::Create(
			m_pGraphicDev, m_pOwner->Get_OwnerObject(), false
		));
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
		return STATE_TYPE::FRONT_IDLE;
	}
		
	else if (m_pOwner->Is_AnimationEnd() && m_bAttackContinue)
	{
		m_bAttackContinue = false;
		m_bEnter = false;
		return STATE_TYPE::FRONT_ATTACK1;
	}
		
	return eState;
}

void CPlayerState_fAttack::LateUpdate_State()
{
}

void CPlayerState_fAttack::Render_State()
{
	//cout << "지금은 앞공격" << endl;
}

STATE_TYPE CPlayerState_fAttack::Key_Input(const _float& fTimeDelta)
{
	if (!m_pOwner->Is_AnimationEnd() && CInputDev::GetInstance()->Key_Down(VK_LBUTTON))
		m_bAttackContinue = true;

	return m_eState;
}

CPlayerState_fAttack* CPlayerState_fAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CPlayerState_fAttack* pInstance = new CPlayerState_fAttack(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Player fAttackState Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerState_fAttack::Free()
{
	__super::Free();
}

