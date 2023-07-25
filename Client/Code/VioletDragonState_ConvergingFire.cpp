#include "VioletDragonState_ConvergingFire.h"
#include "Export_Function.h"
#include "Monster.h"
#include "Player.h"
#include "ConvergingFire_Bullet.h"
#include "EventMgr.h"

CVioletDragonState_ConvergingFire::CVioletDragonState_ConvergingFire(LPDIRECT3DDEVICE9 pGraphicDev)
	:CState(pGraphicDev)
	, m_fAccTime(0.f)
{
}

CVioletDragonState_ConvergingFire::~CVioletDragonState_ConvergingFire()
{
}

HRESULT CVioletDragonState_ConvergingFire::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BOSS_CONVERGING_FIRE;

    m_fAccTime = 0.f;

    m_bFirst = false;
    m_bSecond = false;
    m_bThird = false;
    m_bFourth = false;
    m_bFivth = false;
    m_bSixth = false;
    m_bSeventh = false;
    m_Eighth = false;


    return S_OK;
}

STATE_TYPE CVioletDragonState_ConvergingFire::Update_State(const _float& fTimeDelta)
{     
    // Monster - Ai Com
    CComponent* pOwnerAI = dynamic_cast<CAIComponent*>(m_pOwner->Get_OwnerObject()->Get_Component(COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));
    NULL_CHECK_MSG(pOwnerAI, L"pOwnerAI nullptr");

    // Monster - Transform Com
    CTransform* pOwnerTransform = m_pOwner->Get_OwnerObject()->Get_Transform();
    NULL_CHECK_MSG(pOwnerTransform, L"pOwnerTransform nullptr");

    //Monster - Animator
    CComponent* pOwnerAnimator = dynamic_cast<CAnimator*>(m_pOwner->Get_OwnerObject()->Get_Component(COMPONENT_TYPE::ANIMATOR, COMPONENTID::ID_STATIC));
    NULL_CHECK_MSG(pOwnerAnimator, L"pOwnerAnimator nullptr");

    // Monster - Cur Animation info
    CAnimation* pOwenrCurAnimation = dynamic_cast<CAnimator*>(pOwnerAnimator)->Get_CurAniamtion();
    NULL_CHECK_MSG(pOwenrCurAnimation, L"pOwnerCurAnimation nullptr");


    // Player
    CGameObject* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));
    NULL_CHECK_MSG(pPlayer, L"pPlayer nullptr");

    // Player - Transform Com
    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
    NULL_CHECK_MSG(pPlayerTransform, L"pPlayerTransform nullptr");

    // Monster - Pos
    _vec3       vOwnerPos = pOwnerTransform->Get_Info(INFO_POS);
    NULL_CHECK_MSG(vOwnerPos, L"vOwnerPos nullptr");

    // Mosnter - Origin Pos
    _vec3       vOwnerOriginPos = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_OriginPos();
    NULL_CHECK_MSG(vOwnerOriginPos, L"vOwnerOriginPos nullptr");

    // Monster - Speed
    _float      vOwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;
    NULL_CHECK_MSG(vOwnerSpeed, L"vOwnerSpeed nullptr");

    // Monster - PatternTime
    _float      vOwnerPatternTime = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_PatternTime();
    NULL_CHECK_MSG(vOwnerPatternTime, L"vOwnerPatternTime nullptr");

    // Monster - Scale
    _vec3 vOwnerScale = pOwnerTransform->Get_Scale();
    NULL_CHECK_MSG(vOwnerScale, L"vOwnerScale nullptr");

    // Monster - Dir
    _vec3 vOwnerDir = pOwnerTransform->Get_Dir();
    NULL_CHECK_MSG(vOwnerDir, L"vOwnerDir nullptr");

    // Player - Pos
    _vec3       vPlayerPos;
    vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);
    NULL_CHECK_MSG(pPlayerTransform, L"pPlayerTransform nullptr");



    m_fAccTime += fTimeDelta;

    if (m_bFirst == false && m_fAccTime >= 0.5f) //1 
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging1", CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x - 6.f , vOwnerPos.y +4.f , vOwnerPos.z -5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bFirst = true;
    }


    if (m_bSecond == false && m_fAccTime >= 0.7f) //2
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging2", CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x - 4.f , vOwnerPos.y +6.f, vOwnerPos.z -5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bSecond = true;
    }


    if (m_bThird == false && m_fAccTime >= 0.9f) //3
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging3", CConvergingFire_Bullet::Create(m_pGraphicDev, {vOwnerPos.x +4.f , vOwnerPos.y + 6.f, vOwnerPos.z -5.f}, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bThird = true;
    }


    if (m_bFourth == false  && m_fAccTime >= 1.1f) //4
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging4", CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 6.f, vOwnerPos.y + 4.f , vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bFourth = true;
    }


    if (m_bFivth == false &&  m_fAccTime >= 1.3f) //5
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging5", CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 6.f, vOwnerPos.y -4.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bFivth = true;
    }


    if (m_bSixth == false && m_fAccTime >= 1.5f) //6
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging6", CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 4.f , vOwnerPos.y -6.f , vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bSixth = true;
    }


    if (m_bSeventh == false && m_fAccTime >= 1.7f) //7
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging7", CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x -4.f, vOwnerPos.y -6.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bSeventh = true;
    }

    if (m_Eighth == false && m_fAccTime >= 1.9f) //8
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging8", CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x -6.f, vOwnerPos.y -4.f, vOwnerPos.z - 7.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_Eighth = true;
    }

 










#pragma region State Change

    if (m_fAccTime >= 5.f)
    {
        m_bFirst = false;
        m_bSecond = false;
        m_bThird = false;
        m_bFourth = false;
        m_bFivth = false;
        m_bSixth = false;
        m_bSeventh = false;
        m_Eighth = false;

        m_fAccTime = 0.f;
        return STATE_TYPE::BOSS_FULLDOWN_FLY;
    }

    return STATE_TYPE::BOSS_CONVERGING_FIRE;

#pragma endregion


}


void CVioletDragonState_ConvergingFire::LateUpdate_State()
{
}

void CVioletDragonState_ConvergingFire::Render_State()
{
}

STATE_TYPE CVioletDragonState_ConvergingFire::Key_Input(const _float& fTimeDelta)
{
    return m_eState;
}

CVioletDragonState_ConvergingFire* CVioletDragonState_ConvergingFire::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CVioletDragonState_ConvergingFire* pInstance = new CVioletDragonState_ConvergingFire(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("VioletDragonState Converging_Fire Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CVioletDragonState_ConvergingFire::Free()
{
}
