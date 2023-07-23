#include "VioletDragonState_FullDown_Fly.h"
#include "Export_Function.h"
#include "Monster.h"


CVioletDragonState_FullDown_Fly::CVioletDragonState_FullDown_Fly(LPDIRECT3DDEVICE9 pGraphicDev)
	:CState(pGraphicDev)
	, m_fAccTime(0.f)

{
}

CVioletDragonState_FullDown_Fly::~CVioletDragonState_FullDown_Fly()
{
}

HRESULT CVioletDragonState_FullDown_Fly::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BOSS_FULLDOWN_FLY;
    
    m_fAccTime = 0.f;
    
    

	return S_OK;
}

STATE_TYPE CVioletDragonState_FullDown_Fly::Update_State(const _float& fTimeDelta)
{
    // Monster - Transform Com
    CTransform* pOwnerTransform = m_pOwner->Get_OwnerObject()->Get_Transform();
   
    // Monster - Speed
    _float      vOwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;

    m_fAccTime += fTimeDelta;
    

  /*  if (m_fAccTime >= 1.5)
    {
        pOwnerTransform->Set_Dir(_vec3{ 0.f, 1.f, 0.f });
    }
    pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);*/


#pragma region State Change
    // FullDown 상태는 FullDown Down 상태로만 전이 한다

    // State Change 

    if (m_fAccTime >= 4.f)
    {

        m_fAccTime = 0.f;
        return STATE_TYPE::BOSS_FULLDOWN_DOWN;
    }
    return STATE_TYPE::BOSS_FULLDOWN_FLY;
#pragma endregion
	
}

void CVioletDragonState_FullDown_Fly::LateUpdate_State()
{
}

void CVioletDragonState_FullDown_Fly::Render_State()
{
}

STATE_TYPE CVioletDragonState_FullDown_Fly::Key_Input(const _float& fTimeDelta)
{
    return m_eState;
}

CVioletDragonState_FullDown_Fly* CVioletDragonState_FullDown_Fly::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{

    CVioletDragonState_FullDown_Fly* pInstance = new CVioletDragonState_FullDown_Fly(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("VioletDragonState Fly Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CVioletDragonState_FullDown_Fly::Free()
{

	__super::Free();

}
