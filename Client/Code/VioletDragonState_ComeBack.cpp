#include "VioletDragonState_ComeBack.h"
#include "Export_Function.h"


CVioletDragonState_ComeBack::CVioletDragonState_ComeBack(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
    , m_fChaseRange(0.f)
    , m_fComeBackRange(0.f)
    , m_fPatrolRange(0.f)
    , m_fPlayerTargetRange(0.f)
    , m_fAttackRange(0.f)
{
}

CVioletDragonState_ComeBack::~CVioletDragonState_ComeBack()
{
}

HRESULT CVioletDragonState_ComeBack::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::COMEBACK;

    // 상태에 전이 조건 수치
    m_fPatrolRange = 5.f;  // Patrol 전이
    m_fChaseRange = 20.f; // Chase 전이
    m_fComeBackRange = 10.f; // ComeBack 전이 - 현위치 -> 원 위치
    m_fPlayerTargetRange = 20.f; // ComeBack 전이 - 현위치 -> 플레이어 위치
    m_fAttackRange = 10.f;  // Attack 전이


    return S_OK;
}

STATE_TYPE CVioletDragonState_ComeBack::Update_State(const _float& fTimeDelta)
{
  
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
    _vec3 vOwnerDir = pOwnerTransform->Get_Dir();
    // Player - Pos
    _vec3	    vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);


    // Dir Vector
    _vec3       vDir = vPlayerPos - vOwnerPos;            // 방향 벡터 [플레이어 - 몬스터]
    _vec3       vOriginDir = vOwnerOriginPos - vOwnerPos; // 방향 벡터 [원위치  - 몬스터]

    // Distance
    _float      fPlayerDistance = (D3DXVec3Length(&vDir));       // 플레이어와의 거리
    _float      fOriginDistance = (D3DXVec3Length(&vOriginDir)); // 원 위치와의 거리


    // 현재 상태의 기능
    dynamic_cast<CAIComponent*>(pOwnerAI)->Chase_Target(&vOwnerOriginPos, fTimeDelta, vOwnerSpeed);
    pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);
  

#pragma region State Change

    // COMBACK 우선순위
    // back comback - Patrol - CHASE - ATTACK


  


    // PATROL 전이 조건
    if (fOriginDistance <= m_fPatrolRange)
    {
        if (vOwnerDir.z < 0)
        {
        //    cout << "patrol 전이" << endl;
           // pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::PATROL;
        }
        else
        {
        //    cout << "Back patrol 전이" << endl;
           // pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_PATROL;
        }
    }

    // CHASE 전이 조건
    if (fPlayerDistance <= m_fChaseRange)
    {
        if (vOwnerDir.z < 0)
        {
         //   cout << "Chase 전이" << endl;
         //   pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::CHASE;
        }
        else
        {
        //    cout << "Back Chase 전이" << endl;
        //    pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_CHASE;
        }
    }
    // Attack 전이 조건
    if (fPlayerDistance <= m_fAttackRange)
    {
        if (vOwnerDir.z < 0)
        {
         //   cout << "attack 전이" << endl;
          //  pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::MONATTACK;
        }
        else
        {
        //    cout << "back attack 전이" << endl;
        //    pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_MONATTACK;
        }
    }

    // BACK_COMEBACK 전이 조건
    if (vOwnerDir.z > 0)
    {
        //  cout << "Back comeback 전이" << endl;
        return STATE_TYPE::BACK_COMEBACK;
    }

    // Default
    return STATE_TYPE::COMEBACK;

#pragma endregion

}

void CVioletDragonState_ComeBack::LateUpdate_State()
{
    
}

void CVioletDragonState_ComeBack::Render_State()
{
   

}

STATE_TYPE CVioletDragonState_ComeBack::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CVioletDragonState_ComeBack* CVioletDragonState_ComeBack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CVioletDragonState_ComeBack* pInstance = new CVioletDragonState_ComeBack(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("WyvernState ComeBack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CVioletDragonState_ComeBack::Free()
{
    __super::Free();
}
