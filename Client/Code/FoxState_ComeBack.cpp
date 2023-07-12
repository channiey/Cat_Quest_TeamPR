#include "FoxState_ComeBack.h"
#include "Export_Function.h"


CFoxState_ComeBack::CFoxState_ComeBack(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
{
}

CFoxState_ComeBack::~CFoxState_ComeBack()
{
}

HRESULT CFoxState_ComeBack::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::COMEBACK;
    return S_OK;
}

STATE_TYPE CFoxState_ComeBack::Update_State(const _float& fTimeDelta)
{
  
    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));


    CTransform* pOwnerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Fox", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));

    _float OwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;

    _vec3 OwnerOriginPos = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_OriginPos();


    _vec3	vPlayerPos;
   vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);

    _vec3	vOwnerPos;
    vOwnerPos = pOwnerTransform->Get_Info(INFO_POS);


    _vec3		vDir;
    vDir = vPlayerPos - vOwnerPos;
    _float fDistance = (D3DXVec3Length(&vDir)); // �÷��̾���� �Ÿ�

    _vec3       vOriginDir;
    vOriginDir = OwnerOriginPos - vOwnerPos;
    _float fOriginDistance = (D3DXVec3Length(&vOriginDir)); // �� ��ġ���� �Ÿ�


    CAIComponent* pOwnerAI = dynamic_cast<CAIComponent*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Fox", COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));
   
    // ���
    pOwnerTransform->Set_Dir(vec3.zero);
    pOwnerAI->Chase_Target(&OwnerOriginPos, fTimeDelta, OwnerSpeed);
   
    pOwnerTransform->Translate(fTimeDelta * OwnerSpeed);
  
    if (fOriginDistance <= 5.f)    // PATROL ���� ����
    {
        cout << "patrol ����" << endl;
      pOwnerTransform->Set_Dir(vec3.zero);
      return STATE_TYPE::PATROL; 
    }
    
    if (fDistance <= 10.f)   // CHASE ���� ����
    {
        cout << "chase  ����" << endl;
        pOwnerTransform->Set_Dir(vec3.zero);
        return STATE_TYPE::CHASE;
    }
    
    if (fDistance <= 5.f)  // Attack ���� ����
    {
        cout << "attack ����" << endl;
        pOwnerTransform->Set_Dir(vec3.zero);
        return STATE_TYPE::FRONT_ATTACK;
    }
  
        return STATE_TYPE::COMEBACK;



}

void CFoxState_ComeBack::LateUpdate_State()
{
    
}

void CFoxState_ComeBack::Render_State()
{
  

}

STATE_TYPE CFoxState_ComeBack::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CFoxState_ComeBack* CFoxState_ComeBack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CFoxState_ComeBack* pInstance = new CFoxState_ComeBack(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Fox ComeBack Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CFoxState_ComeBack::Free()
{
    __super::Free();
}
