#include "Fox.h"
#include "Export_Function.h"
#include "EventMgr.h"

#include "FoxState_Patrol.h"
#include "FoxState_Chase.h"
#include "FoxState_ComeBack.h"
#include "FoxState_Attack.h"

CFox::CFox(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonster(pGraphicDev)
{
}

CFox::CFox(const CMonster& rhs)
	: CMonster(rhs)
{
}

CFox::~CFox()
{
}

HRESULT CFox::Ready_Object()
{
	__super::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(),E_FAIL);

	// MoveInfo
	m_tMoveInfo.fMoveSpeed = 10.f;
	m_tMoveInfo.fRotSpeed = 1.f;

	// Stat Info
	//m_tStatInfo.bDead = false;


	// Transform 
	m_pTransformCom->Set_Scale(_vec3{ 1, 1.04f, 2.f });


	m_pTransformCom->Set_Pos(_vec3{ VTXCNTX * 0.3f, m_pTransformCom->Get_Scale().y, 30.f });

	m_pTransformCom->Set_Dir({ 1.42f, 0.f, 1.38f });

	m_vOriginPos = m_pTransformCom->Get_Info(INFO_POS);

	fPatternTime = 2.f;


#pragma region State Add

	CState* pState;

	// Patrol
	pState = CFoxState_Patrol::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::PATROL, pState);

	// Chase
	pState = CFoxState_Chase::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::CHASE, pState);


	// ComeBack
	pState = CFoxState_ComeBack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::COMEBACK, pState);

	// Attack
	pState = CFoxState_Attack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_ATTACK, pState);

#pragma endregion


	m_pStateMachineCom->Set_State(STATE_TYPE::PATROL);


	return S_OK;
}

_int CFox::Update_Object(const _float& fTimeDelta)
{
	

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	if (PLAY_MODE::TOOL == CManagement::GetInstance()->Get_PlayMode()) return 0;

	Move(fTimeDelta);
	

	_int iExit = CMonster::Update_Object(fTimeDelta);
	return iExit;
}

void CFox::LateUpdate_Object()
{
	
	__super::LateUpdate_Object();

}

void CFox::Render_Object()
{
	m_pTextureCom[14]->Render_Texture();
	
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	
	m_pBufferCom->Render_Buffer();
	
	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	

	//__super::Render_Object();

}

void CFox::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CFox::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CFox::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CFox::Add_Component()
{
	CComponent*		pComponent = nullptr;

	// AI
	pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);


	


#pragma region Texture

	pComponent = m_pTextureCom[_uint(STATE_TYPE::PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Fox", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	pComponent = m_pTextureCom[_uint(STATE_TYPE::CHASE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Fox", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


#pragma endregion


	return S_OK;
}

void CFox::Move(const _float& fTimeDelta)
{
	m_pTransformCom->Translate(fTimeDelta * m_tMoveInfo.fMoveSpeed);
}



CFox* CFox::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFox* pInstance = new CFox(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Fox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CFox::Free()
{
	__super::Free();
}