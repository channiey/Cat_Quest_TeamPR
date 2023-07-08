#include "PlayerState_bIdle.h"

#include "Export_Function.h"

CPlayerState_bIdle::CPlayerState_bIdle(LPDIRECT3DDEVICE9 pGraphicDev)
	: CState(pGraphicDev)
{
}

CPlayerState_bIdle::~CPlayerState_bIdle()
{
}

HRESULT CPlayerState_bIdle::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
		m_pOwner = pOwner;

	m_eState = STATE_TYPE::BACK_IDLE;

	return S_OK;
}

STATE_TYPE CPlayerState_bIdle::Update_State(const _float& fTimeDelta)
{
	STATE_TYPE eState = Key_Input(fTimeDelta);

	return eState;
}

void CPlayerState_bIdle::LateUpdate_State()
{
}

void CPlayerState_bIdle::Render_State()
{
	cout << "지금은 뒤서있기" << endl;
}

STATE_TYPE CPlayerState_bIdle::Key_Input(const _float& fTimeDelta)
{
	if (CInputDev::GetInstance()->Key_Down('A'))
		return STATE_TYPE::FRONT_WALK;
	else if (CInputDev::GetInstance()->Key_Down('D'))
		return STATE_TYPE::FRONT_WALK;
	else if (CInputDev::GetInstance()->Key_Down('W'))
		return STATE_TYPE::BACK_WALK;
	else if (CInputDev::GetInstance()->Key_Down('S'))
		return STATE_TYPE::FRONT_WALK;
	else
		return m_eState;
}

CPlayerState_bIdle* CPlayerState_bIdle::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CPlayerState_bIdle* pInstance = new CPlayerState_bIdle(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Player BackIdle State Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerState_bIdle::Free()
{
	__super::Free();
}
