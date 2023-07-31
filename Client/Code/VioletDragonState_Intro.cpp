#include "VioletDragonState_Intro.h"
#include "Export_Function.h"
#include "Player.h"
#include "VioletDragon.h"

CVioletDragonState_Intro::CVioletDragonState_Intro(LPDIRECT3DDEVICE9 pGraphicDev)
    :CState(pGraphicDev)
{
}

CVioletDragonState_Intro::~CVioletDragonState_Intro()
{
}

HRESULT CVioletDragonState_Intro::Ready_State(CStateMachine* pOwner)
{

    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BOSS_INTRO;



    return S_OK;
}

STATE_TYPE CVioletDragonState_Intro::Update_State(const _float& fTimeDelta)
{
    return STATE_TYPE();
}

void CVioletDragonState_Intro::LateUpdate_State()
{
}

void CVioletDragonState_Intro::Render_State()
{
}

STATE_TYPE CVioletDragonState_Intro::Key_Input(const _float& fTimeDelta)
{
    return STATE_TYPE();
}

CVioletDragonState_Intro* CVioletDragonState_Intro::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    return nullptr;
}

void CVioletDragonState_Intro::Free()
{
}
