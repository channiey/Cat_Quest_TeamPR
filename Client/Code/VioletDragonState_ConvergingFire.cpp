#include "VioletDragonState_ConvergingFire.h"
#include "Export_Function.h"
#include "Monster.h"
#include "Player.h"

CVioletDragonState_ConvergingFire::CVioletDragonState_ConvergingFire(LPDIRECT3DDEVICE9 pGraphicDev)
	:CState(pGraphicDev)
	, m_fAccTime(0.f)
{
}

CVioletDragonState_ConvergingFire::~CVioletDragonState_ConvergingFire()
{
}

HRESULT CVioletDragonState_ConvergingFire::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BOSS_CONVERGING_FIRE;

    m_fAccTime = 0.f;



    return S_OK;
}

STATE_TYPE CVioletDragonState_ConvergingFire::Update_State(const _float& fTimeDelta)
{  // Monster - Transform Com
    CTransform* pOwnerTransform = m_pOwner->Get_OwnerObject()->Get_Transform();

    // Monster - Speed
    _float      vOwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;

    m_fAccTime += fTimeDelta;








#pragma region State Change



    return STATE_TYPE::BOSS_CONVERGING_FIRE;

#pragma endregion


}


void CVioletDragonState_ConvergingFire::LateUpdate_State()
{
}

void CVioletDragonState_ConvergingFire::Render_State()
{
}

STATE_TYPE CVioletDragonState_ConvergingFire::Key_Input(const _float& fTimeDelta)
{
    return m_eState;
}

CVioletDragonState_ConvergingFire* CVioletDragonState_ConvergingFire::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CVioletDragonState_ConvergingFire* pInstance = new CVioletDragonState_ConvergingFire(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("VioletDragonState Fly Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CVioletDragonState_ConvergingFire::Free()
{
}
