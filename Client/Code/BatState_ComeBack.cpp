#include "BatState_ComeBack.h"
#include "Export_Function.h"


CBatState_ComeBack::CBatState_ComeBack(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
    , m_fChaseRange(0.f)
    , m_fComeBackRange(0.f)
    , m_fPatrolRange(0.f)
    , m_fPlayerTargetRange(0.f)
    , m_fAttackRange(0.f)
{
}

CBatState_ComeBack::~CBatState_ComeBack()
{
}

HRESULT CBatState_ComeBack::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::COMEBACK;

    // ���¿� ���� ���� ��ġ
    m_fPatrolRange = 1.f;  // Patrol ����
    m_fChaseRange = 10.f; // Chase ����
    m_fComeBackRange = 20.f; // ComeBack ���� - ����ġ -> �� ��ġ
    m_fPlayerTargetRange = 10.f; // ComeBack ���� - ����ġ -> �÷��̾� ��ġ
    m_fAttackRange = 3.f;  // Attack ����


    return S_OK;
}

STATE_TYPE CBatState_ComeBack::Update_State(const _float& fTimeDelta)
{
    // Monster - Ai Com
    CAIComponent* pOwnerAI = dynamic_cast<CAIComponent*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Bat", COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));

    // Monster - Transform Com
    CTransform* pOwnerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Bat", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));

    // Player - Transform Com
    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));

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
    _vec3       vDir = vPlayerPos - vOwnerPos;            // ���� ���� [�÷��̾� - ����]
    _vec3       vOriginDir = vOwnerOriginPos - vOwnerPos; // ���� ���� [����ġ  - ����]

    // Distance
    _float      fPlayerDistance = (D3DXVec3Length(&vDir));       // �÷��̾���� �Ÿ�
    _float      fOriginDistance = (D3DXVec3Length(&vOriginDir)); // �� ��ġ���� �Ÿ�


    // ���� ������ ���
    pOwnerAI->Chase_Target(&vOwnerOriginPos, fTimeDelta, vOwnerSpeed);
    pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);

#pragma region State Change

    // COMBACK �켱����
    // back comback - Patrol - CHASE - ATTACK


    // BACK_COMEBACK ���� ����
    if (vOwnerDir.z > 0)
    {
        //cout << "Back comeback ����" << endl;
        return STATE_TYPE::BACK_COMEBACK;
    }


    // PATROL ���� ����
    if (fOriginDistance <= m_fPatrolRange)
    {
        if (vOwnerDir.z < 0)
        {
          //  cout << "patrol ����" << endl;
            pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::PATROL;
        }
        else
        {
           // cout << "Back patrol ����" << endl;
            pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_PATROL;
        }
    }

    // CHASE ���� ����
    if (fPlayerDistance <= m_fChaseRange)
    {
        if (vOwnerDir.z < 0)
        {
           // cout << "Chase ����" << endl;
            pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::CHASE;
        }
        else
        {
            //cout << "Back Chase ����" << endl;
            pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_CHASE;
        }
    }
    // Attack ���� ����
    if (fPlayerDistance <= m_fAttackRange)
    {
        if (vOwnerDir.z < 0)
        {
           // cout << "attack ����" << endl;
            pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::MONATTACK;
        }
        else
        {
           // cout << "back attack ����" << endl;
            pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_MONATTACK;
        }
    }

    // Default
    return STATE_TYPE::COMEBACK;

#pragma endregion


}
 

 

void CBatState_ComeBack::LateUpdate_State()
{
    
}

void CBatState_ComeBack::Render_State()
{
   

}

STATE_TYPE CBatState_ComeBack::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CBatState_ComeBack* CBatState_ComeBack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CBatState_ComeBack* pInstance = new CBatState_ComeBack(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Bat ComeBack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CBatState_ComeBack::Free()
{
    __super::Free();
}
