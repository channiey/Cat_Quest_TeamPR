#include "HedgehogState_bAttack.h"
#include "Export_Function.h"
#include "Player.h"

CHedgehogState_bAttack::CHedgehogState_bAttack(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
    , m_fChaseRange(0.f)
    , m_fComeBackRange(0.f)
    , m_fPatrolRange(0.f)
    , m_fPlayerTargetRange(0.f)
    , m_fAttackRange(0.f)
{
}

CHedgehogState_bAttack::~CHedgehogState_bAttack()
{
}

HRESULT CHedgehogState_bAttack::Ready_State(CStateMachine* pOwner)
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


    return S_OK;
}

STATE_TYPE CHedgehogState_bAttack::Update_State(const _float& fTimeDelta)
{

    // Monster - Ai Com
    CComponent* pOwnerAI = dynamic_cast<CAIComponent*>(m_pOwner->Get_OwnerObject()->Get_Component(COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));
    NULL_CHECK_MSG(pOwnerAI, L"pOwnerAI nullptr");

    // Monster - Transform Com
    CTransform* pOwnerTransform = m_pOwner->Get_OwnerObject()->Get_Transform();
    NULL_CHECK_MSG(pOwnerTransform, L"pOwnerTransform nullptr");

    //Monster - Animator
    CComponent* pOwnerAnimator = dynamic_cast<CAnimator*>(m_pOwner->Get_OwnerObject()->Get_Component(COMPONENT_TYPE::ANIMATOR, COMPONENTID::ID_STATIC));
    NULL_CHECK_MSG(pOwnerAnimator, L"pOwnerAnimator nullptr");

    // Monster - Cur Animation info
    CAnimation* pOwenrCurAnimation = dynamic_cast<CAnimator*>(pOwnerAnimator)->Get_CurAniamtion();
    NULL_CHECK_MSG(pOwenrCurAnimation, L"pOwnerCurAnimation nullptr");


    // Player
    CGameObject* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));
    NULL_CHECK_MSG(pPlayer, L"pPlayer nullptr");

    // Player - Transform Com
    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
    NULL_CHECK_MSG(pPlayerTransform, L"pPlayerTransform nullptr");

    // Monster - Pos
    _vec3       vOwnerPos = pOwnerTransform->Get_Info(INFO_POS);
    NULL_CHECK_MSG(vOwnerPos, L"vOwnerPos nullptr");

    // Mosnter - Origin Pos
    _vec3       vOwnerOriginPos = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_OriginPos();
    NULL_CHECK_MSG(vOwnerOriginPos, L"vOwnerOriginPos nullptr");

    // Monster - Speed
    _float      vOwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;
    NULL_CHECK_MSG(vOwnerSpeed, L"vOwnerSpeed nullptr");

    // Monster - PatternTime
    _float      vOwnerPatternTime = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_PatternTime();
    NULL_CHECK_MSG(vOwnerPatternTime, L"vOwnerPatternTime nullptr");

    // Monster - Scale
    _vec3 vOwnerScale = pOwnerTransform->Get_Scale();
    NULL_CHECK_MSG(vOwnerScale, L"vOwnerScale nullptr");

    // Monster - Dir
    _vec3 vOwnerDir = pOwnerTransform->Get_Dir();
    NULL_CHECK_MSG(vOwnerDir, L"vOwnerDir nullptr");

    // Player - Pos
    _vec3       vPlayerPos;
    vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);
    NULL_CHECK_MSG(pPlayerTransform, L"pPlayerTransform nullptr");


    // Dir Vector
    _vec3       vDir = vPlayerPos - vOwnerPos;            // 방향 벡터 [플레이어 - 몬스터]
    _vec3       vOriginDir = vOwnerOriginPos - vOwnerPos; // 방향 벡터 [원위치  - 몬스터]

    // Distance
    _float      fPlayerDistance = (D3DXVec3Length(&vDir));       // 플레이어와의 거리
    _float      fOriginDistance = (D3DXVec3Length(&vOriginDir)); // 원 위치와의 거리





#pragma region State Change
   
    // Attack 은 무조건 Rest로 간다                                                    
    
    if (dynamic_cast<CAnimator*>(pOwnerAnimator)->Get_CurAniamtion()->Is_End())
    {

        return STATE_TYPE::BACK_MONREST;

    }
    return STATE_TYPE::BACK_MONATTACK;


#pragma endregion

  
}

void CHedgehogState_bAttack::LateUpdate_State()
{

}

void CHedgehogState_bAttack::Render_State()
{
    
}

STATE_TYPE CHedgehogState_bAttack::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CHedgehogState_bAttack* CHedgehogState_bAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CHedgehogState_bAttack* pInstance = new CHedgehogState_bAttack(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Test State Attack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CHedgehogState_bAttack::Free()
{
    __super::Free();
}
