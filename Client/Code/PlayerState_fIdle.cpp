#include "PlayerState_fIdle.h"

CPlayerState_fIdle::CPlayerState_fIdle(LPDIRECT3DDEVICE9 pGraphicDev)
	: CState(pGraphicDev)
{
}

CPlayerState_fIdle::~CPlayerState_fIdle()
{
}

HRESULT CPlayerState_fIdle::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
		m_pOwner = pOwner;

	m_eState = STATE_TYPE::IDLE;

	return S_OK;
}

STATE_TYPE CPlayerState_fIdle::Update_State(const _float& fTimeDelta)
{
	STATE_TYPE eState = Key_Input(fTimeDelta);

	return eState;
}

void CPlayerState_fIdle::LateUpdate_State()
{
}

void CPlayerState_fIdle::Render_State()
{
	cout << "지금은 서있기" << endl;
}

STATE_TYPE CPlayerState_fIdle::Key_Input(const _float& fTimeDelta)
{
	if (GetAsyncKeyState('N'))
		return STATE_TYPE::WALK;
	else
		return m_eState;
}

CPlayerState_fIdle* CPlayerState_fIdle::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CPlayerState_fIdle* pInstance = new CPlayerState_fIdle(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Player IdleState Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerState_fIdle::Free()
{
	__super::Free();
}
