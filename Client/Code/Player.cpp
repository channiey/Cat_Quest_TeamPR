﻿#include "stdafx.h"
#include "..\Header\Player.h"

#include "Export_Function.h"

#include "RectCollider.h"

#include "PlayerState_Hit.h"
#include "PlayerState_fIdle.h"
#include "PlayerState_fWalk.h"
#include "PlayerState_fRoll.h"
#include "PlayerState_fAttack.h"
#include "PlayerState_fAttack1.h"
#include "PlayerState_fAttack2.h"
#include "PlayerState_fDie.h"
#include "PlayerState_fWake.h"
#include "PlayerState_fSleep.h"
#include "PlayerState_bIdle.h"
#include "PlayerState_bWalk.h"
#include "PlayerState_bRoll.h"
#include "PlayerState_bAttack.h"
#include "PlayerState_bAttack1.h"
#include "PlayerState_bAttack2.h"
#include "PlayerState_fFlight.h"

#include "Environment.h"
#include "Npc.h"
#include "EnterUI.h"
#include "FieldSkillUI.h"

#include "Monster.h"

#include "SphereCollider.h"

// Move Effect
#include "MoveDust.h"
#include "MoveWater.h"
// Skill Effect
#include "Skill_Player_Fire.h"
#include "Skill_Player_Ice.h"
#include "Skill_Player_Thunder.h"
#include "Skill_Player_Beam.h"

// Shadow
#include "Shadow_Player.h"

#include "RangeObj.h"
#include "EventMgr.h"

#include "Inventory.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::PLAYER, OBJ_ID::PLAYER)
	, m_pStateMachineCom(nullptr)
	, m_eCurGroundType(LINE_TYPE::LAND)
{
	ZeroMemory(&m_pTextureCom, sizeof(CTexture*) * _uint(STATE_TYPE::TYPEEND));
}

CPlayer::CPlayer(const CPlayer& rhs)
	: Engine::CGameObject(rhs)
	, m_tMoveInfo(rhs.m_tMoveInfo)
	, m_tStatInfo(rhs.m_tStatInfo)
	, m_pStateMachineCom(rhs.m_pStateMachineCom)
	, m_eCurGroundType(rhs.m_eCurGroundType)
{
	for (size_t i = 0; i < _uint(_uint(STATE_TYPE::TYPEEND)); ++i)
	{
		m_pTextureCom[i] = rhs.m_pTextureCom[i];
	}
}

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	m_tMoveInfo.fMoveSpeed = 20.f;
	Set_AD(10);

	m_bHit = false;
	m_bAttack = false;
	m_bSkill = false;

	m_bIsMonster = false;
	m_fMonTargetLength = 99.f;
	m_pMonTarget = nullptr;
	
	m_bhasFlight = false;
	m_bIsTalking = false;

	m_pInven = nullptr;

	m_tStatInfo.fGold = 120;



	for (size_t i = 0; i < 4; ++i)
	{
		m_arrSkillSlot[i] = nullptr;
	}

	m_fAccDef = 0.f;
	m_pTransformCom->Set_Scale(_vec3{ 3.f, 3.f, 3.f });
	m_pTransformCom->Set_Dir(vec3.right);
	m_pTransformCom->Set_Pos(_vec3{ 
		_float(START_POS_WORLD_X), 
		m_pTransformCom->Get_Scale().y, 
		_float(START_POS_WORLD_Z) });

	CGameObject* pShadow = CShadow_Player::Create(m_pGraphicDev, this);
	CEventMgr::GetInstance()->Add_Obj(L"Player_Shadow", pShadow);
	pShadow->Set_Maintain(TRUE); // <-수정시 팀장 보고!

