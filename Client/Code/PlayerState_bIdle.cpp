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
	if (!m_bEnter)
	{
		m_bEnter = true;
	}

	STATE_TYPE eState = Key_Input(fTimeDelta);

	if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Hit())
		eState = STATE_TYPE::FRONT_HIT;

	if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_StatInfo().bDead)
		eState = STATE_TYPE::FRONT_DIE;

	if (eState != m_eState)
		m_bEnter = false;
	return eState;
}

void CPlayerState_bIdle::LateUpdate_State()
{
}

void CPlayerState_bIdle::Render_State()
{
	//cout << "������ �ڼ��ֱ�" << endl;
}

STATE_TYPE CPlayerState_bIdle::Key_Input(const _float& fTimeDelta)
{
	if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
		return STATE_TYPE::FRONT_WALK;
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
		return STATE_TYPE::FRONT_WALK;
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
		return STATE_TYPE::BACK_WALK;
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
		return STATE_TYPE::FRONT_WALK;

	if (CInputDev::GetInstance()->Key_Down(VK_SPACE))
		return STATE_TYPE::BACK_ROLL;

	if (CInputDev::GetInstance()->Key_Down(VK_LBUTTON))
	{
		if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetLength() < 99)
		{
			if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetDir().z > 0)
				return STATE_TYPE::BACK_ATTACK;
			else
				return STATE_TYPE::FRONT_ATTACK;
		}
		else
			return STATE_TYPE::BACK_ATTACK;
	}


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
