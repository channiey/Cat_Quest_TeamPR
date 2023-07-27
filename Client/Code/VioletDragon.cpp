#include "VioletDragon.h"
#include "Export_Function.h"
#include "EventMgr.h"

//State-===
//Front
#include "VioletDragonState_Patrol.h"
#include "VioletDragonState_Chase.h"
#include "VioletDragonState_Attack.h"
#include "VioletDragonState_ComeBack.h"
#include "VioletDragonState_Rest.h"
// Back		
#include "VioletDragonState_bPatrol.h"
#include "VioletDragonState_bChase.h"
#include "VioletDragonState_bAttack.h"
#include "VioletDragonState_bComeBack.h"
#include "VioletDragonState_bRest.h"

// Pattern State===
//FullDown
#include "VioletDragonState_FullDown_Fly.h"
#include "VioletDragonState_FullDown_Down.h"
// ConvergingFire
#include "VioletDragonState_ConvergingFire.h"
// BloodyThunder
#include "VioletDragonState_BloodyThunder.h"
// ShootingStar
#include "VioletDragonState_ShootingStar.h"
// SpreadBullet
#include "VioletDragonState_SpreadBullet.h"
// Create Wyvern
#include "VioletDragonState_CreateWyvern.h"


// Effect
#include "Shadow_Monster.h"
#include "Skill_Monster_CircleAttack.h"
#include "Skill_Boss_FullDown.h"
#include "Skill_Boss_BloodyThunder.h"
#include "BigCircle_Stemp.h"


CVioletDragon::CVioletDragon(LPDIRECT3DDEVICE9 pGraphicDev)
    : CMonster(pGraphicDev, OBJ_ID::MONSTER_VIOLETDRAGON)
{
}

CVioletDragon::CVioletDragon(const CMonster& rhs)
    : CMonster(rhs)
{
}

CVioletDragon::~CVioletDragon()
{
}