#pragma region State
	CState* pState = CPlayerState_Hit::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_HIT, pState);
	pState = CPlayerState_fWalk::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_WALK, pState);
	pState = CPlayerState_fIdle::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_IDLE, pState);
	pState = CPlayerState_fRoll::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_ROLL, pState);
	pState = CPlayerState_fAttack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_ATTACK, pState);
	pState = CPlayerState_fAttack1::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_ATTACK1, pState);
	pState = CPlayerState_fAttack2::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_ATTACK2, pState);
	pState = CPlayerState_bIdle::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_IDLE, pState);
	pState = CPlayerState_bWalk::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_WALK, pState);
	pState = CPlayerState_bRoll::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_ROLL, pState);
	pState = CPlayerState_bAttack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_ATTACK, pState);
	pState = CPlayerState_bAttack1::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_ATTACK1, pState);
	pState = CPlayerState_bAttack2::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_ATTACK2, pState);
	pState = CPlayerState_fWake::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_WAKE, pState);
	pState = CPlayerState_fDie::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_DIE, pState);
	pState = CPlayerState_fSleep::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_SLEEP, pState);
	pState = CPlayerState_fFlight::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_FLIGHT, pState);
#pragma endregion

#pragma region Animation
	CAnimation* pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_HIT)], STATE_TYPE::FRONT_HIT, 0.2f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_HIT, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_WALK)], STATE_TYPE::FRONT_WALK, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_WALK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_IDLE)], STATE_TYPE::FRONT_IDLE, 0.2f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_IDLE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_ATTACK)], STATE_TYPE::FRONT_ATTACK, 0.08f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_ATTACK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_ATTACK1)], STATE_TYPE::FRONT_ATTACK1, 0.08f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_ATTACK1, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_ATTACK2)], STATE_TYPE::FRONT_ATTACK2, 0.08f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_ATTACK2, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_ROLL)], STATE_TYPE::FRONT_ROLL, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_ROLL, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_DIE)], STATE_TYPE::FRONT_DIE, 0.09f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_DIE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_WAKE)], STATE_TYPE::FRONT_WAKE, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_WAKE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_SLEEP)], STATE_TYPE::FRONT_SLEEP, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_SLEEP, pAnimation);

	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_IDLE)], STATE_TYPE::BACK_IDLE, 0.2f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_IDLE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_WALK)], STATE_TYPE::BACK_WALK, 0.08f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_WALK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_ATTACK)], STATE_TYPE::BACK_ATTACK, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_ATTACK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_ATTACK1)], STATE_TYPE::BACK_ATTACK1, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_ATTACK1, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_ATTACK2)], STATE_TYPE::BACK_ATTACK2, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_ATTACK2, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_ROLL)], STATE_TYPE::BACK_ROLL, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_ROLL, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_FLIGHT)], STATE_TYPE::FRONT_FLIGHT, 0.02f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_FLIGHT, pAnimation);
#pragma endregion

