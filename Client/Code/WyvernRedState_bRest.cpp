#include "WyvernRedState_bRest.h"
#include "Export_Function.h"
#include "Player.h"

CWyvernRedState_bRest::CWyvernRedState_bRest(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
    , m_fChaseRange(0.f)
    , m_fComeBackRange(0.f)
    , m_fPatrolRange(0.f)
    , m_fPlayerTargetRange(0.f)
    , m_fAttackRange(0.f)
{
}

CWyvernRedState_bRest::~CWyvernRedState_bRest()
{
}

HRESULT CWyvernRedState_bRest::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BACK_MONATTACK;

    // 상태에 전이 조건 수치
    m_fPatrolRange = 1.f;  // Patrol 전이
    m_fChaseRange = 10.f; // Chase 전이
    m_fComeBackRange = 20.f; // ComeBack 전이 - 현위치 -> 원 위치
    m_fPlayerTargetRange = 10.f; // ComeBack 전이 - 현위치 -> 플레이어 위치
    m_fAttackRange = 3.f;  // Attack 전이

    m_fAccTime = 0.f;
    return S_OK;
}

STATE_TYPE CWyvernRedState_bRest::Update_State(const _float& fTimeDelta)
{
    STATE_TYPE eState = m_eState;

    // Monstre Component ==============================
    // Monster - Ai Com
    CComponent* pOwnerAI = dynamic_cast<CAIComponent*>(m_pOwner->Get_OwnerObject()->Get_Component(COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));
    NULL_CHECK_RETURN(pOwnerAI, eState);

    // Monster - Transform Com
    CTransform* pOwnerTransform = m_pOwner->Get_OwnerObject()->Get_Transform();
    NULL_CHECK_RETURN(pOwnerTransform, eState);

    //Monster - Animator
    CComponent* pOwnerAnimator = dynamic_cast<CAnimator*>(m_pOwner->Get_OwnerObject()->Get_Component(COMPONENT_TYPE::ANIMATOR, COMPONENTID::ID_STATIC));
    NULL_CHECK_RETURN(pOwnerAnimator, eState);

    // Monster - Cur Animation
    CAnimation* pOwenrCurAnimation = dynamic_cast<CAnimator*>(pOwnerAnimator)->Get_CurAniamtion();
    NULL_CHECK_RETURN(pOwenrCurAnimation, eState);

    // Player Component ==============================
    // Player
    CGameObject* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));
    NULL_CHECK_RETURN(pPlayer, eState);

    // Player - Transform Com
    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
    NULL_CHECK_RETURN(pPlayerTransform, eState);


    // GET INFO =================================================================
    // Monster - Pos
    _vec3       vOwnerPos = pOwnerTransform->Get_Info(INFO_POS);
    NULL_CHECK_RETURN(vOwnerPos, eState);

    // Mosnter - Origin Pos
    _vec3       vOwnerOriginPos = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_OriginPos();
    NULL_CHECK_RETURN(vOwnerOriginPos, eState);

    // Monster - Speed
    _float      vOwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;
    NULL_CHECK_RETURN(vOwnerSpeed, eState);

    // Monster - PatternTime
    _float      vOwnerPatternTime = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_PatternTime();
    NULL_CHECK_RETURN(vOwnerPatternTime, eState);

    // Monster - Scale
    _vec3 vOwnerScale = pOwnerTransform->Get_Scale();
    NULL_CHECK_RETURN(vOwnerScale, eState);

    // Monster - Dir
    _vec3 vOwnerDir = pOwnerTransform->Get_Dir();
    NULL_CHECK_RETURN(vOwnerDir, eState);

    // Player - Pos
    _vec3       vPlayerPos;
    vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);
    NULL_CHECK_RETURN(pPlayerTransform, eState);


    // Setting Value
    // Dir Vector
    _vec3       vDir = vPlayerPos - vOwnerPos;            // 방향 벡터 [플레이어 - 몬스터]
    _vec3       vOriginDir = vOwnerOriginPos - vOwnerPos; // 방향 벡터 [원위치  - 몬스터]

    // Distance
    _float      fPlayerDistance = (D3DXVec3Length(&vDir));       // 플레이어와의 거리
    _float      fOriginDistance = (D3DXVec3Length(&vOriginDir)); // 원 위치와의 거리


   // 현재 상태의 기능
   /* pOwnerTransform->Set_Dir(vec3.zero);
    pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);*/


  

