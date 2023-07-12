#include "Dragon.h"
#include "Export_Function.h"
#include "EventMgr.h"

#include "DragonState_fIdle.h"
#include "DragonState_fAttack.h"

#include "DragonState_bIdle.h"
#include "DragonState_bAttack.h"


CDragon::CDragon(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev)
{
}

CDragon::CDragon(const CMonster& rhs)
	:CMonster(rhs)
{
}

CDragon::~CDragon()
{
}

HRESULT CDragon::Ready_Object()
{
	__super::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	// MoveInfo
	m_tMoveInfo.fMoveSpeed = 10.f;
	m_tMoveInfo.fRotSpeed = 1.f;


	// Transform 
	m_pTransformCom->Set_Scale(_vec3{ 12.f, 12.f, 2.f });

	m_pTransformCom->Set_Pos(_vec3{ VTXCNTX * 0.5f  - 30.f,
									m_pTransformCom->Get_Scale().y,
									50.f });

	m_vOriginPos = m_pTransformCom->Get_Info(INFO_POS);


	fPatternTime = 2.f;
	fAccTime = 0.f;


#pragma region State Add

	CState* pState;

	// Front - Idle
	pState = CDragonState_fIdle::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_IDLE, pState);
	// Front - Attack
	pState = CDragonState_fAttack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_ATTACK, pState);


	// Back - Idle
	pState = CDragonState_bIdle::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_IDLE, pState);
	// Back - Attack
	pState = CDragonState_bAttack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_ATTACK, pState);


#pragma endregion


#pragma region Anim Add

	CAnimation* pAnimation;

	// Front - Idle
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_IDLE)], STATE_TYPE::FRONT_IDLE, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_IDLE, pAnimation);
	// Front - Attack
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_ATTACK)], STATE_TYPE::FRONT_ATTACK, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_ATTACK, pAnimation);


	// Back - Idle
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_IDLE)], STATE_TYPE::BACK_IDLE, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_IDLE, pAnimation);

	// Back - Attack
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_ATTACK)], STATE_TYPE::BACK_ATTACK, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_ATTACK, pAnimation);



#pragma endregion
	// 애니메이션, 상태 세팅
	m_pStateMachineCom->Set_Animator(m_pAnimatorCom);
	m_pStateMachineCom->Set_State(STATE_TYPE::FRONT_IDLE);


	return S_OK;
}

_int CDragon::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CMonster::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);


	return iExit;
}

void CDragon::LateUpdate_Object()
{

	__super::LateUpdate_Object();
}

void CDragon::Render_Object()
{

	// 애니메이터 사용 o
	__super::Render_Object();
}

void CDragon::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CDragon::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CDragon::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CDragon::Add_Component()
{
	CComponent* pComponent = nullptr;



	// Animator
	pComponent = m_pAnimatorCom = dynamic_cast<CAnimator*>(Engine::Clone_Proto(COMPONENT_TYPE::ANIMATOR, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::ANIMATOR, pComponent);


#pragma region Texture

	
	// Front Idle
	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_IDLE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Dragon_fIdle", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// Back Idle
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_IDLE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Dragon_bIdle", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// Front Attack
	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_ATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Dragon_fAttack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// Back Attack
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_ATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Dragon_bAttack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);




#pragma endregion




	return S_OK;
}

void CDragon::Move(const _float& fTimeDelta)
{


}

CDragon* CDragon::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDragon* pInstance = new CDragon(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Dragon Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CDragon::Free()
{
	__super::Free();
}