#pragma region Effect

	m_arrSkill[_uint(SKILL_TYPE::FIRE)] = CSkill_Player_Fire::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(m_arrSkill[_uint(SKILL_TYPE::FIRE)], E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Player_Fire", m_arrSkill[_uint(SKILL_TYPE::FIRE)]), E_FAIL);
	m_arrSkillSlot[0] = m_arrSkill[_uint(SKILL_TYPE::FIRE)];
	m_arrSkillSlot[0]->Set_Maintain(TRUE); // 수정시 팀장 보고

	m_arrSkill[_uint(SKILL_TYPE::THUNDER)] = CSkill_Player_Thunder::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(m_arrSkill[_uint(SKILL_TYPE::THUNDER)], E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Player_Thunder", m_arrSkill[_uint(SKILL_TYPE::THUNDER)]), E_FAIL);
	m_arrSkillSlot[1] = m_arrSkill[_uint(SKILL_TYPE::THUNDER)];
	m_arrSkillSlot[1]->Set_Maintain(TRUE); // 수정시 팀장 보고

	m_arrSkill[_uint(SKILL_TYPE::ICE)] = CSkill_Player_Ice::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(m_arrSkill[_uint(SKILL_TYPE::ICE)], E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Player_Ice", m_arrSkill[_uint(SKILL_TYPE::ICE)]), E_FAIL);
	m_arrSkillSlot[2] = m_arrSkill[_uint(SKILL_TYPE::ICE)];
	m_arrSkillSlot[2]->Set_Maintain(TRUE); // 수정시 팀장 보고

	m_arrSkill[_uint(SKILL_TYPE::BEAM)] = CSkill_Player_Beam::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(m_arrSkill[_uint(SKILL_TYPE::BEAM)], E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Player_Beam", m_arrSkill[_uint(SKILL_TYPE::BEAM)]), E_FAIL);
	m_arrSkillSlot[3] = m_arrSkill[_uint(SKILL_TYPE::BEAM)];
	m_arrSkillSlot[3]->Set_Maintain(TRUE); // 수정시 팀장 보고

#pragma endregion

	// 처음 시작상태 설정
	m_pStateMachineCom->Set_Animator(m_pAnimatorCom);
	m_pStateMachineCom->Set_State(STATE_TYPE::FRONT_WAKE);

	// Camera Setting
	if (PLAY_MODE::TOOL != CManagement::GetInstance()->Get_PlayMode())
	{
		CCameraMgr::GetInstance()->Set_Follow(this);
		CCameraMgr::GetInstance()->Set_LookAt(this);
		CCameraMgr::GetInstance()->Set_ViewSpace();
		CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Set_InitLook_Y(m_pTransformCom->Get_Info(INFO_POS).y);
	}
	m_bMaintain = true; // 씬 변경시 유지 (사용시 팀장 보고)

	// 테스트용
	m_iTempMode = 1;

	// << : Test : Range Test
	CGameObject* pGameObject = nullptr;

	pGameObject = CRangeObj::Create(m_pGraphicDev, this, 7.f);
	pGameObject->Set_Maintain(TRUE); // <-수정시 팀장 보고!
	CSphereCollider* pShpere = dynamic_cast<CSphereCollider*>(pGameObject->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Player_Range_Basic_Attack", pGameObject);
	arrRangeObj[(UINT)RANGE_TYPE::BASIC_ATTACK] = dynamic_cast<CRangeObj*>(pGameObject);

	m_szName = L"Player";

	m_pInven = CInventory::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(m_pInven, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Inventory", m_pInven);
	m_pInven->Set_Maintain(true);

	return S_OK;
}

Engine::_int CPlayer::Update_Object(const _float& fTimeDelta)
{
	//if (!m_pInven)
	//{
	//	m_pInven = CManagement::GetInstance()->
	//		Get_GameObject(OBJ_TYPE::UI, L"UI_Inventory");
	//}

	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	m_pStateMachineCom->Update_StateMachine(fTimeDelta);

	/*for (auto iter : m_arrSkillSlot)
	{
		if(iter != nullptr)
			iter->Update_Object(fTimeDelta);
	}*/

	Regen_Def(fTimeDelta);
	
	if(!m_bIsTalking)
		Key_Input(fTimeDelta);
	
	
	// Move Effect 생성
	if (m_iTempMode == 1) { // 육지
		if (m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_WALK ||
			m_pStateMachineCom->Get_CurState() == STATE_TYPE::BACK_WALK ||
			m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_ROLL ||
			m_pStateMachineCom->Get_CurState() == STATE_TYPE::BACK_ROLL) {
			if (m_pAnimatorCom->Get_CurAniamtion()->Get_CurFrame() == 0 ||
				m_pAnimatorCom->Get_CurAniamtion()->Get_CurFrame() == 7) {
				if (!CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::EFFECT, L"MoveDust"))
				{
					CGameObject* p = CMoveDust::Create(m_pGraphicDev, this);
					CEventMgr::GetInstance()->Add_Obj(L"MoveDust", p);
				}
			}
		}
	} 
	else if (m_iTempMode == 2) { // 물
		if (m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_WALK ||
			m_pStateMachineCom->Get_CurState() == STATE_TYPE::BACK_WALK ||
			m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_ROLL ||
			m_pStateMachineCom->Get_CurState() == STATE_TYPE::BACK_ROLL) {
			if (m_pAnimatorCom->Get_CurAniamtion()->Get_CurFrame() == 0 ||
				m_pAnimatorCom->Get_CurAniamtion()->Get_CurFrame() == 7) {
				if (!CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::EFFECT, L"MoveWater"))
				{
					CGameObject* p = CMoveWater::Create(m_pGraphicDev, this);
					CEventMgr::GetInstance()->Add_Obj(L"MoveWater", p);
				}
			}
		}
	}
	
	
	return iExit;
}

void CPlayer::LateUpdate_Object()
{
	m_pStateMachineCom->LateUpdate_StateMachine();

	if(m_bAttack)
		m_bAttack = false;

	if (m_bSkill)
		m_bSkill = false;

	if (m_bhasFlight)
	{
		NULL_CHECK(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Flight"))
		CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Flight")->Set_Active(true);
	}
		

	__super::LateUpdate_Object();

}

void CPlayer::Render_Object()
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	if(m_bHit && m_tStatInfo.fCurDef <= 0)
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, HITCOLOR_R, HITCOLOR_G, HITCOLOR_B));
	else if (m_bHit && m_tStatInfo.fCurDef > 0)
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 199, 144));

	m_pStateMachineCom->Render_StateMachine();
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pGraphicDev->SetTexture(0, NULL);

	__super::Render_Object(); 
}

