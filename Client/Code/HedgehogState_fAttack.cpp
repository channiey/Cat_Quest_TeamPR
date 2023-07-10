#include "HedgehogState_fAttack.h"
#include "Export_Function.h"


CHedgehogState_fAttack::CHedgehogState_fAttack(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
{
}

CHedgehogState_fAttack::~CHedgehogState_fAttack()
{
}

HRESULT CHedgehogState_fAttack::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }

    m_eState = STATE_TYPE::FRONT_ATTACK;


    return S_OK;
}

STATE_TYPE CHedgehogState_fAttack::Update_State(const _float& fTimeDelta)
{
    // 임시
    STATE_TYPE eState = Key_Input(fTimeDelta);

 /*   if (m_pOwner->Is_AnimationEnd())
    {
        return STATE_TYPE::FRONT_IDLE;
    }*/

    return eState;
}

void CHedgehogState_fAttack::LateUpdate_State()
{
}

void CHedgehogState_fAttack::Render_State()
{


}

STATE_TYPE CHedgehogState_fAttack::Key_Input(const _float& fTimeDelta)
{
    // 임시
    if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_1))
    {
        return STATE_TYPE::FRONT_ATTACK;
    }

    return m_eState;
}

CHedgehogState_fAttack* CHedgehogState_fAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CHedgehogState_fAttack* pInstance = new CHedgehogState_fAttack(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Hedgehog fAttackState Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CHedgehogState_fAttack::Free()
{
    __super::Free();
}
