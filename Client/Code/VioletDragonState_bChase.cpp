#include "VioletDragonState_bChase.h"
#include "Export_Function.h"


CVioletDragonState_bChase::CVioletDragonState_bChase(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
    , m_fChaseRange(0.f)
    , m_fComeBackRange(0.f)
    , m_fPatrolRange(0.f)
    , m_fPlayerTargetRange(0.f)
    , m_fAttackRange(0.f)
{
}

CVioletDragonState_bChase::~CVioletDragonState_bChase()
{
}

HRESULT CVioletDragonState_bChase::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BACK_CHASE;

    // ���¿� ���� ���� ��ġ
    m_fPatrolRange = 5.f;  // Patrol ����
    m_fChaseRange = 20.f; // Chase ����
    m_fComeBackRange = 10.f; // ComeBack ���� - ����ġ -> �� ��ġ
    m_fPlayerTargetRange = 20.f; // ComeBack ���� - ����ġ -> �÷��̾� ��ġ
    m_fAttackRange = 10.f;  // Attack ����


    return S_OK;
}

STATE_TYPE CVioletDragonState_bChase::Update_State(const _float& fTimeDelta)
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
    dynamic_cast<CAIComponent*>(pOwnerAI)->Chase_Target(&vPlayerPos, fTimeDelta, vOwnerSpeed);
    pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);


#pragma region State Change
    // BACK_CHASE �켱����
    //  Chase - Attack - Comeback - Patrol


    // CHASE ���� ����
    if (vOwnerDir.z < 0)
    {
      //  cout << "Chase  ����" << endl;
        return STATE_TYPE::CHASE;
    }


 
    // COMEBACK ���� ����
    if (fOriginDistance >= m_fComeBackRange && fPlayerDistance > m_fPlayerTargetRange)
    {
        if (vOwnerDir.z < 0)
        {
           // cout << "comback ����" << endl;
          //  pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::COMEBACK;
        }
        else
        {
           // cout << "back comback ����" << endl;
           // pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_COMEBACK;
        }
    }

    // ATTACK ���� ����
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
            //cout << "back attack ����" << endl;
           // pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_MONATTACK;
        }
    }

    // PATROL ���� ����
    if (fPlayerDistance >= m_fPlayerTargetRange && fOriginDistance <= m_fPatrolRange)
    {
        if (vOwnerDir.z < 0)
        {
            //cout << "patrol ����" << endl;
           // pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::PATROL;
        }
        else
        {
            //cout << "Back patrol ����" << endl;
           // pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_PATROL;
        }
    }


    // Default 
    return STATE_TYPE::BACK_CHASE;


#pragma endregion


  
}

void CVioletDragonState_bChase::LateUpdate_State()
{
    
}

void CVioletDragonState_bChase::Render_State()
{
   
}

STATE_TYPE CVioletDragonState_bChase::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CVioletDragonState_bChase* CVioletDragonState_bChase::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CVioletDragonState_bChase* pInstance = new CVioletDragonState_bChase(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("WyvernState Chase Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CVioletDragonState_bChase::Free()
{
    __super::Free();
}