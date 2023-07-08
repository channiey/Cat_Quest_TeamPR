#include "PlayerState_fAttack2.h"

#include "Export_Function.h"

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

	return S_OK;
}

STATE_TYPE CPlayerState_fAttack2::Update_State(const _float& fTimeDelta)
{
	m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * 5.f);


	if (m_pOwner->Is_AnimationEnd())
		return STATE_TYPE::FRONT_IDLE;
	else 
		return m_eState;
}

void CPlayerState_fAttack2::LateUpdate_State()
{
}

void CPlayerState_fAttack2::Render_State()
{
	cout << "지금은 앞공격2" << endl;
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
