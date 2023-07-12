#include "HedgehogState_Patrol.h"
#include "Export_Function.h"


CHedgehogState_Patrol::CHedgehogState_Patrol(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
{
}

CHedgehogState_Patrol::~CHedgehogState_Patrol()
{
}

HRESULT CHedgehogState_Patrol::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::PATROL;
    return S_OK;
}

STATE_TYPE CHedgehogState_Patrol::Update_State(const _float& fTimeDelta)
{
    
    STATE_TYPE eState;

    CAIComponent* pOwnerAI = dynamic_cast<CAIComponent*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Hedgehog", COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));
    
   
    _vec3  OwnerOriginPos = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_OriginPos();


    _float  OwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;
  

  CTransform* pOwnerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Hedgehog", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
   _vec3 OwnerPos = pOwnerTransform->Get_Info(INFO_POS);


   _float OwnerPatternTime = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_PatternTime();
  
  
   CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
   _vec3 PlayerPos = pPlayerTransform->Get_Info(INFO_POS);

   _vec3 vDir = PlayerPos - OwnerPos;

   _vec3       vOriginDir;
   vOriginDir = OwnerOriginPos - OwnerPos;
   _float fOriginDistance = (D3DXVec3Length(&vOriginDir)); // �� ��ġ���� �Ÿ�


   _float fDistance = (D3DXVec3Length(&vDir));
   
 

   // ���
   m_fAccTime += fTimeDelta;

   if (OwnerPatternTime <= m_fAccTime)
   {
      
       pOwnerAI->Random_Move(fTimeDelta, OwnerSpeed);
       m_fAccTime = 0.f;
       
   }

   pOwnerTransform->Translate(fTimeDelta * OwnerSpeed);



   _vec3 vOwnerScale = pOwnerTransform->Get_Scale();


   // CHASE ���� ����
   if (fDistance <= 10.f)
   {
       cout << "CHASe ����" << endl;
       pOwnerTransform->Set_Dir(vec3.zero);
       pOwnerTransform->Set_Scale({ fabs(vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
       return STATE_TYPE::CHASE;
   }

   // COMEBACK ���� ����
   if (fOriginDistance >= 20.f  && fDistance> 20.f )
   {
       cout << "comback ����" << endl;
       pOwnerTransform->Set_Dir(vec3.zero);
       pOwnerTransform->Set_Scale({ fabs(vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
       return STATE_TYPE::COMEBACK;
   }
   if (fDistance <= 5.f)  // Attack ���� ����
   {
       cout << "attack ����" << endl;
       pOwnerTransform->Set_Dir(vec3.zero);
       pOwnerTransform->Set_Scale({ fabs(vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
       return STATE_TYPE::FRONT_ATTACK;
   }


   return STATE_TYPE::PATROL;
  


  
}

void CHedgehogState_Patrol::LateUpdate_State()
{

}

void CHedgehogState_Patrol::Render_State()
{
    
}

STATE_TYPE CHedgehogState_Patrol::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CHedgehogState_Patrol* CHedgehogState_Patrol::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CHedgehogState_Patrol* pInstance = new CHedgehogState_Patrol(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Hedgehog fAttackState Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CHedgehogState_Patrol::Free()
{
    __super::Free();
}
