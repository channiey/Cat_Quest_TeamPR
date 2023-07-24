#include "FoxState_Attack.h"
#include "Export_Function.h"
#include "FoxFire.h"

CFoxState_Attack::CFoxState_Attack(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
    , m_fChaseRange(0.f)
    , m_fComeBackRange(0.f)
    , m_fPatrolRange(0.f)
    , m_fPlayerTargetRange(0.f)
    , m_fAttackRange(0.f)
{
}

CFoxState_Attack::~CFoxState_Attack()
{
}

HRESULT CFoxState_Attack::Ready_State(CStateMachine* pOwner)
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
    m_fAttackRange = 5.f;  // Attack ����

    m_fAccTime = 0.f;
    return S_OK;
}

STATE_TYPE CFoxState_Attack::Update_State(const _float& fTimeDelta)
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

    m_fAccTime += fTimeDelta;

   // ���� ������ ���
    
    if (fPlayerDistance <= 10.f)
    {
        pOwnerTransform->Set_Dir({ -vDir.x , 0.f, -vDir.z });
        pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);
    }
 
    if (m_fAccTime >= 2.f)
    {
       // CEventMgr::GetInstance()->Add_Obj(L"Projectile_FoxFire", CFoxFire::Create(m_pGraphicDev, vOwnerPos, vOwnerDir));
        m_fAccTime = 0.f;
    }


#pragma region State Change


    //m_fAccTime += fTimeDelta;

    //if (m_fAccTime >= 1.5f)  // �� �� �� ���� ����
    //{
        //// CHASE ���� ����
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

    return STATE_TYPE::MONATTACK;


#pragma endregion

  
}

void CFoxState_Attack::LateUpdate_State()
{

}

void CFoxState_Attack::Render_State()
{
    
}

STATE_TYPE CFoxState_Attack::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CFoxState_Attack* CFoxState_Attack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CFoxState_Attack* pInstance = new CFoxState_Attack(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("FoxState Attack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CFoxState_Attack::Free()
{
    __super::Free();
}
