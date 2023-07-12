#include "HedgehogState_Attack.h"
#include "Export_Function.h"


CHedgegohState_Attack::CHedgegohState_Attack(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
{
}

CHedgegohState_Attack::~CHedgegohState_Attack()
{
}

HRESULT CHedgegohState_Attack::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::FRONT_ATTACK;
    return S_OK;
}

STATE_TYPE CHedgegohState_Attack::Update_State(const _float& fTimeDelta)
{
    
    STATE_TYPE eState;

    CAIComponent* pOwnerAI = dynamic_cast<CAIComponent*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Hedgehog", COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));
    
   
    _vec3  OwnerOriginPos = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_OriginPos();


    _float  OwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;
  

  CTransform* pOwnerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Hedgehog", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
   _vec3 vOwnerPos = pOwnerTransform->Get_Info(INFO_POS);


   _float OwnerPatternTime = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_PatternTime();
  
  
   CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
   _vec3 vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);

   _vec3 vDir = vPlayerPos - vOwnerPos;

   _vec3       vOriginDir;
   vOriginDir = OwnerOriginPos - vOwnerPos;
   _float fOriginDistance = (D3DXVec3Length(&vOriginDir)); // 원 위치와의 거리


   _float fDistance = (D3DXVec3Length(&vDir));
  

   // 기능
   m_fAccTime += fTimeDelta;

   if (OwnerPatternTime <= m_fAccTime)
   {
       pOwnerAI->Chase_Target(&vPlayerPos, fTimeDelta, OwnerSpeed*2);
       m_fAccTime = 0.f;
   }   
   pOwnerTransform->Translate(fTimeDelta* OwnerSpeed);

  
   _vec3 vOwnerScale = pOwnerTransform->Get_Scale();



   // CHASE 전이 조건
   if (fDistance >= 10.f  &&  fDistance < 30.f)
   {
       cout << "chase  전이" << endl;
       pOwnerTransform->Set_Dir(vec3.zero);
       pOwnerTransform->Set_Scale({ fabs(vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
       return STATE_TYPE::CHASE;
   }
 
   // COMEBACK 전이 조건
   if (fOriginDistance >= 20.f)
   {
       cout << "COMBACK  전이" << endl;
       pOwnerTransform->Set_Scale({ fabs(vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
       pOwnerTransform->Set_Dir(vec3.zero);
       return STATE_TYPE::COMEBACK;
   }
  

   return STATE_TYPE::FRONT_ATTACK;
  

   // Patrol 전이 조건
   //chase -> patrol 가게 해둠

  
}

void CHedgegohState_Attack::LateUpdate_State()
{

}

void CHedgegohState_Attack::Render_State()
{
    
}

STATE_TYPE CHedgegohState_Attack::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CHedgegohState_Attack* CHedgegohState_Attack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CHedgegohState_Attack* pInstance = new CHedgegohState_Attack(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Hedgehog fAttackState Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CHedgegohState_Attack::Free()
{
    __super::Free();
}
