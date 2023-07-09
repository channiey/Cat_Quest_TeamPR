#include "PlayerState_bAttack2.h"

#include "Export_Function.h"

CPlayerState_bAttack2::CPlayerState_bAttack2(LPDIRECT3DDEVICE9 pGraphicDev)
	: CState(pGraphicDev)
{
}

CPlayerState_bAttack2::~CPlayerState_bAttack2()
{
}

HRESULT CPlayerState_bAttack2::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
		m_pOwner = pOwner;

	m_eState = STATE_TYPE::BACK_ATTACK2;

	return S_OK;
}

STATE_TYPE CPlayerState_bAttack2::Update_State(const _float& fTimeDelta)
{
	m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * 5.f);


	if (m_pOwner->Is_AnimationEnd())
		return STATE_TYPE::BACK_IDLE;
	else
		return m_eState;
}

void CPlayerState_bAttack2::LateUpdate_State()
{
}

void CPlayerState_bAttack2::Render_State()
{
	//cout << "지금은 뒤공격2" << endl;
}

STATE_TYPE CPlayerState_bAttack2::Key_Input(const _float& fTimeDelta)
{
	return m_eState;
}

CPlayerState_bAttack2* CPlayerState_bAttack2::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CPlayerState_bAttack2* pInstance = new CPlayerState_bAttack2(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Player bAttack2State Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerState_bAttack2::Free()
{
	__super::Free();
}

