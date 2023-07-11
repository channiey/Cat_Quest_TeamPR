#include "HedgehogState_Chase.h"
#include "Export_Function.h"


CHedgehogState_Chase::CHedgehogState_Chase(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
{
}

CHedgehogState_Chase::~CHedgehogState_Chase()
{
}

HRESULT CHedgehogState_Chase::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::CHASE;
    return S_OK;
}

STATE_TYPE CHedgehogState_Chase::Update_State(const _float& fTimeDelta)
{
  
    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
  

    CTransform* pOwnerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Hedgehog", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
 
    _float OwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;

    _vec3 Dir = pOwnerTransform->Get_Info(INFO_LOOK);

    _vec3	vPlayerPos;
    vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);

    _vec3	vOwnerPos;
    vOwnerPos = pOwnerTransform->Get_Info(INFO_POS);

    _vec3		vLook;
    vLook = vPlayerPos- vOwnerPos;
    _float fDistance = (D3DXVec3Length(&vLook));

    CAIComponent* pOwnerAI = dynamic_cast<CAIComponent*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Hedgehog", COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));
   

    pOwnerAI->Chase_Target(&vPlayerPos, fTimeDelta, OwnerSpeed);
   
  
    if (fDistance >= 20.f)
    {
      pOwnerTransform->Set_Dir(vec3.zero);
      return STATE_TYPE::PATROL; 
    }
    else
    {
        return STATE_TYPE::CHASE;
    }

  
}

void CHedgehogState_Chase::LateUpdate_State()
{
    
}

void CHedgehogState_Chase::Render_State()
{
    cout << "고슴도치 patro 상태" << endl;

}

STATE_TYPE CHedgehogState_Chase::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CHedgehogState_Chase* CHedgehogState_Chase::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CHedgehogState_Chase* pInstance = new CHedgehogState_Chase(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Hedgehog fAttackState Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CHedgehogState_Chase::Free()
{
    __super::Free();
}
