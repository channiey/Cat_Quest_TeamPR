#include "BatState_Attack.h"
#include "Export_Function.h"


CBatState_Attack::CBatState_Attack(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
{
}

CBatState_Attack::~CBatState_Attack()
{
}

HRESULT CBatState_Attack::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::FRONT_ATTACK;
    return S_OK;
}

STATE_TYPE CBatState_Attack::Update_State(const _float& fTimeDelta)
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
       pOwnerAI->Chase_Target(&PlayerPos, fTimeDelta, OwnerSpeed*2);
       m_fAccTime = 0.f;
   }
   pOwnerTransform->Translate(fTimeDelta * OwnerSpeed);


   // CHASE ���� ����
   if (fDistance >= 10.f  &&  fDistance < 30.f)
   {
      // cout << "chase  ����" << endl;
       pOwnerTransform->Set_Dir(vec3.zero);
       return STATE_TYPE::CHASE;
   }
 
   // COMEBACK ���� ����
   if (fOriginDistance >= 20.f)
   {
      // cout << "COMBACK  ����" << endl;
       pOwnerTransform->Set_Dir(vec3.zero);
       return STATE_TYPE::COMEBACK;
   }
  

   return STATE_TYPE::FRONT_ATTACK;
  

   // Patrol ���� ����
   //chase -> patrol ���� �ص�

  
}

void CBatState_Attack::LateUpdate_State()
{

}

void CBatState_Attack::Render_State()
{
    
}

STATE_TYPE CBatState_Attack::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CBatState_Attack* CBatState_Attack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CBatState_Attack* pInstance = new CBatState_Attack(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("BatState Attack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CBatState_Attack::Free()
{
    __super::Free();
}