void CPlayer::OnCollision_Enter(CGameObject* _pColObj)
{
	if (STATE_TYPE::FRONT_FLIGHT == m_pStateMachineCom->Get_CurState() && _pColObj->Get_ID() != OBJ_ID::LINE)
		return;

	_vec3 vMyPos = m_pTransformCom->Get_Info(INFO_POS);
	_vec3 vColPos = _pColObj->Get_Transform()->Get_Info(INFO_POS);

	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::MONSTER:
	{
	/*	_vec3 vOverlap = static_cast<CRectCollider*>(m_pColliderCom)->Get_Overlap_Rect();

		if (vOverlap.x > vOverlap.z)
		{
			if (vMyPos.z < vColPos.z)
				m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
												vMyPos.y,
												vMyPos.z - vOverlap.z });
			else
				m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
												vMyPos.y,
												vMyPos.z + vOverlap.z });
		}
		else
		{
			if (vMyPos.x < vColPos.x)
				m_pTransformCom->Set_Pos(_vec3{ vMyPos.x - vOverlap.x,
												vMyPos.y,
												vMyPos.z });
			else
				m_pTransformCom->Set_Pos(_vec3{ vMyPos.x + vOverlap.x,
												vMyPos.y,
												vMyPos.z });
		}*/
	}
	break;
	case Engine::OBJ_TYPE::LINE:
	{
		_vec3 vNewPos = static_cast<CLineCollider*>(_pColObj->Get_Collider())->Get_Overlap_Line();
		vNewPos.y = 0.f;

		m_pTransformCom->Set_Pos(vMyPos + vNewPos);
	}
	break;
	case Engine::OBJ_TYPE::NPC:
	{
		_vec3 vOverlap = static_cast<CRectCollider*>(m_pColliderCom)->Get_Overlap_Rect();

		if (_pColObj->Get_EnterType() == ENTER_TYPE::ENTER_NO)
		{
			if (vOverlap.x > vOverlap.z)
			{
				if (vMyPos.z < vColPos.z)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z - vOverlap.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z + vOverlap.z });
			}
			else
			{
				if (vMyPos.x < vColPos.x)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x - vOverlap.x,
													vMyPos.y,
													vMyPos.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x + vOverlap.x,
													vMyPos.y,
													vMyPos.z });
			}
		}
		// 대화 가능 UI
		if (_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_CHAT) {
			CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
				(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));

			m_pEnterUI->EnterUI_On(UIENTER_TYPE::CHAT, _pColObj);
		}
	}
	case Engine::OBJ_TYPE::ITEM:
		break;
	case Engine::OBJ_TYPE::PROJECTILE:
		break;
	case Engine::OBJ_TYPE::CAMERA:
		break;
	case Engine::OBJ_TYPE::ENVIRONMENT:
	{
		_vec3 vOverlap = static_cast<CRectCollider*>(m_pColliderCom)->Get_Overlap_Rect();

		if (_pColObj->Get_EnterType() == ENTER_TYPE::ENTER_NO)
		{
			if (vOverlap.x > vOverlap.z)
			{
				if (vMyPos.z < vColPos.z)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z - vOverlap.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z + vOverlap.z });
			}
			else
			{
				if (vMyPos.x < vColPos.x)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x - vOverlap.x,
													vMyPos.y,
													vMyPos.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x + vOverlap.x,
													vMyPos.y,
													vMyPos.z });
			}
		}
		_pColObj->Set_EventSwitch(true);
		_pColObj->Set_IsEnter(true);

		// 입장 가능 UI
		if (_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_ENTER) {
			CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
				(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));

			m_pEnterUI->EnterUI_On(UIENTER_TYPE::ENTER, _pColObj);
		}
		// 탐색 가능 UI
		if (_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_INSPECT) {
			CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
				(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));

			m_pEnterUI->EnterUI_On(UIENTER_TYPE::INSPECT, _pColObj);
		}
	}
	break;
	default:
		break;
	}
}

