#include "VioletDragonState_HellFire.h"
#include "Player.h"
#include "Export_Function.h"
#include "EventMgr.h"
#include "Monster.h"
#include "Effect_Boss_Thunder.h"
#include "Skill_Boss_BloodyThunder.h"
#include "VioletDragon.h"

CVioletDragonState_HellFire::CVioletDragonState_HellFire(LPDIRECT3DDEVICE9 pGraphicDev)
	:CState(pGraphicDev)
	, m_fAccTime(0.f)
{
	
}

CVioletDragonState_HellFire::~CVioletDragonState_HellFire()
{
}

HRESULT CVioletDragonState_HellFire::Ready_State(CStateMachine* pOwner)
{

	if (nullptr != pOwner)
	{
		m_pOwner = pOwner;
	}
	m_eState = STATE_TYPE::BOSS_HELLFIRE;

	m_fAccTime = 0.f;

    m_bThunder = false;

	return S_OK;
}

STATE_TYPE CVioletDragonState_HellFire::Update_State(const _float& fTimeDelta)
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


    //Monster - Cur HP Condition
    _bool Owner_bHP90 = dynamic_cast<CVioletDragon*>(m_pOwner->Get_OwnerObject())->Get_HP90();
    _bool Owner_bHP60 = dynamic_cast<CVioletDragon*>(m_pOwner->Get_OwnerObject())->Get_HP60();
    _bool Owner_bHP30 = dynamic_cast<CVioletDragon*>(m_pOwner->Get_OwnerObject())->Get_HP30();



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






    if (dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_StatInfo().bDead == true)
    {
        return STATE_TYPE::BOSSDEAD;
    }


    m_fAccTime += fTimeDelta;
   

    if (m_fAccTime >= 4.f)
    {
        m_fAccTime = 0.f;

 
        return STATE_TYPE::BOSS_BLUE_CAST;
    }

	return STATE_TYPE::BOSS_HELLFIRE;
}

void CVioletDragonState_HellFire::LateUpdate_State()
{

}

void CVioletDragonState_HellFire::Render_State()
{
}

STATE_TYPE CVioletDragonState_HellFire::Key_Input(const _float& fTimeDelta)
{
	return m_eState;
}

CVioletDragonState_HellFire* CVioletDragonState_HellFire::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CVioletDragonState_HellFire* pInstance = new CVioletDragonState_HellFire(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("VioletDragonState BloodyThunder Create Failed");
		return nullptr;

	}

	return pInstance;
}

void CVioletDragonState_HellFire::Free()
{
    __super::Free();
}
