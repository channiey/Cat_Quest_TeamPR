#include "WyvernState_Patrol.h"
#include "Export_Function.h"


CWyvernState_Patrol::CWyvernState_Patrol(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
{
}

CWyvernState_Patrol::~CWyvernState_Patrol()
{
}

HRESULT CWyvernState_Patrol::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::PATROL;
    return S_OK;
}

STATE_TYPE CWyvernState_Patrol::Update_State(const _float& fTimeDelta)
{
    
    STATE_TYPE eState;

    CAIComponent* pOwnerAI = dynamic_cast<CAIComponent*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Wyvern", COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));
    
   
    _vec3  OwnerOriginPos = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_OriginPos();


    _float  OwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;
  

  CTransform* pOwnerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Wyvern", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
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
   m_fAccTime += fTimeDelta;

   if (OwnerPatternTime <= m_fAccTime)
   {
       pOwnerAI->Random_Move(fTimeDelta, OwnerSpeed);
       m_fAccTime = 0.f;
   }
   pOwnerTransform->Translate(fTimeDelta * OwnerSpeed);


   // CHASE 전이 조건
   if (fDistance <= 10.f)
   {
       cout << "CHASe 전이" << endl;
       pOwnerTransform->Set_Dir(vec3.zero);
       return STATE_TYPE::CHASE;
   }

   // COMEBACK 전이 조건
   if (fOriginDistance >= 20.f  && fDistance> 20.f )
   {
       cout << "comback 전이" << endl;
       pOwnerTransform->Set_Dir(vec3.zero);
       return STATE_TYPE::COMEBACK;
   }
   if (fDistance <= 5.f)  // Attack 전이 조건
   {
       cout << "attack 전이" << endl;
       pOwnerTransform->Set_Dir(vec3.zero);
       return STATE_TYPE::FRONT_ATTACK;
   }


   return STATE_TYPE::PATROL;
  


  
}

void CWyvernState_Patrol::LateUpdate_State()
{

}

void CWyvernState_Patrol::Render_State()
{
    
}

STATE_TYPE CWyvernState_Patrol::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CWyvernState_Patrol* CWyvernState_Patrol::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
 {
    CWyvernState_Patrol* pInstance = new CWyvernState_Patrol(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Wyvern Patrol Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CWyvernState_Patrol::Free()
{
    __super::Free();
}