void CPlayer::OnCollision_Stay(CGameObject* _pColObj)
{
	if (STATE_TYPE::FRONT_FLIGHT == m_pStateMachineCom->Get_CurState() && _pColObj->Get_ID() != OBJ_ID::LINE)
		return;

	_vec3 vMyPos  = m_pTransformCom->Get_Info(INFO_POS);
	_vec3 vColPos = _pColObj->Get_Transform()->Get_Info(INFO_POS);

	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::MONSTER:
	{
		CloseTarget_Dis(_pColObj);

		if (Is_Attack())
		{
			Regen_Mana();
			dynamic_cast<CMonster*>(_pColObj)->Damaged(m_tStatInfo.fAD, this);
			CCameraMgr::GetInstance()->Shake_Camera();
		}
		if (Is_Skill())
		{
			for (auto iter : m_arrSkillSlot)
			{
				if (nullptr != iter && iter->Is_Active())
				{
					dynamic_cast<CMonster*>(_pColObj)->Damaged(dynamic_cast<CSkill*>(iter)->Get_SkillDamage(), this);
				}
			}
			
		}
		
	/*	_vec3 vOverlap = static_cast<CRectCollider*>(m_pColliderCom)->Get_Overlap_Rect();

		if (vOverlap.x > vOverlap.z)
		{
			if (vMyPos.z < vColPos.z)
				m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
												vMyPos.y,
												vMyPos.z - vOverlap.z });
			else
				m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
												vMyPos.y,
												vMyPos.z + vOverlap.z });
		}
		else
		{
			if (vMyPos.x < vColPos.x)
				m_pTransformCom->Set_Pos(_vec3{ vMyPos.x - vOverlap.x,
												vMyPos.y,
												vMyPos.z });
			else
				m_pTransformCom->Set_Pos(_vec3{ vMyPos.x + vOverlap.x,
												vMyPos.y,
												vMyPos.z });
		}*/
	}
	break;
	case Engine::OBJ_TYPE::LINE:
	{
		_vec3 vNewPos = static_cast<CLineCollider*>(_pColObj->Get_Collider())->Get_Overlap_Line();
		vNewPos.y = 0.f;

		m_pTransformCom->Set_Pos(vMyPos + vNewPos);
	}
	break;
	case Engine::OBJ_TYPE::NPC:
	{
		_vec3 vOverlap = static_cast<CRectCollider*>(m_pColliderCom)->Get_Overlap_Rect();

		if (_pColObj->Get_EnterType() == ENTER_TYPE::ENTER_NO)
		{
			if (vOverlap.x > vOverlap.z)
			{
				if (vMyPos.z < vColPos.z)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z - vOverlap.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z + vOverlap.z });
			}
			else
			{
				if (vMyPos.x < vColPos.x)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x - vOverlap.x,
													vMyPos.y,
													vMyPos.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x + vOverlap.x,
													vMyPos.y,
													vMyPos.z });
			}
		}
		// 대화 가능 UI
		if (_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_CHAT) {
			CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
				(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));

			m_pEnterUI->EnterUI_On(UIENTER_TYPE::CHAT, _pColObj);
		}
		// 퀘스트 진입 테스트
		//if (CInputDev::GetInstance()->Key_Down('E')) 
		//{
		//	if (dynamic_cast<CNpc*>(_pColObj)->Get_IsReadyQuest() && !CQuestMgr::GetInstance()->Get_Active()) 
		//	{
		//		dynamic_cast<CNpc*>(_pColObj)->Set_IsReadyQuest(false);
		//		CQuestMgr::GetInstance()->Set_Quest(dynamic_cast<CNpc*>(_pColObj)->Get_HaveQuest());
		//		CQuestMgr::GetInstance()->Set_Active(true);
		//		CQuestMgr::GetInstance()->Set_Player(this);
		//	}
		//}

	}
		break;
	case Engine::OBJ_TYPE::ITEM:
		break;
	case Engine::OBJ_TYPE::PROJECTILE:
		break;
	case Engine::OBJ_TYPE::CAMERA:
		break;
	case Engine::OBJ_TYPE::ENVIRONMENT:
	{
		_vec3 vOverlap = static_cast<CRectCollider*>(m_pColliderCom)->Get_Overlap_Rect();

		if (_pColObj->Get_EnterType() == ENTER_TYPE::ENTER_NO) {
			if (vOverlap.x > vOverlap.z)
			{
				if (vMyPos.z < vColPos.z)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z - vOverlap.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z + vOverlap.z });
			}
			else
			{
				if (vMyPos.x < vColPos.x)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x - vOverlap.x,
													vMyPos.y,
													vMyPos.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x + vOverlap.x,
													vMyPos.y,
													vMyPos.z });
			}
		}

		// 입장 가능 UI
		if (_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_ENTER) {
			CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
				(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));

			m_pEnterUI->EnterUI_On(UIENTER_TYPE::ENTER, _pColObj);
		}
		// 탐색 가능 UI
		if (_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_INSPECT) {
			CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
				(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));

			m_pEnterUI->EnterUI_On(UIENTER_TYPE::INSPECT, _pColObj);
		}
	}
	break;
	default:
		break;
	}
}

