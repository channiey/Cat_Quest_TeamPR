#include "FoxState_bAttack.h"
#include "Export_Function.h"




CFoxState_bAttack::CFoxState_bAttack(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
{
}

CFoxState_bAttack::~CFoxState_bAttack()
{
}

HRESULT CFoxState_bAttack::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BACK_MONATTACK;



    // ���¿� ���� ���� ��ġ
    m_fPatrolRange = 1.f;  // Patrol ����
    m_fChaseRange = 10.f; // Chase ����
    m_fComeBackRange = 20.f; // ComeBack ���� - ����ġ -> �� ��ġ
    m_fPlayerTargetRange = 10.f; // ComeBack ���� - ����ġ -> �÷��̾� ��ġ
    m_fAttackRange = 5.f;  // Attack ����

    m_fAccTime = 0.f;

    return S_OK;
}

STATE_TYPE CFoxState_bAttack::Update_State(const _float& fTimeDelta)
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
    
    m_fAccTime += fTimeDelta;

    if (fPlayerDistance <= 10.f)
    {
        pOwnerTransform->Set_Dir({ -vDir.x , 0.f, -vDir.z });
        pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);
    }





#pragma region State Change
    
    //m_fAccTime += fTimeDelta;

    //if (m_fAccTime >= 1.5f)  // �� �� �� ���� ����
    //{
        // CHASE ���� ����
        //if (fPlayerDistance <= m_fChaseRange && fPlayerDistance >= m_fAttackRange)
        //{
        //    if (vOwnerDir.z < 0)
        //    {
        //        // cout << "Chase ����" << endl;
        //        // pOwnerTransform->Set_Dir(vec3.zero);
        //        return STATE_TYPE::CHASE;
        //    }
        //    else
        //    {
        //        // cout << "Back Chase ����" << endl;
        //       //  pOwnerTransform->Set_Dir(vec3.zero);
        //        return STATE_TYPE::BACK_CHASE;
        //    }
        //}
            // PATROL ���� ����
        if (fPlayerDistance >= m_fPlayerTargetRange )
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
        if (fOriginDistance >= m_fComeBackRange && fPlayerDistance > m_fPlayerTargetRange)
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
    //}

    return STATE_TYPE::BACK_MONATTACK;
#pragma endregion

  
}

void CFoxState_bAttack::LateUpdate_State()
{

}

void CFoxState_bAttack::Render_State()
{
    
}

STATE_TYPE CFoxState_bAttack::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CFoxState_bAttack* CFoxState_bAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CFoxState_bAttack* pInstance = new CFoxState_bAttack(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("BatState Attack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CFoxState_bAttack::Free()
{
    __super::Free();
}
