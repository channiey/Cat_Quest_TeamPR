#include "BatState_Chase.h"
#include "Export_Function.h"


CBatState_Chase::CBatState_Chase(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
    , m_fChaseRange(0.f)
    , m_fComeBackRange(0.f)
    , m_fPatrolRange(0.f)
    , m_fPlayerTargetRange(0.f)
    , m_fAttackRange(0.f)
{
}

CBatState_Chase::~CBatState_Chase()
{
}

HRESULT CBatState_Chase::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::CHASE;


    // 상태에 전이 조건 수치
    m_fPatrolRange = 1.f;  // Patrol 전이
    m_fChaseRange = 10.f; // Chase 전이
    m_fComeBackRange = 20.f; // ComeBack 전이 - 현위치 -> 원 위치
    m_fPlayerTargetRange = 10.f; // ComeBack 전이 - 현위치 -> 플레이어 위치
    m_fAttackRange = 3.f;  // Attack 전이


    return S_OK;
}

STATE_TYPE CBatState_Chase::Update_State(const _float& fTimeDelta)
{
  
    // Monster - Ai Com
    CAIComponent* pOwnerAI = dynamic_cast<CAIComponent*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Bat", COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));

    // Monster - Transform Com
    CTransform* pOwnerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Bat", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));

    // Player - Transform Com
    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));


    // Monster - Pos
    _vec3	    vOwnerPos = pOwnerTransform->Get_Info(INFO_POS);
    // Monster - Origin Pos
    _vec3       vOwnerOriginPos = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_OriginPos();
    // Monster - Speed
    _float      vOwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;
    // Moanter - Scale
    _vec3       vOwnerScale = pOwnerTransform->Get_Scale();
    // Monster - Dir
    _vec3       vOwnerDir = pOwnerTransform->Get_Dir();

    // Player - Pos
    _vec3	    vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);

    // Dir Vector
    _vec3       vDir = vPlayerPos - vOwnerPos;            // 방향 벡터 [플레이어 - 몬스터]
    _vec3       vOriginDir = vOwnerOriginPos - vOwnerPos; // 방향 벡터 [원위치  - 몬스터]

    // Distance
    _float      fPlayerDistance = (D3DXVec3Length(&vDir));       // 플레이어와의 거리
    _float      fOriginDistance = (D3DXVec3Length(&vOriginDir)); // 원 위치와의 거리



    // 현재 상태의 기능
    pOwnerAI->Chase_Target(&vPlayerPos, fTimeDelta, vOwnerSpeed);
    pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);
    

   




#pragma region State Change
    // CHASE 우선순위
    //  Back Chase - Attack - Comeback - Patrol

    if (vOwnerDir.z > 0)
    {
       // cout << "Back_chase  전이" << endl;
        return STATE_TYPE::BACK_CHASE;
    }


    // ATTACK 전이 조건
    if (fPlayerDistance <= m_fAttackRange)
    {
        if (vOwnerDir.z < 0)
        {
          //  cout << "attack 전이" << endl;
           // pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::MONATTACK;
        }
        else
        {
           // cout << "back attack 전이" << endl;
          //  pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_MONATTACK;
        }
    }
    // COMEBACK 전이 조건
    if (fOriginDistance >= m_fComeBackRange && fPlayerDistance > m_fPlayerTargetRange)
    {
        if (vOwnerDir.z < 0)
        {
          //  cout << "comback 전이" << endl;
           // pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::COMEBACK;
        }
        else
        {
          //  cout << "back comback 전이" << endl;
           // pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_COMEBACK;
        }
    }
    // PATROL 전이 조건
    if (fPlayerDistance >= m_fPlayerTargetRange && fOriginDistance <= m_fPatrolRange)
    {
        if (vOwnerDir.z < 0)
        {
          //  cout << "patrol 전이" << endl;
          //  pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::PATROL;
        }
        else
        {
          //  cout << "Back patrol 전이" << endl;
          //  pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_PATROL;
        }
        
    }

    // Default 
    return STATE_TYPE::CHASE;


#pragma endregion




  
}

void CBatState_Chase::LateUpdate_State()
{
    
}

void CBatState_Chase::Render_State()
{
   
}

STATE_TYPE CBatState_Chase::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CBatState_Chase* CBatState_Chase::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CBatState_Chase* pInstance = new CBatState_Chase(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("BatState Chase Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CBatState_Chase::Free()
{
    __super::Free();
}