void CPlayer::OnCollision_Exit(CGameObject* _pColObj)
{
	if (STATE_TYPE::FRONT_FLIGHT == m_pStateMachineCom->Get_CurState() && _pColObj->Get_ID() != OBJ_ID::LINE)
		return;

	_vec3 vColPos = _pColObj->Get_Transform()->Get_Info(INFO_POS);


	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::MONSTER:
		m_bIsMonster = false;
		m_fMonTargetLength = 99.f;
		m_pMonTarget = nullptr;
		Set_PlayerDirNormal(m_vMonTargetDir);
		break;
	default:
		break;
	}

	_pColObj->Set_IsEnter(false);

	// 부쉬면 Event 한번 더 진행
	if (_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_ALPHA)
		_pColObj->Set_EventSwitch(true);

	// UI 끄기
	if (_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_ENTER ||
		_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_INSPECT ||
		_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_CHAT)
	{
		CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
			(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));

		m_pEnterUI->EnterUI_Off();
	}
}

HRESULT CPlayer::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);

	pComponent = m_pStateMachineCom = dynamic_cast<CStateMachine*>(Engine::Clone_Proto(COMPONENT_TYPE::STATEMACHINE, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::STATEMACHINE, pComponent);

	pComponent = m_pAnimatorCom = dynamic_cast<CAnimator*>(Engine::Clone_Proto(COMPONENT_TYPE::ANIMATOR, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::ANIMATOR, pComponent);

	pComponent = m_pRigidBodyCom = dynamic_cast<CRigidBody*>(Engine::Clone_Proto(COMPONENT_TYPE::RIGIDBODY, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::RIGIDBODY, pComponent);



#pragma region Texture
	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_IDLE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fIdle", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_WALK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fWalk", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_ROLL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fRoll", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_ATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fAttack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_ATTACK1)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fAttack1", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_ATTACK2)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fAttack2", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_HIT)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fHit", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_IDLE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bIdle", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_WALK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bWalk", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_ROLL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bRoll", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_ATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bAttack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_ATTACK1)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bAttack1", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_ATTACK2)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bAttack2", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_WAKE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fWake", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_DIE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fDie", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_SLEEP)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fSleep", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_FLIGHT)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fFlight", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
#pragma endregion


	return S_OK;
}

