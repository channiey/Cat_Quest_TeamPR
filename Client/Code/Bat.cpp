#include "Bat.h"
#include "Export_Function.h"
#include "EventMgr.h"

#include "BatState_Patrol.h"
#include "BatState_Chase.h"
#include "BatState_Attack.h"
#include "BatState_ComeBack.h"

#include "BatState_bPatrol.h"
#include "BatState_bChase.h"
#include "BatState_bAttack.h"
#include "BatState_bComeBack.h"

#include "Shadow_Monster.h"


CBat::CBat(LPDIRECT3DDEVICE9 pGraphicDev)
    : CMonster(pGraphicDev, OBJ_ID::MONSTER_BAT)
{
}

CBat::CBat(const CMonster& rhs)
    : CMonster(rhs)
{
}

CBat::~CBat()
{
}

HRESULT CBat::Ready_Object()
{
    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	// MoveInfo
	m_tMoveInfo.fMoveSpeed = 3.f;
	m_tMoveInfo.fRotSpeed = 1.f;

	// Stat Info
	//m_tStatInfo.bDead = false;



	

	// 원래 이미지 크기
	m_vImageSize.x = 1.f; // 100px = 1.f
	m_vImageSize.y = 1.f;
	m_vImageSize.z = 2.f; //  고정


	// Transform 
	m_pTransformCom->Set_Scale(_vec3{ m_vImageSize.x * 2.5f, m_vImageSize.y * 2.5f, m_vImageSize.z });
	
	m_pTransformCom->Set_Pos(_vec3{ 90.f, m_pTransformCom->Get_Scale().y, 110.f });

	m_vOriginPos = m_pTransformCom->Get_Info(INFO_POS);

	m_pTransformCom->Set_Dir({ 1.f, 0.f, 1.f });

	fPatternTime = 1.f;
	
	m_fJumpingSpeed = 0.05f;
	m_fMaxJumpY = m_pTransformCom->Get_Scale().y + 1.f;

	
	CEventMgr::GetInstance()->Add_Obj(L"Monster_Bat_Shadow", CShadow_Monster::Create(m_pGraphicDev, this, OBJ_ID::EFFECT_MONSTER_SHADOW));
#pragma region State Add

	CState* pState;

	// Patrol
	pState = CBatState_Patrol::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::PATROL, pState);

	// Chase
	pState = CBatState_Chase::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::CHASE, pState);


	// ComeBack
	pState = CBatState_ComeBack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::COMEBACK, pState);

	// Attack
	pState = CBatState_Attack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::MONATTACK, pState);


	// Back
	// Patrol
	pState = CBatState_bPatrol::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_PATROL, pState);

	// Chase
	pState = CBatState_bChase::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_CHASE, pState);


	// ComeBack
	pState = CBatState_bComeBack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_COMEBACK, pState);

	// Attack
	pState = CBatState_bAttack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_MONATTACK, pState);

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
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::MONATTACK)], STATE_TYPE::MONATTACK, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::MONATTACK, pAnimation);

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
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_MONATTACK)], STATE_TYPE::BACK_MONATTACK, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_MONATTACK, pAnimation);



#pragma endregion

	// 애니메이션, 상태 세팅
	m_pStateMachineCom->Set_Animator(m_pAnimatorCom);
	m_pStateMachineCom->Set_State(STATE_TYPE::PATROL);

    return S_OK;
}

_int CBat::Update_Object(const _float& fTimeDelta)
{

	Engine::Add_RenderGroup(RENDER_ALPHA, this);
	_int iExit = CMonster::Update_Object(fTimeDelta);



	// Jumping 

	_vec3		vOwnerPos = m_pTransformCom->Get_Info(INFO_POS);
	_float		Y		  = m_pTransformCom->Get_Scale().y;
	STATE_TYPE	eCurType  = m_pStateMachineCom->Get_CurState();

	if (eCurType != STATE_TYPE::MONATTACK && eCurType != STATE_TYPE::BACK_MONATTACK)
	{

		if (vOwnerPos.y < Y || vOwnerPos.y >  m_fMaxJumpY)
		{
			m_fJumpingSpeed *= -1;
		}
		m_pTransformCom->Translate(DIR_UP, m_fJumpingSpeed, WORLD);

	}



	return iExit;
}

void CBat::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CBat::Render_Object()
{
	// 애니메이터 사용 o
	__super::Render_Object(); 
}

void CBat::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CBat::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CBat::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CBat::Add_Component()
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

	//  Front

	pComponent = m_pTextureCom[_uint(STATE_TYPE::PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Bat", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::CHASE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Bat", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::COMEBACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Bat", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::MONATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Bat", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);




	// Back

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Bat", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_CHASE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Bat", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_COMEBACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Bat", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_MONATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Bat", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);



#pragma endregion



	return S_OK;
}



CBat* CBat::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBat* pInstance = new CBat(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Bat Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBat::Free()
{
	__super::Free();
}
