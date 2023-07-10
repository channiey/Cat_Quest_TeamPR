#include "HedgehogState_fIdle.h"
#include "Export_Function.h"


CHedgehogState_fIdle::CHedgehogState_fIdle(LPDIRECT3DDEVICE9 pGraphicDev)
    :CState(pGraphicDev)
{
}

CHedgehogState_fIdle::~CHedgehogState_fIdle()
{
}

HRESULT CHedgehogState_fIdle::Ready_State(CStateMachine* pOwner)
{

    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }

    m_eState = STATE_TYPE::FRONT_IDLE;

    return S_OK;
}

STATE_TYPE CHedgehogState_fIdle::Update_State(const _float& fTimeDelta)
{
    // 임시 
    STATE_TYPE eState = Key_Input(fTimeDelta);

    return eState;
}

void CHedgehogState_fIdle::LateUpdate_State()
{
}

void CHedgehogState_fIdle::Render_State()
{
}

STATE_TYPE CHedgehogState_fIdle::Key_Input(const _float& fTimeDelta)
{

    // State Test

    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
    _vec3 PlayerPos = pPlayerTransform->Get_Info(INFO_POS);


    CTransform* pMonsterTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Hedgehog", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
    _vec3 MonsterPos = pMonsterTransform->Get_Info(INFO_POS);


    _float fDistance = D3DXVec3Length(&(PlayerPos - MonsterPos));


    if (fDistance <= 15.f)
    {
        return STATE_TYPE::FRONT_ATTACK;
    }
    ////////////////////////////////////////////////// 플레이어 가까워지면 공격

    // State Test 2

    if (PlayerPos.z < MonsterPos.z)
    {
        if (PlayerPos.x <= MonsterPos.x)

        {
            pMonsterTransform->Set_Scale({ -1.46f, 1.04f, 2.f });
        }
        else
        {
            pMonsterTransform->Set_Scale({ 1.46f, 1.04f, 2.f });
        }
        return STATE_TYPE::FRONT_IDLE;
    }


    if (PlayerPos.z >= MonsterPos.z)
    {
        if (PlayerPos.x <= MonsterPos.x)
        {
            pMonsterTransform->Set_Scale({ -1.46f, 1.04f, 2.f });
        }
        else
        {
            pMonsterTransform->Set_Scale({ 1.46f, 1.04f, 2.f });
        }
        return STATE_TYPE::BACK_IDLE;
    }




    return m_eState;
}

CHedgehogState_fIdle* CHedgehogState_fIdle::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CHedgehogState_fIdle* pInstance = new CHedgehogState_fIdle(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Hedgehog fIdleState Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CHedgehogState_fIdle::Free()
{
    __super::Free();
}
