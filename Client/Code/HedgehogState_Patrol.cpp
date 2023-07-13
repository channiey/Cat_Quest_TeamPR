#include "HedgehogState_Patrol.h"
#include "Export_Function.h"


CHedgehogState_Patrol::CHedgehogState_Patrol(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
    , m_fChaseRange(0.f)
    , m_fComeBackRange(0.f)
    , m_fPatrolRange(0.f)
    , m_fPlayerTargetRange(0.f)
    , m_fAttackRange(0.f)
    
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


    // ���¿� ���� ���� ��ġ
    m_fPatrolRange          = 1.f;  // Patrol ����
    m_fChaseRange           = 10.f; // Chase ����
    m_fComeBackRange        = 20.f; // ComeBack ���� - ����ġ -> �� ��ġ
    m_fPlayerTargetRange    = 10.f; // ComeBack ���� - ����ġ -> �÷��̾� ��ġ
    m_fAttackRange          = 3.f;  // Attack ����
   


    return S_OK;
}

STATE_TYPE CHedgehogState_Patrol::Update_State(const _float& fTimeDelta)
{
   
    // Monster - Ai Com
    CAIComponent* pOwnerAI = dynamic_cast<CAIComponent*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Hedgehog", COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));
    
    // Monster - Transform Com
    CTransform* pOwnerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Hedgehog", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));

    // Player - Transform Com
    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));



    // Monster - Pos
    _vec3       vOwnerPos = pOwnerTransform->Get_Info(INFO_POS);
    // Mosnter - Origin Pos
    _vec3       vOwnerOriginPos = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_OriginPos();
    // Monster - Speed
    _float      vOwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;
    // Monster - PatternTime
    _float      vOwnerPatternTime = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_PatternTime();
    // Monster - Scale
    _vec3 vOwnerScale = pOwnerTransform->Get_Scale();
  

    // Player - Pos
    _vec3       vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);
   

    // Dir Vector
    _vec3       vDir = vPlayerPos - vOwnerPos;            // ���� ���� [�÷��̾� - ����]
    _vec3       vOriginDir = vOwnerOriginPos - vOwnerPos; // ���� ���� [����ġ  - ����]

    // Distance
    _float      fPlayerDistance = (D3DXVec3Length(&vDir));       // �÷��̾���� �Ÿ�
    _float      fOriginDistance = (D3DXVec3Length(&vOriginDir)); // �� ��ġ���� �Ÿ�


 
 
   // ���� ������ ���
   m_fAccTime += fTimeDelta;

   if (vOwnerPatternTime <= m_fAccTime)
   {
       pOwnerAI->Random_Move(fTimeDelta, vOwnerSpeed);
       m_fAccTime = 0.f;
   }
   pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);
   
   


#pragma region State Change 
   // PATROL �켱����
   // Chase - Comeback - Attack
  

   // CHASE ���� ����
   if (fPlayerDistance <= m_fChaseRange)
   {
       //cout << "chase ����" << endl;
       pOwnerTransform->Set_Dir(vec3.zero);
       pOwnerTransform->Set_Scale({ fabs(vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
       return STATE_TYPE::CHASE;
   }

   // COMEBACK ���� ����
   if (fOriginDistance >= m_fComeBackRange && fPlayerDistance > m_fPlayerTargetRange)
   {
       //cout << "comback ����" << endl;
       pOwnerTransform->Set_Dir(vec3.zero);
       pOwnerTransform->Set_Scale({ fabs(vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
       return STATE_TYPE::COMEBACK;
   }

   //  ATTACK ���� ����
   if (fPlayerDistance <= 5.f)
   {
       //cout << "attack ����" << endl;
       pOwnerTransform->Set_Dir(vec3.zero);
       pOwnerTransform->Set_Scale({ fabs(vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
       return STATE_TYPE::MONATTACK;
   }

   // Default
   return STATE_TYPE::PATROL;

#pragma endregion

  
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
        MSG_BOX("HedgehogState Patrol Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CHedgehogState_Patrol::Free()
{
    __super::Free();
}
