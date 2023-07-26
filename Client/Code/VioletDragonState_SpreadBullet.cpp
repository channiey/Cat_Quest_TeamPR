#include "VioletDragonState_SpreadBullet.h"
#include "Export_Function.h"
#include "Monster.h"
#include "Player.h"
#include "ComeBack_Bullet.h"

#include "EventMgr.h"

CVioletDragonState_SpreadBullet::CVioletDragonState_SpreadBullet(LPDIRECT3DDEVICE9 pGraphicDev)
	:CState(pGraphicDev)
	, m_fAccTime(0.f)
    //, m_pBullet1(nullptr)
{
}

CVioletDragonState_SpreadBullet::~CVioletDragonState_SpreadBullet()
{
}

HRESULT CVioletDragonState_SpreadBullet::Ready_State(CStateMachine* pOwner)
{
    if (nullptr != pOwner)
    {
        m_pOwner = pOwner;
    }
    m_eState = STATE_TYPE::BOSS_SPREAD_BULLET;

    m_fAccTime = 0.f;

    m_fBulletCount = 5.f;
    m_fRadius = 10.f;

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

   // m_pBullet1 = nullptr;


    return S_OK;
}

STATE_TYPE CVioletDragonState_SpreadBullet::Update_State(const _float& fTimeDelta)
{     
    STATE_TYPE eState = m_eState;

    // Monstre Component ==============================
    // Monster - Ai Com
    CComponent* pOwnerAI = dynamic_cast<CAIComponent*>(m_pOwner->Get_OwnerObject()->Get_Component(COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));
    NULL_CHECK_RETURN(pOwnerAI, eState);

    // Monster - Transform Com
    CTransform* pOwnerTransform = m_pOwner->Get_OwnerObject()->Get_Transform();
    NULL_CHECK_RETURN(pOwnerTransform, eState);

    //Monster - Animator
    CComponent* pOwnerAnimator = dynamic_cast<CAnimator*>(m_pOwner->Get_OwnerObject()->Get_Component(COMPONENT_TYPE::ANIMATOR, COMPONENTID::ID_STATIC));
    NULL_CHECK_RETURN(pOwnerAnimator, eState);

    // Monster - Cur Animation
    CAnimation* pOwenrCurAnimation = dynamic_cast<CAnimator*>(pOwnerAnimator)->Get_CurAniamtion();
    NULL_CHECK_RETURN(pOwenrCurAnimation, eState);

    // Player Component ==============================
    // Player
    CGameObject* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));
    NULL_CHECK_RETURN(pPlayer, eState);

    // Player - Transform Com
    CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
    NULL_CHECK_RETURN(pPlayerTransform, eState);


    // GET INFO =================================================================
    // Monster - Pos
    _vec3       vOwnerPos = pOwnerTransform->Get_Info(INFO_POS);
    NULL_CHECK_RETURN(vOwnerPos, eState);

    // Mosnter - Origin Pos
    _vec3       vOwnerOriginPos = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_OriginPos();
    NULL_CHECK_RETURN(vOwnerOriginPos, eState);

    // Monster - Speed
    _float      vOwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;
    NULL_CHECK_RETURN(vOwnerSpeed, eState);

    // Monster - PatternTime
    _float      vOwnerPatternTime = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_PatternTime();
    NULL_CHECK_RETURN(vOwnerPatternTime, eState);

    // Monster - Scale
    _vec3 vOwnerScale = pOwnerTransform->Get_Scale();
    NULL_CHECK_RETURN(vOwnerScale, eState);

    // Monster - Dir
    _vec3 vOwnerDir = pOwnerTransform->Get_Dir();
    NULL_CHECK_RETURN(vOwnerDir, eState);

    // Player - Pos
    _vec3       vPlayerPos;
    vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);
    NULL_CHECK_RETURN(pPlayerTransform, eState);


    // Setting Value
    // Dir Vector
    _vec3       vDir = vPlayerPos - vOwnerPos;            // 방향 벡터 [플레이어 - 몬스터]
    _vec3       vOriginDir = vOwnerOriginPos - vOwnerPos; // 방향 벡터 [원위치  - 몬스터]

    // Distance
    _float      fPlayerDistance = (D3DXVec3Length(&vDir));       // 플레이어와의 거리
    _float      fOriginDistance = (D3DXVec3Length(&vOriginDir)); // 원 위치와의 거리


