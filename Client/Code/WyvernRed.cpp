#include "WyvernRed.h"
#include "Export_Function.h"
#include "EventMgr.h"
//State - Front
#include "WyvernRedState_Patrol.h"
#include "WyvernRedState_Chase.h"
#include "WyvernRedState_Attack.h"
#include "WyvernRedState_ComeBack.h"
#include "WyvernRedState_Rest.h"
//State - Back				
#include "WyvernRedState_bPatrol.h"
#include "WyvernRedState_bChase.h"
#include "WyvernRedState_bAttack.h"
#include "WyvernRedState_bComeBack.h"
#include "WyvernRedState_bRest.h"
//Skill
#include "Skill_Monster_Beam.h"
#include "Skill_Monster_CircleAttack.h"
//Shadow
#include "Shadow_Monster.h"

CWyvernRed::CWyvernRed(LPDIRECT3DDEVICE9 pGraphicDev)
    : CMonster(pGraphicDev, OBJ_ID::MONSTER_WYVERNRED)
{
}

CWyvernRed::CWyvernRed(const CMonster& rhs)
    : CMonster(rhs)
{
}

CWyvernRed::~CWyvernRed()
{
}

HRESULT CWyvernRed::Ready_Object()
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
	m_vImageSize.x = 1.1f;  // 100px = 1.f
	m_vImageSize.y = 1.1f;
	m_vImageSize.z = 2.f;   // 고정 값


	// Transform 
	m_pTransformCom->Set_Scale(_vec3{ m_vImageSize.x * 2.f, m_vImageSize.y * 2.f , m_vImageSize.z });
	
	m_pTransformCom->Set_Pos(_vec3{ 200.f, m_pTransformCom->Get_Scale().y, 200.f });

	//m_vOriginPos = m_pTransformCom->Get_Info(INFO_POS);

	m_pTransformCom->Set_Dir({ -1.f, 0.f, 1.f });

	fPatternTime = 1.f;
	m_fAccTime = 0.f;

	m_fJumpingSpeed = 0.05;
	m_fMaxJumpY = m_pTransformCom->Get_Scale().y + 1.f;

	if (CManagement::GetInstance()->Get_PlayMode() == PLAY_MODE::GAME)
		CEventMgr::GetInstance()->Add_Obj(L"Monster_WyvernRed_Shadow", CShadow_Monster::Create(m_pGraphicDev, this));

	m_bSkill = false;

	// 스킬 생성
	m_pSkill = CSkill_Monster_Beam::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(m_pSkill, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Beam", m_pSkill), E_FAIL);

	m_pBaseSkill = CSkill_Monster_CircleAttack::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(m_pBaseSkill, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Base", m_pBaseSkill), E_FAIL);



#pragma region State Add

	CState* pState;
	// Front
	// Patrol
	pState = CWyvernRedState_Patrol::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::PATROL, pState);

	// Chase
	pState = CWyvernRedState_Chase::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::CHASE, pState);


	// ComeBack
	pState = CWyvernRedState_ComeBack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::COMEBACK, pState);

	// Attack
	pState = CWyvernRedState_Attack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::MONATTACK, pState);

	// Rest
	pState = CWyvernRedState_Rest::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::MONREST, pState);
	

	// Back 
	// Patrol
	pState = CWyvernRedState_bPatrol::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_PATROL, pState);

	// Chase
	pState = CWyvernRedState_bChase::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_CHASE, pState);


	// ComeBack
	pState = CWyvernRedState_bComeBack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_COMEBACK, pState);

	// Attack
	pState = CWyvernRedState_bAttack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_MONATTACK, pState);

	// Rest
	pState = CWyvernRedState_bRest::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_MONREST, pState);
	

#pragma endregion



#pragma region Anim Add

	CAnimation* pAnimation;

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


	// Back 
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





#pragma endregion

	// 애니메이션, 상태 세팅
	m_pStateMachineCom->Set_Animator(m_pAnimatorCom);
	m_pStateMachineCom->Set_State(STATE_TYPE::PATROL);

	m_szName = L"Monster_WyvernRed";

    return S_OK;
}

_int CWyvernRed::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CMonster::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);
	


	// Jumping 
	_vec3		vOwnerPos = m_pTransformCom->Get_Info(INFO_POS);
	float Y = m_pTransformCom->Get_Scale().y;
	STATE_TYPE eCurType = m_pStateMachineCom->Get_CurState();

	if (eCurType != STATE_TYPE::MONATTACK && eCurType != STATE_TYPE::BACK_MONATTACK)
	{

		if (vOwnerPos.y < Y || vOwnerPos.y > m_fMaxJumpY )
		{
			m_fJumpingSpeed *= -1;
		}
		m_pTransformCom->Translate(DIR_UP, m_fJumpingSpeed, WORLD);

	}


	// Skill Use
	STATE_TYPE CurState = m_pStateMachineCom->Get_CurState();
	if (STATE_TYPE::BACK_MONATTACK == CurState ||
		STATE_TYPE::MONATTACK == CurState ||
		STATE_TYPE::CHASE == CurState ||
		STATE_TYPE::BACK_CHASE == CurState)
	{
		m_fAccTime += fTimeDelta;

		if (m_fAccTime >= 2.f)
		{
			m_fAccTime = 0.f;
			m_pSkill->Play();
			m_bSkill = true;
		}
	}

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
	
	return iExit;
}

void CWyvernRed::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CWyvernRed::Render_Object()
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

void CWyvernRed::OnCollision_Enter(CGameObject* _pColObj)
{
	__super::OnCollision_Enter(_pColObj);
}

void CWyvernRed::OnCollision_Stay(CGameObject* _pColObj)
{
	__super::OnCollision_Stay(_pColObj);
}

void CWyvernRed::OnCollision_Exit(CGameObject* _pColObj)
{
	__super::OnCollision_Exit(_pColObj);
}

HRESULT CWyvernRed::Add_Component()
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

	// Front
	pComponent = m_pTextureCom[_uint(STATE_TYPE::PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_WyvernRed", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::CHASE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_WyvernRed", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::COMEBACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_WyvernRed", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::MONATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_WyvernRed_Attack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::MONREST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_WyvernRed", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// Back
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_WyvernRed", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_CHASE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_WyvernRed", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_COMEBACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_WyvernRed", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_MONATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_WyvernRed_Attack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_MONREST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_WyvernRed", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


#pragma endregion



	return S_OK;
}



CWyvernRed* CWyvernRed::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWyvernRed* pInstance = new CWyvernRed(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("WyvernRed Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CWyvernRed::Free()
{
	__super::Free();
}
