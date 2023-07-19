#include "WyvernRedState_Rest.h"
#include "Export_Function.h"


CWyvernRedState_Rest::CWyvernRedState_Rest(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
    , m_fChaseRange(0.f)
    , m_fComeBackRange(0.f)
    , m_fPatrolRange(0.f)
    , m_fPlayerTargetRange(0.f)
    , m_fAttackRange(0.f)
    , m_fPosShakeRange(0.f)
    , m_fAddHeight(0.f)
    , m_fAddRot(0.f)
    , m_fScaleDown(0.f)
{
}

CWyvernRedState_Rest::~CWyvernRedState_Rest()
{
}

HRESULT CWyvernRedState_Rest::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::MONATTACK;

    // 상태에 전이 조건 수치
    m_fPatrolRange = 1.f;  // Patrol 전이
    m_fChaseRange = 10.f; // Chase 전이
    m_fComeBackRange = 20.f; // ComeBack 전이 - 현위치 -> 원 위치
    m_fPlayerTargetRange = 10.f; // ComeBack 전이 - 현위치 -> 플레이어 위치
    m_fAttackRange = 3.f;  // Attack 전이
    m_fPosShakeRange = 1.f;

    m_fPosShakeRange *= -0.2f;
    m_fAccTime = 0.f;
    m_fAddHeight += 1.2f;
    m_fAddRot += 0.3f;
    m_fScaleDown -= 0.01;

    //m_vOriginPos = m


    return S_OK;
}

STATE_TYPE CWyvernRedState_Rest::Update_State(const _float& fTimeDelta)
{
    // Component Info
    
    //Monster - Ainmator Com
    CComponent* pOwnerAnimator = dynamic_cast<CAnimator*>(m_pOwner->Get_OwnerObject()->Get_Component(COMPONENT_TYPE::ANIMATOR, COMPONENTID::ID_STATIC));

    // Monster - Ai Com
    CComponent* pOwnerAI = dynamic_cast<CAIComponent*>(m_pOwner->Get_OwnerObject()->Get_Component(COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));
   
    // Monster - Transform Com
    CTransform* pOwnerTransform = m_pOwner->Get_OwnerObject()->Get_Transform();

    // Player - Transform Com
    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
    NULL_CHECK_MSG(pPlayerTransform, L"PlayerTransform nullptr");


    // Info 

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


    // Setting 

    // Dir Vector
    _vec3       vDir = vPlayerPos - vOwnerPos;            // 방향 벡터 [플레이어 - 몬스터]
    _vec3       vOriginDir = vOwnerOriginPos - vOwnerPos; // 방향 벡터 [원위치 - 몬스터]

    // Distance
    _float      fPlayerDistance = (D3DXVec3Length(&vDir));       // 플레이어와의 거리
    _float      fOriginDistance = (D3DXVec3Length(&vOriginDir)); // 원 위치와의 거리

 
     

#pragma region State Change


    //// BACK_ MONREST 전이
    //if (vOwnerDir.z > 0)
    //{
    //   // cout <<  "back monattack 전이" << endl;
    //    return STATE_TYPE::BACK_MONREST;
    //}

    m_fAccTime += fTimeDelta;

    if (m_fAccTime >= 1.5f)  // 몇 초 후 전이 조건
    {
        m_fAccTime = 0.f;
        // Attack 전이 
        if (fPlayerDistance <= m_fAttackRange)
        {
            m_fAccTime = 0.f;
            //cout << "attack 전이" << endl;
            //pOwnerTransform->Set_Scale({(vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
            return STATE_TYPE::MONATTACK;
        }
    
        // CHASE 전이 조건
       if (fPlayerDistance <= m_fChaseRange)
        {
            m_fAccTime = 0.f;
            // cout << "chase  전이" << endl;
            // pOwnerTransform->Set_Scale({ (vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
            return STATE_TYPE::CHASE;
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
        // COMEBACK 전이 조건
        if (fOriginDistance >= m_fComeBackRange || fPlayerDistance > m_fPlayerTargetRange)
        {
            m_fAccTime = 0.f;
            // cout << "COMBACK  전이" << endl
            //pOwnerTransform->Set_Scale({ (vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
            return STATE_TYPE::COMEBACK;
        }
    }
    
    return STATE_TYPE::MONREST;


#pragma endregion

}

void CWyvernRedState_Rest::LateUpdate_State()
{

}

void CWyvernRedState_Rest::Render_State()
{
    
}

STATE_TYPE CWyvernRedState_Rest::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CWyvernRedState_Rest* CWyvernRedState_Rest::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CWyvernRedState_Rest* pInstance = new CWyvernRedState_Rest(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("HedgehogState Attack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CWyvernRedState_Rest::Free()
{
    __super::Free();
}