#pragma region Cur State Function

    m_fAccTime += fTimeDelta;

   // float angle = PI * 2 / numberOfSatellites;

    _float fYPosMul;
    fYPosMul = 1.5;



    if (m_bBullet1 == false && m_fAccTime >= 0.3f) //1 
    {
     /*   m_pBullet1 = CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(0)) , vPlayerPos.y * fYPosMul , vOwnerPos.z + _float(m_fRadius * sin(0)) }, pPlayer, m_pOwner->Get_OwnerObject());
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging1", m_pBullet1);
        m_bBullet1 = true;*/

        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging1",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(0)) , vPlayerPos.y * fYPosMul, vOwnerPos.z + _float(m_fRadius * sin(0)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet1 = true; 

    }
  
    if (m_bBullet2 == false && m_fAccTime >= 0.4f) //2
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging2",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(10)) , vPlayerPos.y * fYPosMul, vOwnerPos.z + _float(m_fRadius * sin(10)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet2 = true;
    }


    if (m_bBullet3 == false && m_fAccTime >= 0.5f) //3
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging3",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(20)) , vPlayerPos.y * fYPosMul, vOwnerPos.z + _float(m_fRadius * sin(20)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet3 = true;
    }

    if (m_bBullet4 == false && m_fAccTime >= 0.6f) //4
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging4",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(30)) , vPlayerPos.y * fYPosMul,  vOwnerPos.z + _float(m_fRadius * sin(30)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet4 = true;
    }


    if (m_bBullet5 == false && m_fAccTime >= 0.7f) //5
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging5",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius *cos(40)) , vPlayerPos.y * fYPosMul,vOwnerPos.z + _float(m_fRadius* sin(40)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet5 = true;
    }


    if (m_bBullet6 == false && m_fAccTime >= 0.8f) //6
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging6",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(50)) , vPlayerPos.y * fYPosMul,vOwnerPos.z + _float(m_fRadius * sin(50)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet6 = true;
    }

    if (m_bBullet7 == false && m_fAccTime >= 0.9f) //7
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging7",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(60)) , vPlayerPos.y * fYPosMul ,vOwnerPos.z + _float(m_fRadius * sin(60)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet7 = true;
    }


    if (m_bBullet8 == false && m_fAccTime >= 1.f) //8
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging8",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(70)) , vPlayerPos.y * fYPosMul,vOwnerPos.z + _float(m_fRadius * sin(70)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet8 = true;
    }


    if (m_bBullet9 == false && m_fAccTime >= 1.1f) //9
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging9",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(80)) , vPlayerPos.y * fYPosMul ,vOwnerPos.z + _float(m_fRadius * sin(80)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet9 = true;
    }

    if (m_bBullet10 == false && m_fAccTime >= 1.2f) //10
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging10",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(90)) , vPlayerPos.y * fYPosMul ,vOwnerPos.z + _float(m_fRadius * sin(90)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet10 = true;
    }


    if (m_bBullet11 == false && m_fAccTime >= 1.3f) //11
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging11",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(100)) , vPlayerPos.y * fYPosMul ,vOwnerPos.z + _float(m_fRadius * sin(100)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet11 = true;
    }


    if (m_bBullet12 == false && m_fAccTime >= 1.4f) //12
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging12",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(110)) , vPlayerPos.y * fYPosMul ,vOwnerPos.z + _float(m_fRadius * sin(110)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet12 = true;
    }

    if (m_bBullet13 == false && m_fAccTime >= 1.5f) //13
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging13",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(120)) , vPlayerPos.y * fYPosMul ,vOwnerPos.z + _float(m_fRadius * sin(120)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet13 = true;
    }


    if (m_bBullet14 == false && m_fAccTime >= 1.6f) //14
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging14",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(130)) , vPlayerPos.y * fYPosMul ,vOwnerPos.z + _float(m_fRadius * sin(130)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet14 = true;
    }


    if (m_bBullet15 == false && m_fAccTime >= 1.7f) //15
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging15",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(140)) , vPlayerPos.y * fYPosMul ,vOwnerPos.z + _float(m_fRadius * sin(140)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet15 = true;
    }


    if (m_bBullet16 == false && m_fAccTime >= 1.8f) //16
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging16",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(150)) , vPlayerPos.y * fYPosMul,vOwnerPos.z + _float(m_fRadius * sin(150)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet16 = true;
    }


    if (m_bBullet17 == false && m_fAccTime >= 1.9f) //17
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging17",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(160)) , vPlayerPos.y * fYPosMul ,vOwnerPos.z + _float(m_fRadius * sin(160)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet17 = true;
    }

    if (m_bBullet18 == false && m_fAccTime >= 2.0f) //18
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging18",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(170)) , vPlayerPos.y * fYPosMul ,vOwnerPos.z + _float(m_fRadius * sin(170)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet18 = true;
    }

    if (m_bBullet19 == false && m_fAccTime >= 2.1f) //19
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging19",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(180)) , vPlayerPos.y * fYPosMul ,vOwnerPos.z + _float(m_fRadius * sin(180)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet19 = true;
    }

    if (m_bBullet20 == false && m_fAccTime >= 2.2f) //20
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging20",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(190)) , vPlayerPos.y * fYPosMul,vOwnerPos.z + _float(m_fRadius * sin(190)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet20 = true;
    }

    if (m_bBullet21 == false && m_fAccTime >= 2.3f) //21
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging21",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(200)) , vPlayerPos.y * fYPosMul ,vOwnerPos.z + _float(m_fRadius * sin(200)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet21 = true;
    }

    if (m_bBullet22 == false && m_fAccTime >= 2.4f) //22
    {
        CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging22",
            CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(210)) , vPlayerPos.y * fYPosMul ,vOwnerPos.z + _float(m_fRadius * sin(210)) }, pPlayer, m_pOwner->Get_OwnerObject()));
        m_bBullet22 = true;
    }

 /*   if (m_fAccTime >= 3.f)
    {
        if (m_pBullet1 == nullptr)
        {
            dynamic_cast<CComBack_Bullet*>(m_pBullet1)->Comeback(fTimeDelta);

        }
    }*/


    //if (m_bBullet23 == false && m_fAccTime >= 2.5f) //23
    //{
    //    CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging23",
    //        CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(220)) , vOwnerPos.y * fYPosMul ,vOwnerPos.z + _float(m_fRadius * sin(220)) }, pPlayer, m_pOwner->Get_OwnerObject()));
    //    m_bBullet23 = true;
    //}

    //if (m_bBullet24 == false && m_fAccTime >= 2.6f) //24
    //{
    //    CEventMgr::GetInstance()->Add_Obj(L"Projectile_Boss_Converging24",
    //        CComBack_Bullet::Create(m_pGraphicDev, { vOwnerPos.x + _float(m_fRadius * cos(230)) , vOwnerPos.y ,vOwnerPos.z + _float(m_fRadius * sin(230)) }, pPlayer, m_pOwner->Get_OwnerObject()));
    //    m_bBullet23 = true;
    //}