HRESULT CVioletDragon::Ready_Object()
{
    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	// MoveInfo
	m_tMoveInfo.fMoveSpeed = 3.f;
	m_tMoveInfo.fRotSpeed = 1.f;

	// Stat Info
	m_tStatInfo.bDead = false;
	m_tStatInfo.fCurHP = 40.f;
	m_tStatInfo.fMaxHP = m_tStatInfo.fCurHP;
	m_tStatInfo.fAD = 10.f;



	// 원래 이미지 크기
	m_vImageSize.x = 5.f;  // 100px = 1.f
	m_vImageSize.y = 5.f;
	m_vImageSize.z = 2.f;   // 고정 값


	// Transform 
	m_pTransformCom->Set_Scale(_vec3{ m_vImageSize.x * 2.f, m_vImageSize.y * 2.f , m_vImageSize.z });
	
	m_pTransformCom->Set_Pos(_vec3{ 350.f, m_pTransformCom->Get_Scale().y, 150.f });

	//m_vOriginPos = m_pTransformCom->Get_Info(INFO_POS);

	m_pTransformCom->Set_Dir({ -1.f, 0.f, 1.f });

	fPatternTime = 1.f;
	m_fAccTime = 0.f;

	m_fJumpingSpeed = 0.05f;
	m_fMaxJumpY = m_pTransformCom->Get_Scale().y + 1.f;


	if (CManagement::GetInstance()->Get_PlayMode() == PLAY_MODE::GAME)
		CEventMgr::GetInstance()->Add_Obj(L"Monster_VioletDragon_Shadow", CShadow_Monster::Create(m_pGraphicDev, this));


	m_bSkill = false;
	m_bFullDown = false;
	m_bBloodyTunder = false;


	// 스킬 생성
	/*m_pSkill = CSkill_Monster_Ice::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(m_pSkill, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Ice", m_pSkill), E_FAIL);*/

	if (PLAY_MODE::GAME == CManagement::GetInstance()->Get_PlayMode())  // 수정시 팀장 보고
	{
		m_pBaseSkill = CSkill_Monster_CircleAttack::Create(m_pGraphicDev, this);
		NULL_CHECK_RETURN(m_pBaseSkill, E_FAIL);
		FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Base", m_pBaseSkill), E_FAIL);

		m_pFullDown = CSkill_Boss_FullDown::Create(m_pGraphicDev, this);
		NULL_CHECK_RETURN(m_pFullDown, E_FAIL);
		FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_FullDown", m_pFullDown), E_FAIL);

		m_pBloodyThunder = CSkill_Boss_BloodyThunder::Create(m_pGraphicDev, this);
		NULL_CHECK_RETURN(m_pBloodyThunder, E_FAIL);
		FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_BloodyThunder", m_pBloodyThunder), E_FAIL);


	}


	// Test Pattern
	//
	// Full Down


#pragma region State Add

	CState* pState;
	// Front ==============================
	// Patrol
	pState = CVioletDragonState_Patrol::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::PATROL, pState);

	// Chase
	pState = CVioletDragonState_Chase::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::CHASE, pState);


	// ComeBack
	pState = CVioletDragonState_ComeBack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::COMEBACK, pState);

	// Attack
	pState = CVioletDragonState_Attack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::MONATTACK, pState);

	// Rest
	pState = CVioletDragonState_Rest::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::MONREST, pState);
	

	// Back ================================
	// Patrol
	pState = CVioletDragonState_bPatrol::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_PATROL, pState);

	// Chase
	pState = CVioletDragonState_bChase::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_CHASE, pState);

	// ComeBack
	pState = CVioletDragonState_bComeBack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_COMEBACK, pState);

	// Attack
	pState = CVioletDragonState_bAttack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_MONATTACK, pState);

	// Rest
	pState = CVioletDragonState_bRest::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_MONREST, pState);
	


	// Pattern ================================	
	
	// Full Down Pattern =============================
	// FullDown - Fly
	pState = CVioletDragonState_FullDown_Fly::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_FULLDOWN_FLY, pState);
	
	//FullDown - Move
	//pState = CVioletDragonState_FullDown_Move::Create(m_pGraphicDev, m_pStateMachineCom);
	//m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_FULLDOWN_Move, pState);

	// FullDown - Down
	pState = CVioletDragonState_FullDown_Down::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_FULLDOWN_DOWN, pState);

	
	// Convergint Fire Pattern =========================
	// Converging Fire
	pState = CVioletDragonState_ConvergingFire::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_CONVERGING_FIRE, pState);

	// Converging Cast
	//pState = CVioletDragonState_ConvergingCast::Create(m_pGraphicDev, m_pStateMachineCom);
	//m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_CONVERGING_CAST, pState);



	// Bloody Thunder Pattern ==========================
	// Bloody Thunder
	pState = CVioletDragonState_BloodyThunder::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_BLOODY_THUNDER, pState);
	// Bloody Cast
	//pState = CVioletDragonState_BloodyCast::Create(m_pGraphicDev, m_pStateMachineCom);
	//m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_BLOODY_CAST, pState);


	// Shooting Star Pattern ===========================
	// Shooting Star
	pState = CVioletDragonState_ShootingStar::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_SHOOTING_STAR, pState);
	// Shooting Cast
	//pState = CVioletDragonState_ShootingCast::Create(m_pGraphicDev, m_pStateMachineCom);
	//m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_SHOOTING_CAST, pState);


	// Spread Bullet Pattern =============================
	// Spread Bullet
	pState = CVioletDragonState_SpreadBullet::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_SPREAD_BULLET, pState);
	// Spread Cast
	//pState = CVioletDragonState_SpreadCast::Create(m_pGraphicDev, m_pStateMachineCom);
	//m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_SPREAD_CAST, pState);


	// Create Wyvern Pattern ==============================
	// Create Wyvern 
	pState = CVioletDragonState_CreateWyvern::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_CREATE_WYVERN, pState);
	// Create Wyvern Cast
	//pState = CVioletDragonState_CreateCast::Create(m_pGraphicDev, m_pStateMachineCom);
	//m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_CREATE_CAST, pState);




#pragma endregion



