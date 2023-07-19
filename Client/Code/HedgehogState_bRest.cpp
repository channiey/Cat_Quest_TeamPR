#include "HedgehogState_bRest.h"
#include "Export_Function.h"


CHedgehogState_bRest::CHedgehogState_bRest(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
    , m_fChaseRange(0.f)
    , m_fComeBackRange(0.f)
    , m_fPatrolRange(0.f)
    , m_fPlayerTargetRange(0.f)
    , m_fAttackRange(0.f)
{
}

CHedgehogState_bRest::~CHedgehogState_bRest()
{
}

HRESULT CHedgehogState_bRest::Ready_State(CStateMachine* pOwner)
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

STATE_TYPE CHedgehogState_bRest::Update_State(const _float& fTimeDelta)
{

    //Monster - Ainmator Com
    CComponent* pOwnerAnimator = dynamic_cast<CAnimator*>(m_pOwner->Get_OwnerObject()->Get_Component(COMPONENT_TYPE::ANIMATOR, COMPONENTID::ID_STATIC));


    // Monster - Ai Com
    //CAIComponent* pOwnerAI = m_pOwner->Get_OwnerObject()->Get_AiComponent();
    CComponent* pOwnerAI = dynamic_cast<CAIComponent*>(m_pOwner->Get_OwnerObject()->Get_Component(COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));


    // Monster - Transform Com
    CTransform* pOwnerTransform = m_pOwner->Get_OwnerObject()->Get_Transform();

    // Player - Transform Com
    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
    NULL_CHECK_MSG(pPlayerTransform, L"PlayerTransform nullptr");

    // Monster - Pos
    _vec3	    vOwnerPos = pOwnerTransform->Get_Info(INFO_POS);
    // Monster - Origin Pos
    _vec3       vOwnerOriginPos = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_OriginPos();
    // Monster - Speed
    _float      vOwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;
    // Monster - Scale
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
   /* pOwnerTransform->Set_Dir(vec3.zero);
    pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);*/


  

#pragma region State Change

  
   
    //// BACK_ MONREST 전이
    //if (vOwnerDir.z > 0)
    //{
    //    // cout <<  "back monattack 전이" << endl;
    //    return STATE_TYPE::MONREST;
    //}
    // 
    // 
    m_fAccTime += fTimeDelta;

    if (m_fAccTime >= 1.5f) // 몇 초 후 전이 조건
    {
        m_fAccTime = 0.f;
        
        // Attack 전이 조건
        if (fPlayerDistance <= m_fAttackRange)
        {
            m_fAccTime = 0.f;
            //cout << "attack 전이" << endl;
            //pOwnerTransform->Set_Scale({(vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
            return STATE_TYPE::BACK_MONATTACK;
        }
        
        // CHASE 전이 조건
        if (fPlayerDistance <= m_fChaseRange)
        {
            m_fAccTime = 0.f;
            // cout << "chase  전이" << endl;
            // pOwnerTransform->Set_Scale({ (vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
            return STATE_TYPE::BACK_CHASE;
        }

        // COMEBACK 전이 조건
        if (fOriginDistance >= m_fComeBackRange || fPlayerDistance > m_fPlayerTargetRange)
        {
            m_fAccTime = 0.f;
            // cout << "COMBACK  전이" << endl;
             //pOwnerTransform->Set_Scale({ (vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
            return STATE_TYPE::BACK_COMEBACK;
        }
     
    }
    return STATE_TYPE::BACK_MONREST;


#pragma endregion

  
}

void CHedgehogState_bRest::LateUpdate_State()
{

}

void CHedgehogState_bRest::Render_State()
{
    
}

STATE_TYPE CHedgehogState_bRest::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CHedgehogState_bRest* CHedgehogState_bRest::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CHedgehogState_bRest* pInstance = new CHedgehogState_bRest(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Test State Attack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CHedgehogState_bRest::Free()
{
    __super::Free();
}