void CPlayer::Key_Input(const _float& fTimeDelta)
{
	if (CInputDev::GetInstance()->Key_Down('Q'))
		m_bhasFlight = true;

	if (CInputDev::GetInstance()->Key_Down('1') &&
		m_arrSkillSlot[0] != nullptr && !m_arrSkillSlot[0]->Is_Active() &&
		m_arrSkillSlot[0]->Get_SkillUsage() <= m_tStatInfo.fCurMP)
	{
		m_arrSkillSlot[0]->Play();
		Using_Mana(m_arrSkillSlot[0]->Get_SkillUsage());
		if (OBJ_ID::EFFECT_SKILL_HEAL != m_arrSkillSlot[0]->Get_ID())
			m_bSkill = true;
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_IDL_TO_ATK);
	}
	else if (CInputDev::GetInstance()->Key_Down('2') &&
		m_arrSkillSlot[1] != nullptr && !m_arrSkillSlot[1]->Is_Active() &&
		m_arrSkillSlot[1]->Get_SkillUsage() <= m_tStatInfo.fCurMP)
	{
		m_arrSkillSlot[1]->Play();
		Using_Mana(m_arrSkillSlot[1]->Get_SkillUsage());
		if (OBJ_ID::EFFECT_SKILL_HEAL != m_arrSkillSlot[1]->Get_ID())
			m_bSkill = true;
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_IDL_TO_ATK);
	}
	else if (CInputDev::GetInstance()->Key_Down('3') &&
		m_arrSkillSlot[2] != nullptr && !m_arrSkillSlot[2]->Is_Active() && 
		m_arrSkillSlot[2]->Get_SkillUsage() <= m_tStatInfo.fCurMP)
	{
		m_arrSkillSlot[2]->Play();
		Using_Mana(m_arrSkillSlot[2]->Get_SkillUsage());
		if (OBJ_ID::EFFECT_SKILL_HEAL != m_arrSkillSlot[2]->Get_ID())
			m_bSkill = true;
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_IDL_TO_ATK);
	}
	else if (CInputDev::GetInstance()->Key_Down('4') &&
		m_arrSkillSlot[3] != nullptr && !m_arrSkillSlot[3]->Is_Active() &&
		m_arrSkillSlot[3]->Get_SkillUsage() <= m_tStatInfo.fCurMP)
	{
		m_arrSkillSlot[3]->Play();
		Using_Mana(m_arrSkillSlot[3]->Get_SkillUsage());
		if (OBJ_ID::EFFECT_SKILL_HEAL != m_arrSkillSlot[3]->Get_ID())
			m_bSkill = true;
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_IDL_TO_ATK);
	}

	if (CInputDev::GetInstance()->Key_Down('L'))
		Set_CurHP(m_tStatInfo.fMaxHP);
	if (CInputDev::GetInstance()->Key_Down('K'))
		Set_CurMP(m_tStatInfo.fMaxMP);
	if (CInputDev::GetInstance()->Key_Down('C'))
		Set_MoveSpeed(50.f);
	if (CInputDev::GetInstance()->Key_Down('V'))
		Set_MoveSpeed(20.f);
}

void CPlayer::Regen_Def(const _float& fTimeDelta)
{
	if (m_tStatInfo.fCurDef < m_tStatInfo.fMaxDef)
	{
		m_fAccDef += fTimeDelta;
		if (m_fAccDef > 12.f)
		{
			_float fRegenDef = m_tStatInfo.fCurDef + 20;
			if (fRegenDef > m_tStatInfo.fMaxDef)
				fRegenDef = m_tStatInfo.fMaxDef;
			Set_CurDef(fRegenDef);
			m_fAccDef = 0.f;
		}
	}
}

void CPlayer::CloseTarget_Dis(CGameObject* pTarget)
{
	_vec3 vTargetDir = pTarget->Get_Transform()->Get_Info(INFO::INFO_POS) - m_pTransformCom->Get_Info(INFO::INFO_POS);
	_float fTargetLength = D3DXVec3Length(&vTargetDir);
	

	if (m_fMonTargetLength >= fTargetLength)
	{
		m_fMonTargetLength = fTargetLength;
		D3DXVec3Normalize(&m_vMonTargetDir, &vTargetDir);
		m_vMonTargetDir.y = 0;
		m_pMonTarget = pTarget;
		m_bIsMonster = true;
	}
	
}

CGameObject* CPlayer::Get_MonTarget()
{
	if (m_pMonTarget != nullptr && m_pMonTarget->Is_Active())
		return m_pMonTarget;
	else
		return nullptr;
}