#pragma region Anim Add

	CAnimation* pAnimation;

	// Front ================================
	// Patrol
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::PATROL)], STATE_TYPE::PATROL, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::PATROL, pAnimation);

	// ComeBack
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::COMEBACK)], STATE_TYPE::COMEBACK, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::COMEBACK, pAnimation);

	// Chase
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::CHASE)], STATE_TYPE::CHASE, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::CHASE, pAnimation);

	// Attack
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::MONATTACK)], STATE_TYPE::MONATTACK, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::MONATTACK, pAnimation);

	// Rest
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::MONREST)], STATE_TYPE::MONREST, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::MONREST, pAnimation);


	// Back ====================================
	// Patrol
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_PATROL)], STATE_TYPE::BACK_PATROL, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_PATROL, pAnimation);

	// ComeBack
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_COMEBACK)], STATE_TYPE::BACK_COMEBACK, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_COMEBACK, pAnimation);

	// Chase
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_CHASE)], STATE_TYPE::BACK_CHASE, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_CHASE, pAnimation);

	// Attack
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_MONATTACK)], STATE_TYPE::BACK_MONATTACK, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_MONATTACK, pAnimation);

	// Rest
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_MONREST)], STATE_TYPE::BACK_MONREST, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_MONREST, pAnimation);



	// Pattern ==================================
	
	// FullDown - Fly
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_FULLDOWN_FLY)], STATE_TYPE::BOSS_FULLDOWN_FLY, 0.08f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_FULLDOWN_FLY, pAnimation);

	// FullDown - Move
	//pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_FULLDOWN_MOVE)], STATE_TYPE::BOSS_FULLDOWN_MOVE, 0.05f, FALSE);
	//m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_FULLDOWN_MOVE, pAnimation);


	// FullDown - Down
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_FULLDOWN_DOWN)], STATE_TYPE::BOSS_FULLDOWN_DOWN, 0.05f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_FULLDOWN_DOWN, pAnimation);



	// Converging Fire
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_CONVERGING_FIRE)], STATE_TYPE::BOSS_CONVERGING_FIRE, 0.05f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_CONVERGING_FIRE, pAnimation);

	//// Converging Cast
	//pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_CONVERGING_CAST)], STATE_TYPE::BOSS_CONVERGING_CAST, 0.05f, FALSE);
	//m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_CONVERGING_CAST, pAnimation);



	// Bloody Thunder
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_BLOODY_THUNDER)], STATE_TYPE::BOSS_BLOODY_THUNDER, 0.05f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_BLOODY_THUNDER, pAnimation);

	//// Bloody Cast
	//pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_BLOODY_CAST)], STATE_TYPE::BOSS_BLOODY_CAST, 0.05f, FALSE);
	//m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_BLOODY_CAST, pAnimation);


	
	// Shooting Star
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_SHOOTING_STAR)], STATE_TYPE::BOSS_SHOOTING_STAR, 0.05f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_SHOOTING_STAR, pAnimation);
	
	//// Shooting Cast
	//pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_SHOOTING_CAST)], STATE_TYPE::BOSS_SHOOTING_CAST, 0.05f, FALSE);
	//m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_SHOOTING_CAST, pAnimation);



	// Spread Bullet 
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_SPREAD_BULLET)], STATE_TYPE::BOSS_SPREAD_BULLET, 0.05f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_SPREAD_BULLET, pAnimation);

	//// Spread Cast
	//pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_CREATE_CAST)], STATE_TYPE::BOSS_CREATE_CAST, 0.05f, FALSE);
	//m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_CREATE_CAST, pAnimation);


	// Creat Wyvern 
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_CREATE_WYVERN)], STATE_TYPE::BOSS_CREATE_WYVERN, 0.05f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_CREATE_WYVERN, pAnimation);

	//// Creat Cast
	//pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_CREATE_CAST)], STATE_TYPE::BOSS_CREATE_CAST, 0.05f, FALSE);
	//m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_CREATE_CAST, pAnimation);






#pragma endregion

	// 애니메이션, 상태 세팅
	m_pStateMachineCom->Set_Animator(m_pAnimatorCom);
	//m_pStateMachineCom->Set_State(STATE_TYPE::PATROL);


	// Test 
	m_pStateMachineCom->Set_State(STATE_TYPE::BOSS_CONVERGING_FIRE);



	m_szName = L"Monster_VioletDragon";

    return S_OK;
}

