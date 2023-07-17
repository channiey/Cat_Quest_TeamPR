#include "RamState_Chase.h"
#include "Export_Function.h"


CRamState_Chase::CRamState_Chase(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
    , m_fChaseRange(0.f)
    , m_fComeBackRange(0.f)
    , m_fPatrolRange(0.f)
    , m_fPlayerTargetRange(0.f)
    , m_fAttackRange(0.f)
{
}

CRamState_Chase::~CRamState_Chase()
{
}

HRESULT CRamState_Chase::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::CHASE;

    // ���¿� ���� ���� ��ġ
    m_fPatrolRange = 1.f;  // Patrol ����
    m_fChaseRange = 10.f; // Chase ����
    m_fComeBackRange = 20.f; // ComeBack ���� - ����ġ -> �� ��ġ
    m_fPlayerTargetRange = 10.f; // ComeBack ���� - ����ġ -> �÷��̾� ��ġ
    m_fAttackRange = 3.f;  // Attack ����

    return S_OK;
}

STATE_TYPE CRamState_Chase::Update_State(const _float& fTimeDelta)
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
    // CHASE �켱����
    // Attack - Comeback - Patrol


    // ATTACK ���� ����
    if (fPlayerDistance <= m_fAttackRange)
    {
        //cout << "attack ����" << endl;
       // pOwnerTransform->Set_Dir(vec3.zero);
       // pOwnerTransform->Set_Scale({ (vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
        return STATE_TYPE::MONATTACK;
    }
    // COMEBACK ���� ����
    if (fOriginDistance >= m_fComeBackRange && fPlayerDistance > m_fPlayerTargetRange)
    {
        //cout << "COMBACK  ����" << endl;
       // pOwnerTransform->Set_Dir(vec3.zero);
       // pOwnerTransform->Set_Scale({ (vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
        return STATE_TYPE::COMEBACK;
    }
    // PATROL ���� ����
    if (fPlayerDistance >= m_fPlayerTargetRange && fOriginDistance <= m_fPatrolRange)
    {
        //cout << "patrol ����" << endl;
       // pOwnerTransform->Set_Dir(vec3.zero);
        //pOwnerTransform->Set_Scale({ (vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
        return STATE_TYPE::PATROL;
    }
    // Default 
    return STATE_TYPE::CHASE;


#pragma endregion
  
}

void CRamState_Chase::LateUpdate_State()
{
    
}

void CRamState_Chase::Render_State()
{


}

STATE_TYPE CRamState_Chase::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CRamState_Chase* CRamState_Chase::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CRamState_Chase* pInstance = new CRamState_Chase(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("RamState Chase Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CRamState_Chase::Free()
{
    __super::Free();
}
