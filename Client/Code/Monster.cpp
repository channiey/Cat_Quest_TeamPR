#include "stdafx.h"
#include "..\Header\Monster.h"
#include "AIComponent.h"
#include "Export_Function.h"
#include "RangeObj.h"
#include "Player.h"
#include "Mage_Bullet.h"

#include "GoldCoin.h"
#include "ExpCoin.h"

#include "MonHpUI.h"

#include "Skill.h"

// Spirit
#include "MonstSpirit.h"
// CutEffect
#include "MobCutEffect.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::MONSTER, _eID)
	, m_pStateMachineCom(nullptr)
	, m_pAICom(nullptr)
	, fPatternTime(0.f)
	, m_vOriginPos({0.f,0.f,0.f})
	, m_fJumpingSpeed(0.f)
	, m_vImageSize({0.f,0.f,0.f})
	, m_fMaxJumpY(0.f)
	, m_bHit(false)
	, m_bInit(false)
	, m_fAccTime(0.f)
{
	//ZeroMemory(&m_pTextureCom, sizeof(CTexture*) * _uint(STATE_TYPE::TYPEEND));

	ZeroMemory(&m_tMoveInfo, sizeof(MOVEINFO));
	ZeroMemory(&m_tStatInfo, sizeof(STATINFO));
}

CMonster::CMonster(const CMonster& rhs)
	: Engine::CGameObject(rhs)
	, m_tMoveInfo(rhs.m_tMoveInfo)
	, m_tStatInfo(rhs.m_tStatInfo)
	, fPatternTime(rhs.fPatternTime)
	, m_vOriginPos(rhs.m_vOriginPos)
	, m_fJumpingSpeed(rhs.m_fJumpingSpeed)
	, m_vImageSize(rhs.m_vImageSize)
	, m_fMaxJumpY(rhs.m_fMaxJumpY)
	, m_fAccTime(rhs.m_fAccTime)
{

	for (size_t i = 0; i < _uint(_uint(STATE_TYPE::TYPEEND)); ++i)
	{
		m_pTextureCom[i] = rhs.m_pTextureCom[i];
	}

}

CMonster::~CMonster()
{
}

HRESULT CMonster::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	// 각 몬스터에서 배치
	//m_pStateMachineCom->Set_Animator(m_pAnimatorCom);
	//m_pStateMachineCom->Set_State(STATE_TYPE::PATROL);



	// << : Test : Range Test
	CGameObject* pGameObject = nullptr;

	if (PLAY_MODE::GAME == CManagement::GetInstance()->Get_PlayMode())
	{
		pGameObject = CRangeObj::Create(m_pGraphicDev, this, 10.f);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		CEventMgr::GetInstance()->Add_Obj(L"Player_Range_Basic_Attack", pGameObject);
		arrRangeObj[(UINT)RANGE_TYPE::BASIC_ATTACK] = dynamic_cast<CRangeObj*>(pGameObject);


		pGameObject = CMonHpUI::Create(m_pGraphicDev, this);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		CEventMgr::GetInstance()->Add_Obj(L"MonHp_UI", pGameObject);
	}




	return S_OK;
}

Engine::_int CMonster::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	if (PLAY_MODE::TOOL == CManagement::GetInstance()->Get_PlayMode())
	{
		//m_pStateMachineCom->Get_Animator()->Set_Animation(STATE_TYPE::FRONT_IDLE);
		//m_PCurAnimator->Set_Animation(eState);
		//m_pStateMachineCom->Update_StateMachine(fTimeDelta);
		return iExit;
	}

	// Update 에서 한번 불려지게 만듬
	if (!m_bInit)
	{
		m_bInit = true;
		m_vOriginPos = m_pTransformCom->Get_Info(INFO_POS);

		// DATA 파일에 위치랑 달라서 일단 추가함
		m_pTransformCom->Set_Pos({ m_vOriginPos.x, m_pTransformCom->Get_Scale().y,m_vOriginPos.z });
	}


	if (PLAY_MODE::TOOL != CManagement::GetInstance()->Get_PlayMode())
		m_pStateMachineCom->Update_StateMachine(fTimeDelta);


	

	if (true == m_tStatInfo.bDead)
	{
		CEventMgr::GetInstance()->Add_Obj(L"Monster_Spirit", CMonstSpirit::Create(m_pGraphicDev, m_pTransformCom->Get_Info(INFO_POS)));
		// CEventMgr::GetInstance()->Add_Obj(L"Test", CHedgehog_Stemp::Create(m_pGraphicDev, m_pTransformCom->Get_Info(INFO_POS)));

		// 플레이어가 나는 상태에서는 코인을 생성하지 않는다 (수정시 팀장 보고)
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));
		if(nullptr != pPlayer && !pPlayer->Is_Fly())
		{
			CGameObject* GoldCoin = CGoldCoin::Create(m_pGraphicDev);
			CEventMgr::GetInstance()->Add_Obj(L"Item_GoldCoin", GoldCoin);
			GoldCoin->Get_Transform()->Set_Pos({ m_pTransformCom->Get_Info(INFO_POS).x, GoldCoin->Get_Transform()->Get_Info(INFO_POS).y , m_pTransformCom->Get_Info(INFO_POS).z });
		}

		CEventMgr::GetInstance()->Delete_Obj(this);
	}

	// Hit state return 
	if (m_bHit == true)
	{
		m_fAccTime += fTimeDelta;

		if (m_fAccTime >= 0.2f) // 플레이어 딜레이 만큼이 베스트
		{
			m_bHit = false;
			m_fAccTime = 0.f;
		}
	}

	return iExit;
}

