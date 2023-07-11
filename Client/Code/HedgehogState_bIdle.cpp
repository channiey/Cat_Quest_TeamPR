#include "HedgehogState_bIdle.h"
#include "Export_Function.h"
#include "HedgehogState_Patrol.h"

CHedgehogState_bIdle::CHedgehogState_bIdle(LPDIRECT3DDEVICE9 pGraphicDev)
	:CState(pGraphicDev)
{
}

CHedgehogState_bIdle::~CHedgehogState_bIdle()
{
}

HRESULT CHedgehogState_bIdle::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }

    m_eState = STATE_TYPE::BACK_IDLE;


    return S_OK;
}

STATE_TYPE CHedgehogState_bIdle::Update_State(const _float& fTimeDelta)
{
    // юс╫ц
    STATE_TYPE eState = Key_Input(fTimeDelta);

    return eState;
}

void CHedgehogState_bIdle::LateUpdate_State()
{
}

void CHedgehogState_bIdle::Render_State()
{
}

STATE_TYPE CHedgehogState_bIdle::Key_Input(const _float& fTimeDelta)
{
    // State Test

    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
    _vec3 PlayerPos = pPlayerTransform->Get_Info(INFO_POS);


    CTransform* pDragonTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Hedgehog", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
    _vec3 DragonPos = pDragonTransform->Get_Info(INFO_POS);

    _float fDistance = D3DXVec3Length(&(PlayerPos - DragonPos));


    if (fDistance <= 15.f)
    {
        return STATE_TYPE::PATROL;
    }


    return m_eState;
}

CHedgehogState_bIdle* CHedgehogState_bIdle::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CHedgehogState_bIdle* pInstance = new CHedgehogState_bIdle(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("HedgehogState bIdleState Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CHedgehogState_bIdle::Free()
{
    __super::Free();
}
