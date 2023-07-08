#include "PlayerState_bAttack1.h"

#include "Export_Function.h"

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

	return S_OK;
}

STATE_TYPE CPlayerState_bAttack1::Update_State(const _float& fTimeDelta)
{
	m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * 5.f);

	STATE_TYPE eState = Key_Input(fTimeDelta);

	if (m_pOwner->Is_AnimationEnd() && !m_bAttackContinue)
		return STATE_TYPE::BACK_IDLE;
	else if (m_pOwner->Is_AnimationEnd() && m_bAttackContinue)
	{
		m_bAttackContinue = false;
		return STATE_TYPE::BACK_ATTACK2;
	}
		

	return eState;
}

void CPlayerState_bAttack1::LateUpdate_State()
{
}

void CPlayerState_bAttack1::Render_State()
{
	cout << "지금은 뒤공격1" << endl;
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