//#pragma region State Change
//
//  
//   
//    //// BACK_ MONREST 전이
//    //if (vOwnerDir.z > 0)
//    //{
//    //    // cout <<  "back monattack 전이" << endl;
//    //    return STATE_TYPE::MONREST;
//    //}
//    // 
//    // 
//    m_fAccTime += fTimeDelta;
//
//    if (m_fAccTime >= 1.5f)
//    {
//        m_fAccTime = 0.f;
//        if (dynamic_cast<CPlayer*>(pPlayer)->Get_Clocking() != true)
//        {
//            //  ATTACK 전이 조건
//            if (fPlayerDistance <= m_fAttackRange)
//            {
//                if (vOwnerDir.z < 0)
//                {
//                    // cout << "attack 전이" << endl;
//                    // pOwnerTransform->Set_Dir(vec3.zero);
//                    return STATE_TYPE::MONATTACK;
//                }
//                else
//                {
//                    // cout << "back attack 전이" << endl;
//                   //  pOwnerTransform->Set_Dir(vec3.zero);
//                    return STATE_TYPE::BACK_MONATTACK;
//                }
//
//            }
//
//            // CHASE 전이 조건
//            if (fPlayerDistance <= m_fChaseRange)
//            {
//                if (vOwnerDir.z < 0)
//                {
//                    // cout << "Chase 전이" << endl;
//                    // pOwnerTransform->Set_Dir(vec3.zero);
//                    return STATE_TYPE::CHASE;
//                }
//                else
//                {
//                    // cout << "Back Chase 전이" << endl;
//                   //  pOwnerTransform->Set_Dir(vec3.zero);
//                    return STATE_TYPE::BACK_CHASE;
//                }
//            }
//        }
//        // PATROL 전이 조건
//        if (fPlayerDistance >= m_fPlayerTargetRange && fOriginDistance <= m_fPatrolRange)
//        {
//            if (vOwnerDir.z < 0)
//            {
//                //  cout << "patrol 전이" << endl;
//                //  pOwnerTransform->Set_Dir(vec3.zero);
//                return STATE_TYPE::PATROL;
//            }
//            else
//            {
//                //  cout << "Back patrol 전이" << endl;
//                //  pOwnerTransform->Set_Dir(vec3.zero);
//                return STATE_TYPE::BACK_PATROL;
//            }
//
//        }
//        // COMEBACK 전이 조건
//        if (fOriginDistance >= m_fComeBackRange || fPlayerDistance > m_fPlayerTargetRange)
//        {
//            if (vOwnerDir.z < 0)
//            {
//                // cout << "comback 전이" << endl;
//                // pOwnerTransform->Set_Dir(vec3.zero);
//                return STATE_TYPE::COMEBACK;
//            }
//            else
//            {
//                // cout << "back comback 전이" << endl;
//                // pOwnerTransform->Set_Dir(vec3.zero);
//                return STATE_TYPE::BACK_COMEBACK;
//            }
//        }
//     
//    }
//    return STATE_TYPE::BACK_MONREST;
//
//
//#pragma endregion


    //Test 전이  - 공격으로만 전이 된다

    // Attack 전이
    if (fPlayerDistance <= m_fAttackRange)
    {
        if (vOwnerDir.z < 0)
        {
            // cout << "attack 전이" << endl;
            // pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::MONATTACK;
        }
        else
        {
            // cout << "back attack 전이" << endl;
            // pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_MONATTACK;
        }
    }
    //CHASE 전이 조건
    if (fPlayerDistance <= m_fChaseRange)
    {
        if (vOwnerDir.z < 0)
        {
            // cout << "Chase 전이" << endl;
            // pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::CHASE;
        }
        else
        {
            // cout << "Back Chase 전이" << endl;
           //  pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_CHASE;
        }
    }



  
}

void CWyvernRedState_bRest::LateUpdate_State()
{

}

void CWyvernRedState_bRest::Render_State()
{
    
}

STATE_TYPE CWyvernRedState_bRest::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CWyvernRedState_bRest* CWyvernRedState_bRest::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CWyvernRedState_bRest* pInstance = new CWyvernRedState_bRest(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Bat State Attack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CWyvernRedState_bRest::Free()
{
    __super::Free();
}