_int CVioletDragon::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CMonster::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);
	
	if (PLAY_MODE::TOOL == CManagement::GetInstance()->Get_PlayMode())  // 수정시 팀장 보고
	{
		m_pStateMachineCom->Set_State(STATE_TYPE::MONREST);
		m_pStateMachineCom->Get_RealAnimator()->Set_Animation(STATE_TYPE::MONREST);
		return iExit;
	}

	//// Jumping 
	_vec3		vOwnerPos = m_pTransformCom->Get_Info(INFO_POS);
	//float Y = m_pTransformCom->Get_Scale().y;
	//STATE_TYPE eCurType = m_pStateMachineCom->Get_CurState();

	//if (eCurType != STATE_TYPE::MONATTACK && eCurType != STATE_TYPE::BACK_MONATTACK)
	//{

	//	if (vOwnerPos.y < Y || vOwnerPos.y > m_fMaxJumpY )
	//	{
	//		m_fJumpingSpeed *= -1;
	//	}
	//	m_pTransformCom->Translate(DIR_UP, m_fJumpingSpeed, WORLD);

	//}


	// Skill Use
	STATE_TYPE CurState = m_pStateMachineCom->Get_CurState();
	//if (STATE_TYPE::BACK_MONATTACK == CurState ||
	//	STATE_TYPE::MONATTACK == CurState ||
	//	STATE_TYPE::CHASE == CurState ||
	//	STATE_TYPE::BACK_CHASE == CurState)
	//{
	//	m_fAccTime += fTimeDelta;

	//	if (m_fAccTime >= 2.f)
	//	{
	//		m_fAccTime = 0.f;
	//		m_pSkill->Play();
	//		m_bSkill = true;
	//	}
	//}


	// Base Skill Use Condition
	if (STATE_TYPE::BACK_MONATTACK == CurState || STATE_TYPE::MONATTACK == CurState)
	{
		if (!m_bSkill)
		{
			m_pBaseSkill->Play();
			m_bSkill = true;
		}

		if (m_pAnimatorCom->Get_CurAniamtion()->Is_End() || this->m_bActive == false)
		{
			m_pBaseSkill->End();
			m_bSkill = false;
		}

	}


	// Full Down Skill Use Condition
	if (STATE_TYPE::BOSS_FULLDOWN_FLY == CurState && m_pAnimatorCom->Get_CurAniamtion()->Is_End())
	{
		if (!m_bFullDown)
		{
			m_pFullDown->Play();
			m_bFullDown = true;
		}
	}
	if (STATE_TYPE::BOSS_FULLDOWN_DOWN == CurState && m_pAnimatorCom->Get_CurAniamtion()->Is_End())
	{
		if (m_bFullDown)
		{
			m_pFullDown->End();
			m_bFullDown = false;
		}
	}
	if (STATE_TYPE::BOSS_FULLDOWN_DOWN == CurState )
	{
		if (m_pAnimatorCom->Get_CurAniamtion()->Get_CurFrame() == 3)
		{
			CEventMgr::GetInstance()->Add_Obj(L"Monster_Hedgehog_Stemp", CBigCircle_Stemp::Create(m_pGraphicDev, _vec3{ vOwnerPos.x, 0.5f, vOwnerPos.z }));
		}
	}




	// Bloody Thunder Skill Use Condition
	if (STATE_TYPE::BOSS_BLOODY_THUNDER == CurState && m_pAnimatorCom->Get_CurAniamtion()->Is_End())
	{
		m_fAccTime += fTimeDelta;

		if (!m_bBloodyTunder && m_fAccTime <= 1.f)
		{
			dynamic_cast<CSkill_Boss_BloodyThunder*>(m_pBloodyThunder)->Play();
			m_bBloodyTunder = true;
		}
		if ( m_fAccTime >= 2.f && m_bBloodyTunder == true )
		{
			dynamic_cast<CSkill_Boss_BloodyThunder*>(m_pBloodyThunder)->End();
	
			dynamic_cast<CSkill_Boss_BloodyThunder*>(m_pBloodyThunder)->LatePlay();
			//CCameraMgr::GetInstance()->Shake_Camera(0.15, 40);
			m_bBloodyTunder = false;
		}
		if (m_bBloodyTunder == false && m_fAccTime >= 4.f)
		{
			CCameraMgr::GetInstance()->Stop_Shake();
			dynamic_cast<CSkill_Boss_BloodyThunder*>(m_pBloodyThunder)->LateEnd();
			m_fAccTime = 0.f;
		}
		
	}





	
	return iExit;
}

