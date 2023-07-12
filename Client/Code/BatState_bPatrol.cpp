#include "BatState_bPatrol.h"
#include "Export_Function.h"


CBatState_bPatrol::CBatState_bPatrol(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
{
}

CBatState_bPatrol::~CBatState_bPatrol()
{
}

HRESULT CBatState_bPatrol::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BACK_PATROL;
    return S_OK;
}

STATE_TYPE CBatState_bPatrol::Update_State(const _float& fTimeDelta)
{
    
    STATE_TYPE eState;

    CAIComponent* pOwnerAI = dynamic_cast<CAIComponent*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Bat", COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));
    
   
    _vec3  OwnerOriginPos = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_OriginPos();


    _float  OwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;
  

  CTransform* pOwnerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Bat", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
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




   _vec3 vOwnerDir = pOwnerTransform->Get_Dir();

   //  Patrol ���� ����
   if (vOwnerDir.z < 0)
   {
       cout << "patrol  ����" << endl;
       return STATE_TYPE::PATROL;
   }



   // CHASE ���� ����
   if (fDistance <= 10.f)
   {
     
       if (vOwnerDir.z < 0)
       {
           cout << "chase  ����" << endl;
           pOwnerTransform->Set_Dir(vec3.zero);
           return STATE_TYPE::CHASE;
       }
       else
       {
           cout << "back chase  ����" << endl;
           pOwnerTransform->Set_Dir(vec3.zero);
           return STATE_TYPE::BACK_CHASE;
       }
   }

   // COMEBACK ���� ����
   if (fOriginDistance >= 50.f  &&  fDistance> 15.f )
   {
   

       if (vOwnerDir.z < 0)
       {
           cout << "COMBACK  ����" << endl;
           pOwnerTransform->Set_Dir(vec3.zero);
           return STATE_TYPE::COMEBACK;
       }
       else
       {
           cout << "back COMBACK  ����1" << endl;
           pOwnerTransform->Set_Dir(vec3.zero);
           return STATE_TYPE::BACK_COMEBACK;
       }
   }
   if (fDistance <= 5.f)  // Attack ���� ����
   {

       if (vOwnerDir.z < 0)
       {
           cout << "attack  ����" << endl;
           pOwnerTransform->Set_Dir(vec3.zero);
           return STATE_TYPE::MONATTACK;
       }
       else
       {
           cout << "back attack  ����" << endl;
           pOwnerTransform->Set_Dir(vec3.zero);
           return STATE_TYPE::BACK_MONATTACK;
       }
    
   }


   return STATE_TYPE::BACK_PATROL;
  


  
}

void CBatState_bPatrol::LateUpdate_State()
{

}

void CBatState_bPatrol::Render_State()
{
    
}

STATE_TYPE CBatState_bPatrol::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CBatState_bPatrol* CBatState_bPatrol::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
 {
    CBatState_bPatrol* pInstance = new CBatState_bPatrol(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Bat Patrol Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CBatState_bPatrol::Free()
{
    __super::Free();
}
