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
#include "PlayerState_bIdle.h"
#include "PlayerState_bWalk.h"
#include "PlayerState_bRoll.h"
#include "PlayerState_bAttack.h"
#include "PlayerState_bAttack1.h"
#include "PlayerState_bAttack2.h"

#include "Environment.h"
#include "Npc.h"
#include "EnterUI.h"
#include "FieldSkillUI.h"

#include "Monster.h"

// Move Effect
#include "MoveDust.h"
#include "MoveWater.h"
// Skill Effect
#include "Effect_Fire.h"
#include "Effect_Thunder.h"

// Shadow
#include "Shadow_Player.h"

#include "RangeObj.h"
#include "EventMgr.h"
#include "QuestMgr.h" // 퀘스트 매니저

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

	Set_AD(10);

	m_bHit = false;
	m_bAttack = false;
	m_bSkill = false;

	for (_uint i = 0; i < 4; ++i)
		m_bOnSKill[i] = false;
	
	m_fAccDef = 0.f;
	m_pTransformCom->Set_Scale(_vec3{ 3.f, 3.f, 3.f });
	m_pTransformCom->Set_Dir(vec3.right);
	m_pTransformCom->Set_Pos(_vec3{ 100, m_pTransformCom->Get_Scale().y, 100 });	

	CEventMgr::GetInstance()->Add_Obj(L"Player_Shadow", CShadow_Player::Create(m_pGraphicDev, this));

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

	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_IDLE)], STATE_TYPE::BACK_IDLE, 0.2f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_IDLE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_WALK)], STATE_TYPE::BACK_WALK, 0.09f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_WALK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_ATTACK)], STATE_TYPE::BACK_ATTACK, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_ATTACK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_ATTACK1)], STATE_TYPE::BACK_ATTACK1, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_ATTACK1, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_ATTACK2)], STATE_TYPE::BACK_ATTACK2, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_ATTACK2, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_ROLL)], STATE_TYPE::BACK_ROLL, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_ROLL, pAnimation);
#pragma endregion

#pragma region Effect

	m_arrEffect[_uint(SKILL_TYPE::FIRE)] = CEffect_Fire::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(m_arrEffect[_uint(SKILL_TYPE::FIRE)], E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Fire", m_arrEffect[_uint(SKILL_TYPE::FIRE)]), E_FAIL);
	m_bOnSKill[0] = true;

	m_arrEffect[_uint(SKILL_TYPE::THUNDER)] = CEffect_Thunder::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(m_arrEffect[_uint(SKILL_TYPE::THUNDER)], E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Thunder", m_arrEffect[_uint(SKILL_TYPE::THUNDER)]), E_FAIL);
	m_bOnSKill[1] = true;

#pragma endregion

	m_pStateMachineCom->Set_Animator(m_pAnimatorCom);
	m_pStateMachineCom->Set_State(STATE_TYPE::FRONT_IDLE);


	// Camera Setting
	if (PLAY_MODE::TOOL != CManagement::GetInstance()->Get_PlayMode())
	{
		CCameraMgr::GetInstance()->Set_Follow(this);
		CCameraMgr::GetInstance()->Set_LookAt(this);
		CCameraMgr::GetInstance()->Set_ViewSpace();
	}

	// 테스트용
	m_iTempMode = 1;

	// << : Test : Range Test
	CGameObject* pGameObject = nullptr;

	pGameObject = CRangeObj::Create(m_pGraphicDev, this, 10.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Player_Range_Basic_Attack", pGameObject);
	arrRangeObj[(UINT)RANGE_TYPE::BASIC_ATTACK] = dynamic_cast<CRangeObj*>(pGameObject);

	return S_OK;
}

Engine::_int CPlayer::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	m_pStateMachineCom->Update_StateMachine(fTimeDelta);
	
	Key_Input(fTimeDelta);
	Regen_Def(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

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

	__super::LateUpdate_Object();

}

void CPlayer::Render_Object()
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	if(m_bHit)
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, HITCOLOR_R, HITCOLOR_G, HITCOLOR_B));

	m_pStateMachineCom->Render_StateMachine();
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pGraphicDev->SetTexture(0, NULL);

	__super::Render_Object(); 


}

void CPlayer::OnCollision_Enter(CGameObject* _pColObj)
{
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
		m_pTransformCom->Set_Pos(vMyPos + static_cast<CLineCollider*>(_pColObj->Get_Collider())->Get_Overlap_Line());
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
	_vec3 vMyPos  = m_pTransformCom->Get_Info(INFO_POS);
	_vec3 vColPos = _pColObj->Get_Transform()->Get_Info(INFO_POS);

	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::MONSTER:
	{
		if (Is_Attack())
		{
			dynamic_cast<CMonster*>(_pColObj)->Damaged(this);
			CCameraMgr::GetInstance()->Shake_Camera();
		}
		if (Is_Skill())
		{
			dynamic_cast<CMonster*>(_pColObj)->Damaged(this);
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
		m_pTransformCom->Set_Pos(vMyPos + static_cast<CLineCollider*>(_pColObj->Get_Collider())->Get_Overlap_Line());
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
		if (CInputDev::GetInstance()->Key_Down('E')) 
		{
			if (dynamic_cast<CNpc*>(_pColObj)->Get_IsReadyQuest() && !CQuestMgr::GetInstance()->Get_Active()) 
			{
				dynamic_cast<CNpc*>(_pColObj)->Set_IsReadyQuest(false);
				CQuestMgr::GetInstance()->Set_Quest(dynamic_cast<CNpc*>(_pColObj)->Get_HaveQuest());
				CQuestMgr::GetInstance()->Set_Active(true);
				CQuestMgr::GetInstance()->Set_Player(this);
			}
		}

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
	_vec3 vColPos = _pColObj->Get_Transform()->Get_Info(INFO_POS);

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
#pragma endregion


	return S_OK;
}

void CPlayer::Key_Input(const _float& fTimeDelta)
{
	if (CInputDev::GetInstance()->Key_Down('Z'))
		Damaged(10);
}

void CPlayer::Regen_Def(const _float& fTimeDelta)
{
	if (m_tStatInfo.fCurDef < m_tStatInfo.fMaxDef)
	{
		m_fAccDef += fTimeDelta;
		if (m_fAccDef > 8.f)
		{
			_float fRegenDef = m_tStatInfo.fCurDef + 20;
			if (fRegenDef > m_tStatInfo.fMaxDef)
				fRegenDef = m_tStatInfo.fMaxDef;
			Set_CurDef(fRegenDef);
			m_fAccDef = 0.f;
		}
	}
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

void CPlayer::Damaged(const _float& fDamage)
{
	if(m_tStatInfo.fCurDef > 0)
		Set_CurDef(m_tStatInfo.fCurDef - fDamage);
	else
	{
		if (m_tStatInfo.fCurHP <= 0)
		{
			Set_CurHP(m_tStatInfo.fMaxHP);
			m_bHit = true;
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