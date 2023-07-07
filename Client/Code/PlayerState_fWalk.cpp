#include "PlayerState_fWalk.h"

#include "Export_Function.h"

CPlayerState_fWalk::CPlayerState_fWalk(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
{
}

CPlayerState_fWalk::~CPlayerState_fWalk()
{
}

HRESULT CPlayerState_fWalk::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
        m_pOwner = pOwner;

    m_eState = STATE_TYPE::WALK;

    return S_OK;
}

STATE_TYPE CPlayerState_fWalk::Update_State(const _float& fTimeDelta)
{
    STATE_TYPE eState = Key_Input(fTimeDelta);

    return eState;
}

void CPlayerState_fWalk::LateUpdate_State()
{
}

void CPlayerState_fWalk::Render_State()
{
   cout << "Áö±ÝÀº °È±â" << endl;
}

STATE_TYPE CPlayerState_fWalk::Key_Input(const _float& fTimeDelta)
{
    if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(vec3.forward + vec3.right
            , fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
        return m_eState;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(vec3.forward + -vec3.right
            , fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
        return m_eState;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(-vec3.forward + vec3.right
            , fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
        return m_eState;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(-vec3.forward - vec3.right
            , fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
        return m_eState;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(DIR_FORWARD
            , fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
        return m_eState;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(DIR_FORWARD
            , fTimeDelta * -static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
        return m_eState;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(DIR_RIGHT
            , fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
        return m_eState;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(DIR_RIGHT
            , fTimeDelta * -static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
        return m_eState;
    }
     

    return STATE_TYPE::IDLE;
}

CPlayerState_fWalk* CPlayerState_fWalk::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CPlayerState_fWalk* pInstance = new CPlayerState_fWalk(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Player IdleState Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CPlayerState_fWalk::Free()
{
    __super::Free();
}
