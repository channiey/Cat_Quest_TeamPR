#include "BatState_bAttack.h"
#include "Export_Function.h"


CBatState_bAttack::CBatState_bAttack(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
{
}

CBatState_bAttack::~CBatState_bAttack()
{
}

HRESULT CBatState_bAttack::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BACK_MONATTACK;
    return S_OK;
}

STATE_TYPE CBatState_bAttack::Update_State(const _float& fTimeDelta)
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
   _float fOriginDistance = (D3DXVec3Length(&vOriginDir)); // 원 위치와의 거리


   _float fDistance = (D3DXVec3Length(&vDir));
  

   // 기능
   //m_fAccTime += fTimeDelta;

   //if (OwnerPatternTime <= m_fAccTime)
   //{
   //    pOwnerAI->Chase_Target(&PlayerPos, fTimeDelta, OwnerSpeed*2);
   //    m_fAccTime = 0.f;
   //}
   pOwnerTransform->Set_Dir(vec3.zero);
   pOwnerTransform->Translate(fTimeDelta * OwnerSpeed);


   _vec3 vOwnerDir = pOwnerTransform->Get_Dir();
   if (vOwnerDir.z < 0)
   {
       cout << "attack 전이" << endl;
       return STATE_TYPE::MONATTACK;
   }



   // CHASE 전이 조건
   if (fDistance >= 10.f )
   {
  
       if (vOwnerDir.z < 0)
       {
           cout << "chase  전이" << endl;
           pOwnerTransform->Set_Dir(vec3.zero);
           return STATE_TYPE::CHASE;
       }
       else
       {
           cout << "back chase  전이" << endl;
           pOwnerTransform->Set_Dir(vec3.zero);
           return STATE_TYPE::BACK_CHASE;
       }
   }
 
   // COMEBACK 전이 조건
   if (fOriginDistance >= 20.f && fDistance > 10.f)
   {
     
       if (vOwnerDir.z < 0)
       {
           cout << "COMBACK  전이" << endl;
           pOwnerTransform->Set_Dir(vec3.zero);
           return STATE_TYPE::COMEBACK;
       }
       else
       {
           cout << "back COMBACK  전이" << endl;
           pOwnerTransform->Set_Dir(vec3.zero);
           return STATE_TYPE::BACK_COMEBACK;
       }
   }
  

   return STATE_TYPE::MONATTACK;
  

   // Patrol 전이 조건
   //chase -> patrol 가게 해둠

  
}

void CBatState_bAttack::LateUpdate_State()
{

}

void CBatState_bAttack::Render_State()
{
    
}

STATE_TYPE CBatState_bAttack::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CBatState_bAttack* CBatState_bAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CBatState_bAttack* pInstance = new CBatState_bAttack(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("BatState Attack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CBatState_bAttack::Free()
{
    __super::Free();
}
