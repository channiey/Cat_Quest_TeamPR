#include "PlayerState_fWalk.h"

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
    if (GetAsyncKeyState('M'))
        return STATE_TYPE::IDLE;
    else
        return m_eState;
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
