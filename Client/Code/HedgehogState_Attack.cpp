#include "HedgehogState_Attack.h"
#include "Export_Function.h"


CHedgegohState_Attack::CHedgegohState_Attack(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
    , m_fChaseRange(0.f)
    , m_fComeBackRange(0.f)
    , m_fPatrolRange(0.f)
    , m_fPlayerTargetRange(0.f)
    , m_fAttackRange(0.f)
    , m_fPosShakeRange(0.f)
{
}

CHedgegohState_Attack::~CHedgegohState_Attack()
{
}

HRESULT CHedgegohState_Attack::Ready_State(CStateMachine* pOwner)
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

    m_fPosShakeRange = 0.1f;

    return S_OK;
}

STATE_TYPE CHedgegohState_Attack::Update_State(const _float& fTimeDelta)
{
    
    // Monster - Ai Com
    CAIComponent* pOwnerAI = dynamic_cast<CAIComponent*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Hedgehog", COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));

    // Monster - Transform Com
    CTransform* pOwnerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Hedgehog", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));

    // Player - Transform Com
    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));

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

 

    m_fAccTime += Engine::Get_TimeDelta(L"Timer_FPS65");
    
    
    pOwnerTransform->Set_Pos({ vOwnerPos.x +(-1 * m_fPosShakeRange), vOwnerPos.y, vOwnerPos.z });

    if (m_fAccTime <= 1.f)
    {
       
        m_fAccTime = 0.f;
    }




  /*  if (m_fShakeTime <= m_fAccTime)
    {
        Stop_Shake();
        return;
    }

    _vec3 vShakeDelta{ _float(rand() % (_int)m_fIntensity),
                            _float(rand() % (_int)m_fIntensity),
                            0.f };

    vShakeDelta *= 0.01f;

    m_tVspace.Eye += vShakeDelta;

    m_tVspace.LookAt += vShakeDelta;*/







#pragma region State Change
    // Attack �켱����
    // chase - Comeback

    // CHASE ���� ����
    if (fPlayerDistance >= m_fChaseRange)
    {
        //cout << "chase  ����" << endl;
        pOwnerTransform->Set_Scale({(vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
        return STATE_TYPE::CHASE;
    }

    // COMEBACK ���� ����
    if (fOriginDistance >= m_fComeBackRange && fPlayerDistance > m_fPlayerTargetRange)
    {
        //cout << "COMBACK  ����" << endl;
        pOwnerTransform->Set_Scale({ (vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
        return STATE_TYPE::COMEBACK;
    }


    return STATE_TYPE::MONATTACK;



#pragma endregion

}

void CHedgegohState_Attack::LateUpdate_State()
{

}

void CHedgegohState_Attack::Render_State()
{
    
}

STATE_TYPE CHedgegohState_Attack::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CHedgegohState_Attack* CHedgegohState_Attack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CHedgegohState_Attack* pInstance = new CHedgegohState_Attack(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("HedgehogState Attack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CHedgegohState_Attack::Free()
{
    __super::Free();
}
