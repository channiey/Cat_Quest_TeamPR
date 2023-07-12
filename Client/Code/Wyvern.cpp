#include "Wyvern.h"
#include "Export_Function.h"
#include "EventMgr.h"

#include "WyvernState_Patrol.h"
#include "WyvernState_Chase.h"
#include "WyvernState_Attack.h"
#include "WyvernState_ComeBack.h"



CWyvern::CWyvern(LPDIRECT3DDEVICE9 pGraphicDev)
    : CMonster(pGraphicDev)
{
}

CWyvern::CWyvern(const CMonster& rhs)
    : CMonster(rhs)
{
}

CWyvern::~CWyvern()
{
}

HRESULT CWyvern::Ready_Object()
{
    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	// MoveInfo
	m_tMoveInfo.fMoveSpeed = 5.f;
	m_tMoveInfo.fRotSpeed = 1.f;

	// Stat Info
	//m_tStatInfo.bDead = false;

	// Transform 
	m_pTransformCom->Set_Scale(_vec3{ 2.f, 2.f, 2.f });
	
	m_pTransformCom->Set_Pos(_vec3{ VTXCNTX * 0.1f, m_pTransformCom->Get_Scale().y, 30.f });

	m_vOriginPos = m_pTransformCom->Get_Info(INFO_POS);

	m_pTransformCom->Set_Dir({ -1.f, 0.f, 1.f });

	fPatternTime = 1.f;
	
#pragma region State Add

	CState* pState;

	// Patrol
	pState = CWyvernState_Patrol::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::PATROL, pState);

	// Chase
	pState = CWyvernState_Chase::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::CHASE, pState);


	// ComeBack
	pState = CWyvernState_ComeBack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::COMEBACK, pState);

	// Attack
	pState = CWyvernState_Attack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_ATTACK, pState);



	
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
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_ATTACK)], STATE_TYPE::FRONT_ATTACK, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_ATTACK, pAnimation);

#pragma endregion

	
	m_pStateMachineCom->Set_Animator(m_pAnimatorCom);

	m_pStateMachineCom->Set_State(STATE_TYPE::PATROL);

    return S_OK;
}

_int CWyvern::Update_Object(const _float& fTimeDelta)
{


	Engine::Add_RenderGroup(RENDER_ALPHA, this);
	if (PLAY_MODE::TOOL == CManagement::GetInstance()->Get_PlayMode()) return 0;

	Move(fTimeDelta);

	_int iExit = CMonster::Update_Object(fTimeDelta);
	return iExit;
}

void CWyvern::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CWyvern::Render_Object()
{
	__super::Render_Object();
}

void CWyvern::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CWyvern::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CWyvern::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CWyvern::Add_Component()
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

	pComponent = m_pTextureCom[_uint(STATE_TYPE::PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Wyvern", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	//pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_IDLE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Bat", this));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	pComponent = m_pTextureCom[_uint(STATE_TYPE::CHASE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Wyvern", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	pComponent = m_pTextureCom[_uint(STATE_TYPE::COMEBACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Wyvern", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_ATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Wyvern", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


#pragma endregion



	return S_OK;
}

void CWyvern::Move(const _float& fTimeDelta)
{
	m_pTransformCom->Translate(fTimeDelta * m_tMoveInfo.fMoveSpeed);
}

CWyvern* CWyvern::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWyvern* pInstance = new CWyvern(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Wyvern Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CWyvern::Free()
{
	__super::Free();
}