#include "PlayerState_fIdle.h"

#include "Export_Function.h"

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

	m_eState = STATE_TYPE::FRONT_IDLE;

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
	//cout << "지금은 앞서있기" << endl;
}

STATE_TYPE CPlayerState_fIdle::Key_Input(const _float& fTimeDelta)
{
	if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
		return STATE_TYPE::FRONT_WALK;
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
		return STATE_TYPE::FRONT_WALK;
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
		return STATE_TYPE::BACK_WALK;
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
		return STATE_TYPE::FRONT_WALK;

	
	// 구르기
	if (CInputDev::GetInstance()->Key_Down(VK_SPACE))
		return STATE_TYPE::FRONT_ROLL;

	// 공격
	if (CInputDev::GetInstance()->Key_Down(VK_LBUTTON))
		return STATE_TYPE::FRONT_ATTACK; 

		return m_eState;
}

CPlayerState_fIdle* CPlayerState_fIdle::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CPlayerState_fIdle* pInstance = new CPlayerState_fIdle(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Player fIdleState Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerState_fIdle::Free()
{
	__super::Free();
}