void CMonster::LateUpdate_Object()
{
	// Dead Condition
	if (m_tStatInfo.fCurHP <= 0.f)
	{
		m_tStatInfo.bDead = true;
	}

	__super::LateUpdate_Object();
	if (PLAY_MODE::TOOL != CManagement::GetInstance()->Get_PlayMode())
		m_pStateMachineCom->LateUpdate_StateMachine();

}

void CMonster::Render_Object()  // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!
{
	__super::Render_Object(); // 콜라이더 출력

}

void CMonster::OnCollision_Enter(CGameObject* _pColObj)
{

	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::PLAYER:
	{
	}
	break;
	case Engine::OBJ_TYPE::LINE:
	{
		_vec3 vLinePos = static_cast<CLineCollider*>(_pColObj->Get_Collider())->Get_Overlap_Line();

		_vec3 vMonsterPos = m_pTransformCom->Get_Info(INFO_POS);
		_vec3 vMonsterDir = m_pTransformCom->Get_Dir();

		if ((vLinePos.x == vMonsterPos.x) && (vLinePos.z == vMonsterPos.z))
		{
			m_pTransformCom->Set_Dir({ -vMonsterDir.x, vMonsterDir.y, -vMonsterDir.z });
		}
		
	}
	break;
	case Engine::OBJ_TYPE::PROJECTILE:
	{
		CGameObject* pOwner = dynamic_cast<CProjectile*>(_pColObj)->Get_Owner();
		if (pOwner != nullptr)
		{
			OBJ_TYPE eType = pOwner->Get_Type();
				if (OBJ_TYPE::PLAYER == eType)
				{
					Damaged(dynamic_cast<CMage_Bullet*>(_pColObj)->Get_BallDamage());

				}
		}
		
	}
	break;
	default:
	{
	}
	break;
	} // Switch end

}

void CMonster::OnCollision_Stay(CGameObject* _pColObj)
{	
	_vec3 _vColPos = _pColObj->Get_Transform()->Get_Info(INFO_POS);
	_vec3 vOwnerPos = m_pTransformCom->Get_Info(INFO_POS);

	_float Distance = D3DXVec3Length(&(_vColPos - vOwnerPos));


	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::PLAYER:
	{
		if (m_pStateMachineCom->Get_CurState() == STATE_TYPE::MONATTACK ||
			m_pStateMachineCom->Get_CurState() == STATE_TYPE::BACK_MONATTACK )
		{
			if (m_pAnimatorCom->Get_CurAniamtion()->Is_End() && 
				_pColObj->Get_ID() != OBJ_ID::MONSTER_FOX && 
				_pColObj->Get_ID() != OBJ_ID::MONSTER_SQUIRREL)
			{

				dynamic_cast<CPlayer*>(_pColObj)->Damaged(m_tStatInfo.fAD);		


			}
			
		}
	}
	break;
	case Engine::OBJ_TYPE::SKILL:
	{
		OBJ_TYPE eType = dynamic_cast<CSkill*>(_pColObj)->Get_SkillOwner()->Get_Type();
		if (eType == OBJ_TYPE::PLAYER)
		{
			Damaged(static_cast<CSkill*>(_pColObj)->Get_SkillDamage());
		}
	}
	break;
	case Engine::OBJ_TYPE::LINE:
	{
		_vec3 vLinePos = static_cast<CLineCollider*>(_pColObj->Get_Collider())->Get_Overlap_Line();

		_vec3 vMonsterPos = m_pTransformCom->Get_Info(INFO_POS);
		_vec3 vMonsterDir = m_pTransformCom->Get_Dir();

		if ((vLinePos.x == vMonsterPos.x) && (vLinePos.z == vMonsterPos.z))
		{
			m_pTransformCom->Set_Dir({ -vMonsterDir.x, vMonsterDir.y, -vMonsterDir.z });
		}
	}
	break;
	default:
	{
	}
	break;

	} // Switch end
}

void CMonster::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CMonster::Add_Component()
{
	CComponent* pComponent = nullptr;

	// Rc Texture
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	// Rect Collider
	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);

	// State Machine
	pComponent = m_pStateMachineCom = dynamic_cast<CStateMachine*>(Engine::Clone_Proto(COMPONENT_TYPE::STATEMACHINE, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::STATEMACHINE, pComponent);

	// AI
	pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);

	// RigidyBody
	pComponent = m_pRigidBodyCom = dynamic_cast<CRigidBody*>(Engine::Clone_Proto(COMPONENT_TYPE::RIGIDBODY, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::RIGIDBODY, pComponent);

#pragma region Texture

	// 각각의 몬스터 객체에서 진행 

#pragma endregion


	return S_OK;
}

void CMonster::Damaged(const _float& fDamage, CGameObject* pObj)
{


	 Set_CurHP(m_tStatInfo.fCurHP - fDamage);

	// cout << "뎀지받음" << endl;

	m_bHit = true;
	if (!m_pRigidBodyCom->Is_Vel_Zero())
	{
		m_pRigidBodyCom->Zero_KnockBack();
	}
	
	if (m_pStateMachineCom->Get_CurState() == STATE_TYPE::MONATTACK ||
		m_pStateMachineCom->Get_CurState() == STATE_TYPE::BACK_MONATTACK )
	{
		m_pRigidBodyCom->Zero_KnockBack();
	}
	else
	{
		if(pObj != nullptr)
			m_pRigidBodyCom->Knock_Back(pObj, 120);
	}
	
	CEventMgr::GetInstance()->Add_Obj(L"Monster_Cut_Effect", CMobCutEffect::Create(m_pGraphicDev, m_pTransformCom->Get_Info(INFO_POS)));


	

}


void CMonster::Free()
{
	__super::Free();
}

