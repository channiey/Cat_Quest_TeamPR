#include "SerpentState_Rest.h"
#include "Export_Function.h"


CSerpentState_Rest::CSerpentState_Rest(LPDIRECT3DDEVICE9 pGraphicDev)
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

CSerpentState_Rest::~CSerpentState_Rest()
{
}

HRESULT CSerpentState_Rest::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::MONATTACK;

    // ���¿� ���� ���� ��ġ
    m_fPatrolRange = 1.f;  // Patrol ����
    m_fChaseRange = 10.f; // Chase ����
    m_fComeBackRange = 20.f; // ComeBack ���� - ����ġ -> �� ��ġ
    m_fPlayerTargetRange = 10.f; // ComeBack ���� - ����ġ -> �÷��̾� ��ġ
    m_fAttackRange = 3.f;  // Attack ����
    m_fPosShakeRange = 1.f;

    m_fPosShakeRange *= -0.2f;
    m_fAccTime = 0.f;
    m_fAddHeight += 1.2f;
    m_fAddRot += 0.3f;
    m_fScaleDown -= 0.01;

    //m_vOriginPos = m


    return S_OK;
}

STATE_TYPE CSerpentState_Rest::Update_State(const _float& fTimeDelta)
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
    _vec3       vDir = vPlayerPos - vOwnerPos;            // ���� ���� [�÷��̾� - ����]
    _vec3       vOriginDir = vOwnerOriginPos - vOwnerPos; // ���� ���� [����ġ - ����]

    // Distance
    _float      fPlayerDistance = (D3DXVec3Length(&vDir));       // �÷��̾���� �Ÿ�
    _float      fOriginDistance = (D3DXVec3Length(&vOriginDir)); // �� ��ġ���� �Ÿ�

 
     

#pragma region State Change


    //// BACK_ MONREST ����
    //if (vOwnerDir.z > 0)
    //{
    //   // cout <<  "back monattack ����" << endl;
    //    return STATE_TYPE::BACK_MONREST;
    //}

    m_fAccTime += fTimeDelta;

    if (m_fAccTime >= 1.f)  // �� �� �� ���� ����
    {
        m_fAccTime = 0.f;
        // CHASE ���� ����
        if (fPlayerDistance <= m_fChaseRange)
        {
            if (vOwnerDir.z < 0)
            {
                // cout << "Chase ����" << endl;
                // pOwnerTransform->Set_Dir(vec3.zero);
                return STATE_TYPE::CHASE;
            }
            else
            {
                // cout << "Back Chase ����" << endl;
               //  pOwnerTransform->Set_Dir(vec3.zero);
                return STATE_TYPE::BACK_CHASE;
            }
        }
        // PATROL ���� ����
        if (fPlayerDistance >= m_fPlayerTargetRange && fOriginDistance <= m_fPatrolRange)
        {
            if (vOwnerDir.z < 0)
            {
                //  cout << "patrol ����" << endl;
                //  pOwnerTransform->Set_Dir(vec3.zero);
                return STATE_TYPE::PATROL;
            }
            else
            {
                //  cout << "Back patrol ����" << endl;
                //  pOwnerTransform->Set_Dir(vec3.zero);
                return STATE_TYPE::BACK_PATROL;
            }

        }
        // COMEBACK ���� ����
        if (fOriginDistance >= m_fComeBackRange || fPlayerDistance > m_fPlayerTargetRange)
        {
            if (vOwnerDir.z < 0)
            {
                // cout << "comback ����" << endl;
                // pOwnerTransform->Set_Dir(vec3.zero);
                return STATE_TYPE::COMEBACK;
            }
            else
            {
                // cout << "back comback ����" << endl;
                // pOwnerTransform->Set_Dir(vec3.zero);
                return STATE_TYPE::BACK_COMEBACK;
            }
        }

        //  ATTACK ���� ����
        if (fPlayerDistance <= m_fAttackRange)
        {
            if (vOwnerDir.z < 0)
            {
                // cout << "attack ����" << endl;
                // pOwnerTransform->Set_Dir(vec3.zero);
                return STATE_TYPE::MONATTACK;
            }
            else
            {
                // cout << "back attack ����" << endl;
               //  pOwnerTransform->Set_Dir(vec3.zero);
                return STATE_TYPE::BACK_MONATTACK;
            }
        }

    }
    
    return STATE_TYPE::MONREST;


#pragma endregion

}

void CSerpentState_Rest::LateUpdate_State()
{

}

void CSerpentState_Rest::Render_State()
{
    
}

STATE_TYPE CSerpentState_Rest::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CSerpentState_Rest* CSerpentState_Rest::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CSerpentState_Rest* pInstance = new CSerpentState_Rest(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("HedgehogState Attack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CSerpentState_Rest::Free()
{
    __super::Free();
}