#pragma endregion




#pragma region State Change

    if (m_fAccTime >= 5.f)
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
    
        m_bBullet17 = false;
        m_bBullet18 = false;
        m_bBullet19 = false;
        m_bBullet20 = false;

        m_bBullet21 = false;
        m_bBullet22 = false;
        m_bBullet23 = false;
        m_bBullet24 = false;


        //cout << " 전이" << endl;
        return STATE_TYPE::BOSS_SHOOTING_STAR;
    }

    return STATE_TYPE::BOSS_SPREAD_BULLET;

#pragma endregion


}


void CVioletDragonState_SpreadBullet::LateUpdate_State()
{
}

void CVioletDragonState_SpreadBullet::Render_State()
{
}

STATE_TYPE CVioletDragonState_SpreadBullet::Key_Input(const _float& fTimeDelta)
{
    return m_eState;
}

CVioletDragonState_SpreadBullet* CVioletDragonState_SpreadBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
    CVioletDragonState_SpreadBullet* pInstance = new CVioletDragonState_SpreadBullet(pGraphicDev);

    if (FAILED(pInstance->Ready_State(pOwner)))
    {
        Safe_Release(pInstance);
        MSG_BOX("VioletDragonState SpreadBullet Create Failed");
        return nullptr;

    }

    return pInstance;
}

void CVioletDragonState_SpreadBullet::Free()
{
    __super::Free();
}
