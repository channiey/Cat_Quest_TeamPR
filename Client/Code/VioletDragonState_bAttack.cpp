#include "VioletDragonState_bAttack.h"
#include "Export_Function.h"
#include "Player.h"

#include "VioletDragon.h"

CVioletDragonState_bAttack::CVioletDragonState_bAttack(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
    , m_fChaseRange(0.f)
    , m_fComeBackRange(0.f)
    , m_fPatrolRange(0.f)
    , m_fPlayerTargetRange(0.f)
    , m_fAttackRange(0.f)
{
}

CVioletDragonState_bAttack::~CVioletDragonState_bAttack()
{
}

HRESULT CVioletDragonState_bAttack::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BACK_MONATTACK;

    // 상태에 전이 조건 수치
    m_fPatrolRange = 5.f;  // Patrol 전이
    m_fChaseRange = 20.f; // Chase 전이
    m_fComeBackRange = 30.f; // ComeBack 전이 - 현위치 -> 원 위치
    m_fPlayerTargetRange = 20.f; // ComeBack 전이 - 현위치 -> 플레이어 위치
    m_fAttackRange = 10.f;  // Attack 전이



    return S_OK;
}

STATE_TYPE CVioletDragonState_bAttack::Update_State(const _float& fTimeDelta)
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

    //Monster - Cur HP Condition
    _bool Owner_bHP80 = dynamic_cast<CVioletDragon*>(m_pOwner->Get_OwnerObject())->Get_HP80();
    _bool Owner_bHP50 = dynamic_cast<CVioletDragon*>(m_pOwner->Get_OwnerObject())->Get_HP50();
    _bool Owner_bHP20 = dynamic_cast<CVioletDragon*>(m_pOwner->Get_OwnerObject())->Get_HP20();


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




#pragma region State Change
    // back Attack 우선순위
    // attack - chase - Comeback

    if (dynamic_cast<CAnimator*>(pOwnerAnimator)->Get_CurAniamtion()->Is_End())
    {

        if (Owner_bHP80 == true && Owner_bHP50 == false && Owner_bHP20 == false)
        {
            return STATE_TYPE::BOSS_FULLDOWN_FLY;
        }


        return STATE_TYPE::BACK_MONREST;

    }
    return STATE_TYPE::BACK_MONATTACK;


#pragma endregion

  
}

void CVioletDragonState_bAttack::LateUpdate_State()
{

}

void CVioletDragonState_bAttack::Render_State()
{
    
}

STATE_TYPE CVioletDragonState_bAttack::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CVioletDragonState_bAttack* CVioletDragonState_bAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CVioletDragonState_bAttack* pInstance = new CVioletDragonState_bAttack(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("WyvernState Attack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CVioletDragonState_bAttack::Free()
{
    __super::Free();
}
