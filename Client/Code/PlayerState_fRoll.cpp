#include "PlayerState_fRoll.h"

#include "Export_Function.h"

CPlayerState_fRoll::CPlayerState_fRoll(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
{
}

CPlayerState_fRoll::~CPlayerState_fRoll()
{
}

HRESULT CPlayerState_fRoll::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
        m_pOwner = pOwner;

    m_eState = STATE_TYPE::FRONT_ROLL;

    return S_OK;
}

STATE_TYPE CPlayerState_fRoll::Update_State(const _float& fTimeDelta)
{
    if (!m_bEnter)
    {
        m_bEnter = true;
    }

    m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * 30.f);

    if (m_pOwner->Is_AnimationEnd())
    {
        m_bEnter = false;
        return STATE_TYPE::FRONT_IDLE;
    } 
    else
        return m_eState;
        
}

void CPlayerState_fRoll::LateUpdate_State()
{
   
}

void CPlayerState_fRoll::Render_State()
{
    //cout << "지금은 앞구르기" << endl;
}

STATE_TYPE CPlayerState_fRoll::Key_Input(const _float& fTimeDelta)
{
    return STATE_TYPE();
}

CPlayerState_fRoll* CPlayerState_fRoll::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CPlayerState_fRoll* pInstance = new CPlayerState_fRoll(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Player fRollState Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CPlayerState_fRoll::Free()
{
    __super::Free();
}
