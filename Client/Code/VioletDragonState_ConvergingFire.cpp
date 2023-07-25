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


    m_bBullet1 = false;
    m_bBullet2 = false;
    m_bBullet3 = false;
    m_bBullet4 = false;

    m_bBullet5 = false;
    m_bBullet6 = false;
    m_bBullet7 = false;
    m_bBullet8 = false;

    m_bBullet9  = false;
    m_bBullet10 = false;
    m_bBullet11 = false;
    m_bBullet12 = false;

    m_bBullet13 = false;
    m_bBullet14 = false;
    m_bBullet15 = false;
    m_bBullet16 = false;

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

    if (m_bBullet1 == false && m_fAccTime >= 0.5f) //1 
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging1", 
            CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x - 8.f , vOwnerPos.y +2.f , vOwnerPos.z -5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet1 = true;
    }


    if (m_bBullet2 == false && m_fAccTime >= 0.6f) //2
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging2", 
            CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x - 6.f , vOwnerPos.y +4.f, vOwnerPos.z -5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet2 = true;
    }


    if (m_bBullet3 == false && m_fAccTime >= 0.7f) //3
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging3", 
            CConvergingFire_Bullet::Create(m_pGraphicDev, {vOwnerPos.x -4.f , vOwnerPos.y + 6.f, vOwnerPos.z -5.f}, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet3 = true;
    }

    if (m_bBullet4 == false && m_fAccTime >= 0.8f) //4
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging4", 
            CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x -2.f , vOwnerPos.y + 8.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet4 = true;
    }


    if (m_bBullet5 == false && m_fAccTime >= 0.9f) //5
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging5", 
            CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 2.f , vOwnerPos.y + 8.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet5 = true;
    }

    if (m_bBullet6 == false && m_fAccTime >= 1.f) //6
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging6", 
            CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 4.f , vOwnerPos.y + 6.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet6 = true;
    }

    if (m_bBullet7 == false && m_fAccTime >= 1.1f) //7
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging7", 
            CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 6.f , vOwnerPos.y + 4.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet7 = true;
    }


    if (m_bBullet8 == false && m_fAccTime >= 1.2f) //8
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging8", 
            CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 8.f , vOwnerPos.y + 2.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet8 = true;
    }


    if (m_bBullet9 == false && m_fAccTime >= 1.3f) //9
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging9", 
            CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 8.f , vOwnerPos.y -2.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet9 = true;
    }

    if (m_bBullet10 == false && m_fAccTime >= 1.4f) //10
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging10", 
            CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x +6.f , vOwnerPos.y -4.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet10 = true;
    }


    if (m_bBullet11 == false && m_fAccTime >= 1.5f) //11
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging11", 
            CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 4.f , vOwnerPos.y - 6.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet11 = true;
    }


    if (m_bBullet12 == false && m_fAccTime >= 1.6f) //12
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging12", 
            CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + 2.f , vOwnerPos.y -8.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet12 = true;
    }

    if (m_bBullet13 == false && m_fAccTime >= 1.7f) //13
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging13", 
            CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x -2.f , vOwnerPos.y -8.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet13 = true;
    }


    if (m_bBullet14 == false && m_fAccTime >= 1.8f) //14
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging14", 
            CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x -4.f , vOwnerPos.y - 6.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet14 = true;
    }


    if (m_bBullet15 == false && m_fAccTime >= 1.9f) //15
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging15", 
            CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x -6.f , vOwnerPos.y -4.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet15 = true;
    }


    if (m_bBullet16 == false && m_fAccTime >= 2.f) //16
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging16", 
            CConvergingFire_Bullet::Create(m_pGraphicDev, { vOwnerPos.x -8.f , vOwnerPos.y -2.f, vOwnerPos.z - 5.f }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet16 = true;
    }


#pragma region State Change

    if (m_fAccTime >= 4.f)
    {
        m_fAccTime = 0.f;

        m_bBullet1 = false;
        m_bBullet2 = false;
        m_bBullet3 = false;
        m_bBullet4 = false;

        m_bBullet5 = false;
        m_bBullet6 = false;
        m_bBullet7 = false;
        m_bBullet8 = false;

        m_bBullet9 = false;
        m_bBullet10 = false;
        m_bBullet11 = false;
        m_bBullet12 = false;

        m_bBullet13 = false;
        m_bBullet14 = false;
        m_bBullet15 = false;
        m_bBullet16 = false;
    
        
        //cout << "번개 전이" << endl;
        return STATE_TYPE::BOSS_BLOODY_THUNDER;
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
