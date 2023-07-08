#include "PlayerState_bWalk.h"

#include "Export_Function.h"

CPlayerState_bWalk::CPlayerState_bWalk(LPDIRECT3DDEVICE9 pGraphicDev)
	: CState(pGraphicDev)
{
}

CPlayerState_bWalk::~CPlayerState_bWalk()
{
}

HRESULT CPlayerState_bWalk::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
		m_pOwner = pOwner;

	m_eState = STATE_TYPE::BACK_WALK;

	return S_OK;
}

STATE_TYPE CPlayerState_bWalk::Update_State(const _float& fTimeDelta)
{
	STATE_TYPE eState = Key_Input(fTimeDelta);

	return eState;
}

void CPlayerState_bWalk::LateUpdate_State()
{
}

void CPlayerState_bWalk::Render_State()
{
	cout << "지금은 뒤걷기" << endl;
}

STATE_TYPE CPlayerState_bWalk::Key_Input(const _float& fTimeDelta)
{
    if (CInputDev::GetInstance()->Get_DIMouseState(DIM_LB))
        return STATE_TYPE::BACK_IDLE; // 나중에 공격으로 바꿀것

    if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Scale(_vec3{ 4.f, 4.f, 4.f });

        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(vec3.forward + vec3.right
            , fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
        return m_eState;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Scale(_vec3{ -4.f, 4.f, 4.f });

        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(vec3.forward + -vec3.right
            , fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
        return m_eState;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
    {
        return STATE_TYPE::FRONT_WALK;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
    {
        return STATE_TYPE::FRONT_WALK;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(DIR_FORWARD
            , fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
        return m_eState;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
    {
        return STATE_TYPE::FRONT_WALK;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
    {
        return STATE_TYPE::FRONT_WALK;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
    {
        return STATE_TYPE::FRONT_WALK;
    }


    return STATE_TYPE::BACK_IDLE;
}

CPlayerState_bWalk* CPlayerState_bWalk::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CPlayerState_bWalk* pInstance = new CPlayerState_bWalk(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Player BackWalk State Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerState_bWalk::Free()
{
	__super::Free();
}
