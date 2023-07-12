#include "SquirrelState_ComeBack.h"
#include "Export_Function.h"


CSquirrelState_ComeBack::CSquirrelState_ComeBack(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
{
}

CSquirrelState_ComeBack::~CSquirrelState_ComeBack()
{
}

HRESULT CSquirrelState_ComeBack::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::COMEBACK;
    return S_OK;
}

STATE_TYPE CSquirrelState_ComeBack::Update_State(const _float& fTimeDelta)
{
  
    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));


    CTransform* pOwnerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Squirrel", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));

    _float OwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;

    _vec3 OwnerOriginPos = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_OriginPos();


    _vec3	vPlayerPos;
   vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);

    _vec3	vOwnerPos;
    vOwnerPos = pOwnerTransform->Get_Info(INFO_POS);


    _vec3		vDir;
    vDir = vPlayerPos - vOwnerPos;
    _float fDistance = (D3DXVec3Length(&vDir)); // 플레이어와의 거리

    _vec3       vOriginDir;
    vOriginDir = OwnerOriginPos - vOwnerPos;
    _float fOriginDistance = (D3DXVec3Length(&vOriginDir)); // 원 위치와의 거리


    CAIComponent* pOwnerAI = dynamic_cast<CAIComponent*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Squirrel", COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));
   
    // 기능
    pOwnerTransform->Set_Dir(vec3.zero);
    pOwnerAI->Chase_Target(&OwnerOriginPos, fTimeDelta, OwnerSpeed);
   
    pOwnerTransform->Translate(fTimeDelta * OwnerSpeed);
  
    if (fOriginDistance <= 5.f)    // PATROL 전이 조건
    {
       // cout << "patrol 전이" << endl;
      pOwnerTransform->Set_Dir(vec3.zero);
      return STATE_TYPE::PATROL; 
    }
    
    if (fDistance <= 10.f)   // CHASE 전이 조건
    {
        //cout << "chase  전이" << endl;
        pOwnerTransform->Set_Dir(vec3.zero);
        return STATE_TYPE::CHASE;
    }
    
    if (fDistance <= 5.f)  // Attack 전이 조건
    {
        //cout << "attack 전이" << endl;
        pOwnerTransform->Set_Dir(vec3.zero);
        return STATE_TYPE::FRONT_ATTACK;
    }
  
        return STATE_TYPE::COMEBACK;



}

void CSquirrelState_ComeBack::LateUpdate_State()
{
    
}

void CSquirrelState_ComeBack::Render_State()
{
  

}

STATE_TYPE CSquirrelState_ComeBack::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CSquirrelState_ComeBack* CSquirrelState_ComeBack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CSquirrelState_ComeBack* pInstance = new CSquirrelState_ComeBack(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Squirrel ComeBack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CSquirrelState_ComeBack::Free()
{
    __super::Free();
}