void CVioletDragon::LateUpdate_Object()
{

	__super::LateUpdate_Object();
}

void CVioletDragon::Render_Object()
{
	// 피격 시 red
	if (m_bHit)
	{
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(HITCOLOR_A, HITCOLOR_R, HITCOLOR_G, HITCOLOR_B));
	}
	else
	{
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pStateMachineCom->Render_StateMachine();

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	__super::Render_Object();

	// 원래 색상 상태로 돌리기 
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));


	__super::Render_Object(); // 콜라이더 출력
}

void CVioletDragon::OnCollision_Enter(CGameObject* _pColObj)
{
	__super::OnCollision_Enter(_pColObj);
}

void CVioletDragon::OnCollision_Stay(CGameObject* _pColObj)
{
	__super::OnCollision_Stay(_pColObj);
}

void CVioletDragon::OnCollision_Exit(CGameObject* _pColObj)
{
	__super::OnCollision_Exit(_pColObj);
}

HRESULT CVioletDragon::Add_Component()
{
	CComponent* pComponent = nullptr;

	// Animator
	pComponent = m_pAnimatorCom = dynamic_cast<CAnimator*>(Engine::Clone_Proto(COMPONENT_TYPE::ANIMATOR, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::ANIMATOR, pComponent);

	// AI
	pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);


#pragma region Texture

	// Front ===================================

	pComponent = m_pTextureCom[_uint(STATE_TYPE::PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::CHASE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::COMEBACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::MONATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon_Attack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::MONREST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// Back ==================================

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_CHASE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_COMEBACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_MONATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_VioletDragon_Attack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_MONREST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);




	// Pattern ===================================
	
	// Full Down ===========================
	// Full Down Fly
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_FULLDOWN_FLY)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_FullDown_VioletDragon_Fly", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	
	//// Full Down Move
	//pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_FULLDOWN_MOVE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_FullDown_VioletDragon_Fly", this));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// Full Down Down
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_FULLDOWN_DOWN)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_FullDown_VioletDragon_Down", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// Converging Fire ======================
	// Converging Fire 
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_CONVERGING_FIRE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_FullDown_VioletDragon_Down", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); // 텍스처 수정 필요

	//Converging Fire Cast
	//pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_CONVERGING_CAST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_FullDown_VioletDragon_Down", this));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); // 텍스처 수정 필요


	// Bloody Thunder ===========================
	// Bloody Thunder
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_BLOODY_THUNDER)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_FullDown_VioletDragon_Down", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); // 텍스처 수정 필요
	// Bloody Cast
	//pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_BLOODY_CAST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_FullDown_VioletDragon_Down", this));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); // 텍스처 수정 필요



	// Shooting Star ============================
	// Shooting Star
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_SHOOTING_STAR)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_FullDown_VioletDragon_Down", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); // 텍스처 수정 필요
	// Shooting Cast
	//pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_SHOOTING_CAST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_FullDown_VioletDragon_Down", this));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); // 텍스처 수정 필요



	// Spread Bullet ============================
	// Spread Bullet 
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_SPREAD_BULLET)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_FullDown_VioletDragon_Down", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); // 텍스처 수정 필요
	// Spread Cast
	//pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_SPREAD_CAST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_FullDown_VioletDragon_Down", this));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); // 텍스처 수정 필요



	// Create Wyvern ===========================
	// Create Wyvern 
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_CREATE_WYVERN)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_FullDown_VioletDragon_Down", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); // 텍스처 수정 필요
	// Create Cast
	//pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_CREATE_CAST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_FullDown_VioletDragon_Down", this));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); // 텍스처 수정 필요




#pragma endregion


	return S_OK;
}



CVioletDragon* CVioletDragon::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CVioletDragon* pInstance = new CVioletDragon(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Violet Dragon Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CVioletDragon::Free()
{
	__super::Free();
}
