#include "HedgehogState_ComeBack.h"
#include "Export_Function.h"


CHedgehogState_ComeBack::CHedgehogState_ComeBack(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
{
}

CHedgehogState_ComeBack::~CHedgehogState_ComeBack()
{
}

HRESULT CHedgehogState_ComeBack::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::COMEBACK;
    return S_OK;
}

STATE_TYPE CHedgehogState_ComeBack::Update_State(const _float& fTimeDelta)
{
   //m_pTransformCom->Translate(fTimeDelta * m_tMoveInfo.fMoveSpeed);
    
  
    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));

    CTransform* pOwnerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Hedgehog", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));

   
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


    CAIComponent* pOwnerAI = dynamic_cast<CAIComponent*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Hedgehog", COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));
   
    // 기능
    pOwnerTransform->Set_Dir(vec3.zero);
    pOwnerAI->Chase_Target(&OwnerOriginPos, fTimeDelta, OwnerSpeed);
    pOwnerTransform->Translate(fTimeDelta * OwnerSpeed);


    _vec3 vOwnerScale = pOwnerTransform->Get_Scale();

 

    if (fOriginDistance <= 5.f)    // PATROL 전이 조건
    {
        cout << "patrol 전이" << endl;
      pOwnerTransform->Set_Dir(vec3.zero);
      pOwnerTransform->Set_Scale({ fabs(vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
      return STATE_TYPE::PATROL; 
    }
    
    if (fDistance <= 5.f)   // CHASE 전이 조건
    {
        cout << "chase  전이" << endl;
        pOwnerTransform->Set_Dir(vec3.zero);
        pOwnerTransform->Set_Scale({ fabs(vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
        return STATE_TYPE::CHASE;
    }
    
    if (fDistance <= 5.f)  // Attack 전이 조건
    {
        cout << "attack 전이" << endl;
        pOwnerTransform->Set_Dir(vec3.zero);
        pOwnerTransform->Set_Scale({ fabs(vOwnerScale.x) , vOwnerScale.y, vOwnerScale.z });
        return STATE_TYPE::FRONT_ATTACK;
    }
  
        return STATE_TYPE::COMEBACK;



}

void CHedgehogState_ComeBack::LateUpdate_State()
{
    
}

void CHedgehogState_ComeBack::Render_State()
{
    cout << "고슴도치 patro 상태" << endl;

}

STATE_TYPE CHedgehogState_ComeBack::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CHedgehogState_ComeBack* CHedgehogState_ComeBack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CHedgehogState_ComeBack* pInstance = new CHedgehogState_ComeBack(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Hedgehog fAttackState Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CHedgehogState_ComeBack::Free()
{
    __super::Free();
}
