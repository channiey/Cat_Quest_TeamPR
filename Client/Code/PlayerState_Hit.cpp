#include "PlayerState_Hit.h"

#include "Export_Function.h"

CPlayerState_Hit::CPlayerState_Hit(LPDIRECT3DDEVICE9 pGraphicDev)
	: CState(pGraphicDev)
{
}

CPlayerState_Hit::~CPlayerState_Hit()
{
}

HRESULT CPlayerState_Hit::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
		m_pOwner = pOwner;

	m_eState = STATE_TYPE::FRONT_HIT;
	m_fAcc = 0.f;

	return S_OK;
}

STATE_TYPE CPlayerState_Hit::Update_State(const _float& fTimeDelta)
{
	if (!m_bEnter)
	{
		m_bEnter = true;
	}

	STATE_TYPE eState = Key_Input(fTimeDelta);

	if (eState != m_eState)
		m_bEnter = false;
	return eState;
}

void CPlayerState_Hit::LateUpdate_State()
{
}

void CPlayerState_Hit::Render_State()
{
	//cout << "지금은 맞음" << endl;
}

STATE_TYPE CPlayerState_Hit::Key_Input(const _float& fTimeDelta)
{
	return m_eState;
}

CPlayerState_Hit* CPlayerState_Hit::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CPlayerState_Hit* pInstance = new CPlayerState_Hit(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Player HitState Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerState_Hit::Free()
{
	__super::Free();
}
