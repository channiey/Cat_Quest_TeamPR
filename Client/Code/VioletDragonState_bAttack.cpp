#include "VioletDragonState_bAttack.h"
#include "Export_Function.h"


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

    // ���¿� ���� ���� ��ġ
    m_fPatrolRange = 5.f;  // Patrol ����
    m_fChaseRange = 20.f; // Chase ����
    m_fComeBackRange = 10.f; // ComeBack ���� - ����ġ -> �� ��ġ
    m_fPlayerTargetRange = 20.f; // ComeBack ���� - ����ġ -> �÷��̾� ��ġ
    m_fAttackRange = 10.f;  // Attack ����



    return S_OK;
}

STATE_TYPE CVioletDragonState_bAttack::Update_State(const _float& fTimeDelta)
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
    _vec3       vDir = vPlayerPos - vOwnerPos;            // ���� ���� [�÷��̾� - ����]
    _vec3       vOriginDir = vOwnerOriginPos - vOwnerPos; // ���� ���� [����ġ  - ����]

    // Distance
    _float      fPlayerDistance = (D3DXVec3Length(&vDir));       // �÷��̾���� �Ÿ�
    _float      fOriginDistance = (D3DXVec3Length(&vOriginDir)); // �� ��ġ���� �Ÿ�



   // ���� ������ ���
   /* pOwnerTransform->Set_Dir(vec3.zero);
    pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);*/




#pragma region State Change
    // back Attack �켱����
    // attack - chase - Comeback

    if (dynamic_cast<CAnimator*>(pOwnerAnimator)->Get_CurAniamtion()->Is_End())
    {
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