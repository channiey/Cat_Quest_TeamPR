#include "FoxState_bAttack.h"
#include "Export_Function.h"
#include "Chase_Bullet.h"
#include "Player.h"
#include "FoxFire.h"

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



    // 상태에 전이 조건 수치
    m_fPatrolRange = 1.f;  // Patrol 전이
    m_fChaseRange = 10.f; // Chase 전이
    m_fComeBackRange = 20.f; // ComeBack 전이 - 현위치 -> 원 위치
    m_fPlayerTargetRange = 10.f; // ComeBack 전이 - 현위치 -> 플레이어 위치
    m_fAttackRange = 5.f;  // Attack 전이

    m_fAccTime = 0.f;

    m_bFoxFire = false;
    m_fAttackTime = 0.f;

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

    // Monster - RegidBodyCom
   
    CComponent* pOwnerRigid = dynamic_cast<CRigidBody*>(m_pOwner->Get_OwnerObject()->Get_Component(COMPONENT_TYPE::RIGIDBODY, COMPONENTID::ID_DYNAMIC));




    CGameObject* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));

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
    _vec3       vDir = vPlayerPos - vOwnerPos;            // 방향 벡터 [플레이어 - 몬스터]
    _vec3       vOriginDir = vOwnerOriginPos - vOwnerPos; // 방향 벡터 [원위치  - 몬스터]

    // Distance
    _float      fPlayerDistance = (D3DXVec3Length(&vDir));       // 플레이어와의 거리
    _float      fOriginDistance = (D3DXVec3Length(&vOriginDir)); // 원 위치와의 거리

 

    m_fAccTime += fTimeDelta;
    m_fAttackTime += fTimeDelta;

    
    // x 이동 방향에 따라 스케일 전환 
    if (vOwnerPos.x < (vPlayerPos).x && vOwnerScale.x < 0)
    {
        pOwnerTransform->Set_Scale({ -vOwnerScale.x , vOwnerScale.y, vOwnerScale.z });
    }
    else if (vOwnerPos.x > (vPlayerPos).x && vOwnerScale.x > 0)
    {
        pOwnerTransform->Set_Scale({ -vOwnerScale.x , vOwnerScale.y, vOwnerScale.z });
    }



    _vec3    vRunDir = { -vDir.x, 0.f, -vDir.z };

    // 현재 상태의 기능
    if (fPlayerDistance >= 10.f)
    {
        dynamic_cast<CAIComponent*>(pOwnerAI)->Chase_Target(&vPlayerPos, fTimeDelta, vOwnerSpeed);
        pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);
    }

    else if (fPlayerDistance <= 7.f)
    {
        pOwnerTransform->Set_Dir(vRunDir);
        pOwnerTransform->Translate(fTimeDelta * vOwnerSpeed);
    }




    if ( m_fAttackTime >= 1.5f)
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_FoxFire", CFoxFire::Create(m_pGraphicDev, vOwnerPos, vDir, m_pOwner->Get_OwnerObject()));
        m_fAttackTime = 0.f;
       
    }
   





#pragma region State Change

    // COMEBACK 전이 조건
    if (vPlayerPos.z < vOwnerPos.z)
    {

        return STATE_TYPE::MONATTACK;
    }

    
    //m_fAccTime += fTimeDelta;

    if (m_fAccTime >= 2.5f)  // 몇 초 후 전이 조건
    {
        m_fAccTime = 0.f;
        dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Set_MoveSpeed(3.f);
        if (dynamic_cast<CPlayer*>(pPlayer)->Get_Clocking() != true)
        {
            //CHASE 전이 조건
            if (fPlayerDistance <= m_fChaseRange && fPlayerDistance >= m_fAttackRange)
            {
                if (vOwnerDir.z < 0)
                {
                    // cout << "Chase 전이" << endl;
                    // pOwnerTransform->Set_Dir(vec3.zero);
                    return STATE_TYPE::CHASE;
                }
                else
                {
                    // cout << "Back Chase 전이" << endl;
                   //  pOwnerTransform->Set_Dir(vec3.zero);
                    return STATE_TYPE::BACK_CHASE;
                }
            }
        }
            // PATROL 전이 조건
        if (fPlayerDistance >= m_fPlayerTargetRange )
        {
            if (vOwnerDir.z < 0)
            {
                //  cout << "patrol 전이" << endl;
                //  pOwnerTransform->Set_Dir(vec3.zero);
                return STATE_TYPE::PATROL;
            }
            else
            {
                //  cout << "Back patrol 전이" << endl;
                //  pOwnerTransform->Set_Dir(vec3.zero);
                return STATE_TYPE::BACK_PATROL;
            }

        }
        // COMEBACK 전이 조건
        if (fOriginDistance >= m_fComeBackRange && fPlayerDistance > m_fPlayerTargetRange)
        {
            if (vOwnerDir.z < 0)
            {
                // cout << "comback 전이" << endl;
                // pOwnerTransform->Set_Dir(vec3.zero);
                return STATE_TYPE::COMEBACK;
            }
            else
            {
                // cout << "back comback 전이" << endl;
                // pOwnerTransform->Set_Dir(vec3.zero);
                return STATE_TYPE::BACK_COMEBACK;
            }
        }
    }

    if (dynamic_cast<CPlayer*>(pPlayer)->Get_Clocking() == true)
    {
        if (vOwnerDir.z < 0)
        {
            //  cout << "comback 전이" << endl;
             // pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::COMEBACK;
        }
        else
        {
            //  cout << "back comback 전이" << endl;
             // pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_COMEBACK;
        }
    }

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