void CPlayer::Set_PlayerLook(const _vec3& vDir)
{
	if(vDir.x < 0)
		m_pTransformCom->Set_Scale(_vec3{ -3.f, 3.f, 3.f });
	if (vDir.x > 0)
		m_pTransformCom->Set_Scale(_vec3{ 3.f, 3.f, 3.f });
}

void CPlayer::Set_PlayerDirNormal(const _vec3& vDir)
{
	if (m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_ROLL ||
		m_pStateMachineCom->Get_CurState() == STATE_TYPE::BACK_ROLL)
		return;

	_vec3 vDirA;
	D3DXVec3Normalize(&vDirA, &vDir);

	_float horizontalX = vDirA.x;
	_float horizontalZ = vDirA.z;

	_vec3 resultDir;

	if (horizontalX > 0.f && horizontalX <= 1.f && horizontalZ > 0.f && horizontalZ <= 1.f)
		resultDir = (_vec3(1.f, 0.f, 1.f)); // 오른쪽 뒤 대각선
	else if (horizontalX >= 0.f && horizontalX < 1.f && horizontalZ < -0.f && horizontalZ <= -1.f)
		resultDir = (_vec3(1.f, 0.f, -1.f)); // 오른쪽 앞 대각선
	else if (horizontalX < -0.f && horizontalX <= -1.f && horizontalZ > 0.f && horizontalZ <= 1.f)
		resultDir = (_vec3(-1.f, 0.f, 1.f)); // 왼쪽 뒤 대각선
	else if (horizontalX < -0.f && horizontalX <= -1.f && horizontalZ < -0.f && horizontalZ <= -1.f)
		resultDir = (_vec3(-1.f, 0.f, -1.f)); // 왼쪽 앞 대각선
	else if (horizontalX >= 0.f)
		resultDir = (_vec3(1.f, 0.f, 0.f)); // 오른쪽
	else if (horizontalX <= -0.f)
		resultDir = (_vec3(-1.f, 0.f, 0.f)); // 왼쪽
	else if (horizontalZ >= 0.f)
		resultDir = (_vec3(0.f, 0.f, 1.f)); // 뒤쪽
	else if (horizontalZ <= -0.f)
		resultDir = (_vec3(0.f, 0.f, -1.f)); // 앞쪽
	else
		resultDir = (_vec3(vDirA.x, 0.f, vDirA.z));

	m_pTransformCom->Set_Dir(resultDir);
	Set_PlayerLook(resultDir);
	
}

void CPlayer::Regen_HP(const _float& fHeal)
{
	if (m_tStatInfo.fCurHP > 0)
	{
		_float fRegenHeal = m_tStatInfo.fCurHP + fHeal;
		if (fRegenHeal > m_tStatInfo.fMaxHP)
			fRegenHeal = m_tStatInfo.fMaxHP;

		Set_CurHP(fRegenHeal);
	}

}

void CPlayer::Regen_Mana()
{
	Set_CurMP(m_tStatInfo.fCurMP += 0.5f);

	if (m_tStatInfo.fCurMP >= m_tStatInfo.fMaxMP)
		Set_CurMP(m_tStatInfo.fMaxMP);
}

void CPlayer::Using_Mana(const _uint& iUsage)
{
	Set_CurMP(m_tStatInfo.fCurMP - iUsage);

	if (m_tStatInfo.fCurMP <= 0)
		Set_CurMP(0);

}

void CPlayer::Damaged(const _float& fDamage)
{
	if (m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_DIE ||
		m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_WAKE || 
		m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_ROLL || 
		m_pStateMachineCom->Get_CurState() == STATE_TYPE::BACK_ROLL ||
		m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_FLIGHT)
		return;

	if (m_tStatInfo.fCurDef > 0)
	{
		Set_CurDef(m_tStatInfo.fCurDef - fDamage);
		m_bHit = true;
	}
	else
	{
		if (m_tStatInfo.fCurHP <= 1)
		{
			Set_CurHP(0);
			m_tStatInfo.bDead = true;
		}
		else
		{
			Set_CurHP(m_tStatInfo.fCurHP - fDamage);
			m_bHit = true;
		}
	}
}

CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayer* pInstance = new CPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Player Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayer::Free()
{

	__super::Free();
}