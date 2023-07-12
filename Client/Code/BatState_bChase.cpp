#include "BatState_bChase.h"
#include "Export_Function.h"


CBatState_bChase::CBatState_bChase(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
{
}

CBatState_bChase::~CBatState_bChase()
{
}

HRESULT CBatState_bChase::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BACK_CHASE;
    return S_OK;
}

STATE_TYPE CBatState_bChase::Update_State(const _float& fTimeDelta)
{
  
    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
  

    CTransform* pOwnerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Bat", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
 
    _float OwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;

    _vec3 OwnerOriginPos = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_OriginPos();


    _vec3	vPlayerPos;
    vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);

    _vec3	vOwnerPos;
    vOwnerPos = pOwnerTransform->Get_Info(INFO_POS);


    _vec3		vDir;
    vDir = vPlayerPos- vOwnerPos;
    _float fDistance = (D3DXVec3Length(&vDir)); // 플레이어와의 거리

    _vec3       vOriginDir;
    vOriginDir = OwnerOriginPos - vOwnerPos;
    _float fOriginDistance = (D3DXVec3Length(&vOriginDir)); // 원 위치와의 거리


    // 기능
    CAIComponent* pOwnerAI = dynamic_cast<CAIComponent*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Bat", COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));
    pOwnerAI->Chase_Target(&vPlayerPos, fTimeDelta, OwnerSpeed);
   
    pOwnerTransform->Translate(fTimeDelta * OwnerSpeed);



    _vec3 vOwnerDir = pOwnerTransform->Get_Dir();
   
    if (vOwnerDir.z < 0)
    {
        cout << "Chase  전이" << endl;
        return STATE_TYPE::CHASE;
    }


    if (fOriginDistance >= 50.f  &&  fDistance > 15.f   )// Comeback 전이 조건
    {
 
        if (vOwnerDir.z < 0)
        {
            cout << "COMBACK  전이" << endl;
            pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::COMEBACK;
        }
        else
        {
            cout << "back COMBACK  전이" << endl;
            pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_COMEBACK;
        }
    }
    

    if (fDistance >= 20.f)  // PATROL 전이 조건
    {
        if (vOwnerDir.z < 0)
        {
            cout << "patrol  전이" << endl;
            pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::PATROL;
        }
        else
        {
            cout << "back patrol  전이" << endl;
            pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_PATROL;

        }

    }

  

    if (fDistance <= 1.f) // Attack 전이 조건
    {
        if (vOwnerDir.z < 0)
        {
            cout << "attack  전이" << endl;
            pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::MONATTACK;
        }
        else
        {
            cout << "back attack  전이" << endl;
            pOwnerTransform->Set_Dir(vec3.zero);
            return STATE_TYPE::BACK_MONATTACK;
        }


    }
 
   
     return STATE_TYPE::BACK_CHASE;
    

  
}

void CBatState_bChase::LateUpdate_State()
{
    
}

void CBatState_bChase::Render_State()
{
   
}

STATE_TYPE CBatState_bChase::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CBatState_bChase* CBatState_bChase::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CBatState_bChase* pInstance = new CBatState_bChase(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("BatState Chase Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CBatState_bChase::Free()
{
    __super::Free();
}
