#include "stdafx.h"
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

// Move Effect
#include "MoveDust.h"
#include "MoveWater.h"

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

	m_pTransformCom->Set_Scale(_vec3{ 3.f, 3.f, 3.f });
	m_pTransformCom->Set_Dir(vec3.right);
	m_pTransformCom->Set_Pos(_vec3{ 100, m_pTransformCom->Get_Scale().y, 100 });	

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
	CAnimation* pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_HIT)], STATE_TYPE::FRONT_HIT, 0.2f, TRUE);
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


	m_pStateMachineCom->Set_Animator(m_pAnimatorCom);
	m_pStateMachineCom->Set_State(STATE_TYPE::FRONT_IDLE);


	// Camera Setting
	if (PLAY_MODE::TOOL != CManagement::GetInstance()->Get_PlayMode())
	{
		CCameraMgr::GetInstance()->Set_Follow(this);
		CCameraMgr::GetInstance()->Set_LookAt(this);
	}

	// 테스트용
	m_iTempMode = 1;

	return S_OK;
}

Engine::_int CPlayer::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	m_pStateMachineCom->Update_StateMachine(fTimeDelta);

	Key_Input(fTimeDelta);

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

	__super::LateUpdate_Object();

}

void CPlayer::Render_Object()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pStateMachineCom->Render_StateMachine();
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	__super::Render_Object(); // �ݶ��̴� ���
}

void CPlayer::OnCollision_Enter(CGameObject* _pColObj)
{
	_vec3 vMyPos = m_pTransformCom->Get_Info(INFO_POS);
	_vec3 vColPos = _pColObj->Get_Transform()->Get_Info(INFO_POS);

	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::MONSTER:
	{
		_vec3 vOverlap = static_cast<CRectCollider*>(m_pColliderCom)->Get_Overlap_Rect();

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
	_vec3 vMyPos = m_pTransformCom->Get_Info(INFO_POS);
	_vec3 vColPos = _pColObj->Get_Transform()->Get_Info(INFO_POS);

	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::MONSTER:
	{
		_vec3 vOverlap = static_cast<CRectCollider*>(m_pColliderCom)->Get_Overlap_Rect();

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
	// UI 테스트 용
	if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_Z))
		Set_CurHP(30);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_X))
		Set_CurHP(60);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_C))
		Set_CurHP(Get_StatInfo().fMaxHP);

	if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_B))
		Set_CurMP(30);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_N))
		Set_CurMP(60);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_M))
		Set_CurMP(Get_StatInfo().fMaxMP);

	if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_H))
		Set_CurDef(0);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_J))
		Set_CurDef(30);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_K))
		Set_CurDef(60);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_L))
		Set_CurDef(Get_StatInfo().fMaxDef);

	if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_I))
		Set_CurExp(0);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_O))
		Set_CurExp(200);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_P))
		Set_CurExp(500);

	CEnterUI* pEnterUI = static_cast<CEnterUI*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));
	if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_Q))
	{
		pEnterUI->EnterUI_On(UIENTER_TYPE::INSPECT, this);
		
	}
	if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_E))
		pEnterUI->EnterUI_Off();
		
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