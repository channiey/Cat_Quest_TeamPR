#include "RamState_Rest.h"
#include "Export_Function.h"


CRamState_Rest::CRamState_Rest(LPDIRECT3DDEVICE9 pGraphicDev)
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

CRamState_Rest::~CRamState_Rest()
{
}

HRESULT CRamState_Rest::Ready_State(CStateMachine* pOwner)
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

STATE_TYPE CRamState_Rest::Update_State(const _float& fTimeDelta)
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

    if (m_fAccTime >= 1.5f)  // �� �� �� ���� ����
    {
        // Attack ���� 
        if (fPlayerDistance <= m_fAttackRange)
        {
            m_fAccTime = 0.f;
            //cout << "attack ����" << endl;
            //pOwnerTransform->Set_Scale({(vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
            return STATE_TYPE::MONATTACK;
        }
    
        // CHASE ���� ����
       if (fPlayerDistance <= m_fChaseRange)
        {
            m_fAccTime = 0.f;
            // cout << "chase  ����" << endl;
            // pOwnerTransform->Set_Scale({ (vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
            return STATE_TYPE::CHASE;
        }

        // COMEBACK ���� ����
        if (fOriginDistance >= m_fComeBackRange || fPlayerDistance > m_fPlayerTargetRange)
        {
            m_fAccTime = 0.f;
            // cout << "COMBACK  ����" << endl
            //pOwnerTransform->Set_Scale({ (vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
            return STATE_TYPE::COMEBACK;
        }
    }
    
    return STATE_TYPE::MONREST;


#pragma endregion

}

void CRamState_Rest::LateUpdate_State()
{

}

void CRamState_Rest::Render_State()
{
    
}

STATE_TYPE CRamState_Rest::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CRamState_Rest* CRamState_Rest::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CRamState_Rest* pInstance = new CRamState_Rest(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("HedgehogState Attack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CRamState_Rest::Free()
{
    __super::Free();
}