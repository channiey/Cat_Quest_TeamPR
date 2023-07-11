#include "Hedgehog.h"
#include "Export_Function.h"
#include "EventMgr.h"

#include "HedgehogState_fIdle.h"
#include "HedgehogState_fAttack.h"

#include "HedgehogState_bIdle.h"
#include "HedgehogState_bAttack.h"

#include "HedgehogState_Patrol.h"
#include "HedgehogState_Chase.h"
#include "HedgehogState_ComeBack.h"
#include "HedgehogState_Attack.h"

CHedgehog::CHedgehog(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonster(pGraphicDev)
{
}

CHedgehog::CHedgehog(const CMonster& rhs)
	: CMonster(rhs)
{
}

CHedgehog::~CHedgehog()
{
}

HRESULT CHedgehog::Ready_Object()
{
	__super::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(),E_FAIL);

	// MoveInfo
	m_tMoveInfo.fMoveSpeed = 10.f;
	m_tMoveInfo.fRotSpeed = 1.f;

	// Stat Info
	//m_tStatInfo.bDead = false;


	// Transform 
	m_pTransformCom->Set_Scale(_vec3{ 1.46f, 1.04f, 2.f });
	//m_pTransformCom->Set_Pos(_vec3{ 300.f, m_pTransformCom->Get_Scale().y, 300.f });

	m_pTransformCom->Set_Pos(_vec3{ VTXCNTX * 0.5f, m_pTransformCom->Get_Scale().y, 30.f });

	m_vOriginPos = m_pTransformCom->Get_Info(INFO_POS);


	

	fPatternTime = 2.f;


#pragma region State Add

	CState* pState;

	// Patrol
	pState = CHedgehogState_Patrol::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::PATROL, pState);

	// Chase
	pState = CHedgehogState_Chase::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::CHASE, pState);


	// ComeBack
	pState = CHedgehogState_ComeBack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::COMEBACK, pState);

	// Attack
	pState = CHedgegohState_Attack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_ATTACK, pState);


	//// Front - Idle
	//pState = CHedgehogState_fIdle::Create(m_pGraphicDev, m_pStateMachineCom);
	//m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_IDLE, pState);
	
	//// Front - Attack
	//pState = CHedgehogState_fAttack::Create(m_pGraphicDev, m_pStateMachineCom);
	//m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_ATTACK, pState);


	//// Back - Idle
	//pState = CHedgehogState_fIdle::Create(m_pGraphicDev, m_pStateMachineCom);
	//m_pStateMachineCom->Add_State(STATE_TYPE::BACK_IDLE, pState);
	
	//// Back - Attack
	//pState = CHedgehogState_bAttack::Create(m_pGraphicDev, m_pStateMachineCom);
	//m_pStateMachineCom->Add_State(STATE_TYPE::BACK_ATTACK, pState);



#pragma endregion

	m_pStateMachineCom->Set_State(STATE_TYPE::PATROL);


	return S_OK;
}

_int CHedgehog::Update_Object(const _float& fTimeDelta)
{
	

	Engine::Add_RenderGroup(RENDER_ALPHA, this);


	Move(fTimeDelta);
	

	_int iExit = CMonster::Update_Object(fTimeDelta);
	return iExit;
}

void CHedgehog::LateUpdate_Object()
{
	
	__super::LateUpdate_Object();

}

void CHedgehog::Render_Object()
{
	m_pTextureCom[14]->Render_Texture();
	
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	
	m_pBufferCom->Render_Buffer();
	
	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	

	//__super::Render_Object();

}

void CHedgehog::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CHedgehog::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CHedgehog::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CHedgehog::Add_Component()
{
	CComponent*		pComponent = nullptr;

	// AI
	pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);


	


#pragma region Texture

	pComponent = m_pTextureCom[_uint(STATE_TYPE::PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Hedgehog", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	pComponent = m_pTextureCom[_uint(STATE_TYPE::CHASE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Hedgehog", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


#pragma endregion


	return S_OK;
}

void CHedgehog::Move(const _float& fTimeDelta)
{
	m_pTransformCom->Translate(fTimeDelta * m_tMoveInfo.fMoveSpeed);
}



CHedgehog* CHedgehog::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHedgehog* pInstance = new CHedgehog(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Hedgehog Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHedgehog::Free()
{
	__super::Free();
}
