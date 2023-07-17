#include "RamState_ComeBack.h"
#include "Export_Function.h"


CRamState_ComeBack::CRamState_ComeBack(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
    , m_fChaseRange(0.f)
    , m_fComeBackRange(0.f)
    , m_fPatrolRange(0.f)
    , m_fPlayerTargetRange(0.f)
    , m_fAttackRange(0.f)
{
}

CRamState_ComeBack::~CRamState_ComeBack()
{
}

HRESULT CRamState_ComeBack::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::COMEBACK;

    // 상태에 전이 조건 수치
    m_fPatrolRange = 1.f;  // Patrol 전이
    m_fChaseRange = 10.f; // Chase 전이
    m_fComeBackRange = 20.f; // ComeBack 전이 - 현위치 -> 원 위치
    m_fPlayerTargetRange = 10.f; // ComeBack 전이 - 현위치 -> 플레이어 위치
    m_fAttackRange = 3.f;  // Attack 전이

    return S_OK;
}

STATE_TYPE CRamState_ComeBack::Update_State(const _float& fTimeDelta)
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
    // Moanter - Scale
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
    // Patrol - CHASE - ATTACK

    //  // BACK_COMEBACK 전이 조건
    //if (vOwnerDir.z > 0)
    //{
    //    //cout << "Back comeback 전이" << endl;
    //    return STATE_TYPE::BACK_COMEBACK;
    //}



    // PATROL 전이 조건
    if (fOriginDistance <= m_fPatrolRange)
    {
        //cout << "patrol 전이" << endl;
       // pOwnerTransform->Set_Dir(vec3.zero);
       // pOwnerTransform->Set_Scale({ fabs(vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
        return STATE_TYPE::PATROL;
    }

    // CHASE 전이 조건
    if (fPlayerDistance <= m_fChaseRange)
    {
        //cout << "chase  전이" << endl;
       // pOwnerTransform->Set_Dir(vec3.zero);
       // pOwnerTransform->Set_Scale({ (vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
        return STATE_TYPE::CHASE;
    }
    // Attack 전이 조건
    if (fPlayerDistance <= m_fAttackRange)
    {
        //cout << "attack 전이" << endl;
        //pOwnerTransform->Set_Dir(vec3.zero);
       // pOwnerTransform->Set_Scale({ (vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
        return STATE_TYPE::MONATTACK;
    }

    // Default
    return STATE_TYPE::COMEBACK;

#pragma endregion


}

void CRamState_ComeBack::LateUpdate_State()
{
    
}

void CRamState_ComeBack::Render_State()
{
   

}

STATE_TYPE CRamState_ComeBack::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CRamState_ComeBack* CRamState_ComeBack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CRamState_ComeBack* pInstance = new CRamState_ComeBack(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("RamState ComeBack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CRamState_ComeBack::Free()
{
    __super::Free();
}
