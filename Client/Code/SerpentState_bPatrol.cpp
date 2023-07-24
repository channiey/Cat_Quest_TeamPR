#include "SerpentState_bPatrol.h"
#include "Export_Function.h"
#include "Player.h"

CSerpentState_bPatrol::CSerpentState_bPatrol(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
    , m_fChaseRange(0.f)
    , m_fComeBackRange(0.f)
    , m_fPatrolRange(0.f)
    , m_fPlayerTargetRange(0.f)
    , m_fAttackRange(0.f)
{
}

CSerpentState_bPatrol::~CSerpentState_bPatrol()
{
}

HRESULT CSerpentState_bPatrol::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BACK_PATROL;

    // 상태에 전이 조건 수치
    m_fPatrolRange = 1.f;  // Patrol 전이
    m_fChaseRange = 10.f; // Chase 전이
    m_fComeBackRange = 10.f; // ComeBack 전이 - 현위치 -> 원 위치
    m_fPlayerTargetRange = 10.f; // ComeBack 전이 - 현위치 -> 플레이어 위치
    m_fAttackRange = 3.f;  // Attack 전이

    return S_OK;
}

STATE_TYPE CSerpentState_bPatrol::Update_State(const _float& fTimeDelta)
{
    // Monster - Ai Com
    //CAIComponent* pOwnerAI = m_pOwner->Get_OwnerObject()->Get_AiComponent();
    CComponent* pOwnerAI = dynamic_cast<CAIComponent*>(m_pOwner->Get_OwnerObject()->Get_Component(COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));

    // Monster - Transform Com
    CTransform* pOwnerTransform = m_pOwner->Get_OwnerObject()->Get_Transform();

    //Player
    CGameObject* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));



    // Player - Transform Com
    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
    NULL_CHECK_MSG(pPlayerTransform, L"PlayerTransform nullptr");


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
    // Monster - Dir
    _vec3 vOwnerDir = pOwnerTransform->Get_Dir();


    // Player - Pos
    _vec3       vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);


    // Dir Vector
    _vec3       vDir = vPlayerPos - vOwnerPos;            // 방향 벡터 [플레이어 - 몬스터]
    _vec3       vOriginDir = vOwnerOriginPos - vOwnerPos; // 방향 벡터 [원위치  - 몬스터]

    // Distance
    _float      fPlayerDistance = (D3DXVec3Length(&vDir));       // 플레이어와의 거리
    _float      fOriginDistance = (D3DXVec3Length(&vOriginDir)); // 원 위치와의 거리



   // 현재 상태의 기능
    m_fAccTime += fTimeDelta;

    if (vOwnerPatternTime <= m_fAccTime)
    {
        dynamic_cast<CAIComponent*>(pOwnerAI)->Random_Move(fTimeDelta, vOwnerSpeed);
        m_fAccTime = 0.f;
    }
    pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);




#pragma region State Change 
    // BACKPATROL 우선순위
    // Patrol - Chase - Comeback - Attack



      //  임시 조치로 Patrol 에서 comback만 동작 함

   // Patrol 전이 조건
    if (vOwnerDir.z < 0)
    {
       // cout << "patrol 전이" << endl;
        return STATE_TYPE::PATROL;
    }

    if (dynamic_cast<CPlayer*>(pPlayer)->Get_Clocking() != true)
    {
        //// CHASE 전이 조건
        //if (fPlayerDistance <= m_fChaseRange)
        //{
        //    if (vOwnerDir.z < 0)
        //    {
        //      //  cout << "Chase 전이" << endl;
        //     //   pOwnerTransform->Set_Dir(vec3.zero);
        //        return STATE_TYPE::CHASE;
        //    }
        //    else
        //    {
        //     //   cout << "Back Chase 전이" << endl;
        //      //  pOwnerTransform->Set_Dir(vec3.zero);
        //        return STATE_TYPE::BACK_CHASE;
        //    }
        //}



        ////  ATTACK 전이 조건
        //if (fPlayerDistance <= m_fAttackRange)
        //{
        //    if (vOwnerDir.z < 0)
        //    {
        //      //  cout << "attack 전이" << endl;
        //      //  pOwnerTransform->Set_Dir(vec3.zero);
        //        return STATE_TYPE::MONATTACK;
        //    }
        //    else
        //    {
        //     //   cout << "back attack 전이" << endl;
        //     //   pOwnerTransform->Set_Dir(vec3.zero);
        //        return STATE_TYPE::BACK_MONATTACK;
        //    }
        //}
    }


        // COMEBACK 전이 조건
    if (fOriginDistance >= m_fComeBackRange && fPlayerDistance > m_fPlayerTargetRange)
    {
        if (vOwnerDir.z < 0)
        {
            //  cout << "comback 전이" << endl;
            //  pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::COMEBACK;
        }
        else
        {
            //  cout << "back comback 전이" << endl;
            //  pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_COMEBACK;
        }
    }
    // Default
    return STATE_TYPE::BACK_PATROL;

#pragma endregion


  
}

void CSerpentState_bPatrol::LateUpdate_State()
{

}

void CSerpentState_bPatrol::Render_State()
{
    
}

STATE_TYPE CSerpentState_bPatrol::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CSerpentState_bPatrol* CSerpentState_bPatrol::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
 {
    CSerpentState_bPatrol* pInstance = new CSerpentState_bPatrol(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Bat Patrol Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CSerpentState_bPatrol::Free()
{
    __super::Free();
}
