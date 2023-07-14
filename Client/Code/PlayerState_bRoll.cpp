#include "PlayerState_bRoll.h"

#include "Export_Function.h"

CPlayerState_bRoll::CPlayerState_bRoll(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
{
}

CPlayerState_bRoll::~CPlayerState_bRoll()
{
}

HRESULT CPlayerState_bRoll::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
        m_pOwner = pOwner;

    m_eState = STATE_TYPE::BACK_ROLL;

    return S_OK;
}

STATE_TYPE CPlayerState_bRoll::Update_State(const _float& fTimeDelta)
{
    m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * 60.f);

    if (m_pOwner->Is_AnimationEnd())
        return STATE_TYPE::BACK_IDLE;
    else
        return m_eState;
}

void CPlayerState_bRoll::LateUpdate_State()
{

}

void CPlayerState_bRoll::Render_State()
{
    //cout << "������ �ڱ�����" << endl;
}

STATE_TYPE CPlayerState_bRoll::Key_Input(const _float& fTimeDelta)
{
    return STATE_TYPE();
}

CPlayerState_bRoll* CPlayerState_bRoll::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CPlayerState_bRoll* pInstance = new CPlayerState_bRoll(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Player bRollState Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CPlayerState_bRoll::Free()
{
    __super::Free();
}