#include "FoxState_Chase.h"
#include "Export_Function.h"


CFoxState_Chase::CFoxState_Chase(LPDIRECT3DDEVICE9 pGraphicDev)
    : CState(pGraphicDev)
    , m_fAccTime(0.f)
{
}

CFoxState_Chase::~CFoxState_Chase()
{
}

HRESULT CFoxState_Chase::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::CHASE;
    return S_OK;
}

STATE_TYPE CFoxState_Chase::Update_State(const _float& fTimeDelta)
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
    vDir = vPlayerPos- vOwnerPos;
    _float fDistance = (D3DXVec3Length(&vDir)); // �÷��̾���� �Ÿ�

    _vec3       vOriginDir;
    vOriginDir = OwnerOriginPos - vOwnerPos;
    _float fOriginDistance = (D3DXVec3Length(&vOriginDir)); // �� ��ġ���� �Ÿ�


    // ���
    CAIComponent* pOwnerAI = dynamic_cast<CAIComponent*>(Engine::Get_Component(OBJ_TYPE::MONSTER, L"Monster_Fox", COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));
    pOwnerAI->Chase_Target(&vPlayerPos, fTimeDelta, OwnerSpeed);
   

    if (fOriginDistance >= 30.f  && fDistance >10.f   )// Comeback ���� ����
    {
        cout << "COMBACK  ����" << endl;
        pOwnerTransform->Set_Dir(vec3.zero);
        return STATE_TYPE::COMEBACK;
    }
    
    if (fDistance >= 20.f)  // PATROL ���� ����
    {
        cout << "patrol ����" << endl;
      pOwnerTransform->Set_Dir(vec3.zero);
      return STATE_TYPE::PATROL; 
    }

  

    if (fDistance <= 5.f) // Attack ���� ����
    {
        cout << "attack ����" << endl;
        pOwnerTransform->Set_Dir(vec3.zero);
        return STATE_TYPE::FRONT_ATTACK;
    }
 
   
     return STATE_TYPE::CHASE;
    

  
}

void CFoxState_Chase::LateUpdate_State()
{
    
}

void CFoxState_Chase::Render_State()
{


}

STATE_TYPE CFoxState_Chase::Key_Input(const _float& fTimeDelta)
{
 
    return m_eState;
}

CFoxState_Chase* CFoxState_Chase::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CFoxState_Chase* pInstance = new CFoxState_Chase(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("FoxState Chase Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CFoxState_Chase::Free()
{
    __super::Free();
}