#include "stdafx.h"
#include "..\Header\Monster.h"
#include "AIComponent.h"
#include "Export_Function.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::MONSTER)
	, m_pAICom(nullptr)
	, m_pStateMachineCom(nullptr)
	, fPatternTime(0.f)
	, m_vOriginPos({0.f,0.f,0.f})
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


	m_pStateMachineCom->Set_Animator(m_pAnimatorCom);
	m_pStateMachineCom->Set_State(STATE_TYPE::FRONT_IDLE);
	return S_OK;
}

Engine::_int CMonster::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	m_pStateMachineCom->Update_StateMachine(fTimeDelta);

	return iExit;
}

void CMonster::LateUpdate_Object()
{
	__super::LateUpdate_Object();
	
	m_pStateMachineCom->LateUpdate_StateMachine();

}

void CMonster::Render_Object()  // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!
{

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pStateMachineCom->Render_StateMachine();

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));


	__super::Render_Object(); // 콜라이더 출력
}

void CMonster::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CMonster::OnCollision_Stay(CGameObject* _pColObj)
{
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



#pragma region Texture

	// 각각의 몬스터 객체에서 진행 

#pragma endregion




	return S_OK;
}

void CMonster::Free()
{
	__super::Free();
}

