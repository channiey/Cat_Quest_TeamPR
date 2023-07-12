#include "Ram.h"
#include "Export_Function.h"
#include "EventMgr.h"

#include "RamState_Patrol.h"
#include "RamState_Chase.h"
#include "RamState_ComeBack.h"
#include "RamState_Attack.h"

CRam::CRam(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonster(pGraphicDev)
{
}

CRam::CRam(const CMonster& rhs)
	: CMonster(rhs)
{
}

CRam::~CRam()
{
}

HRESULT CRam::Ready_Object()
{
	__super::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(),E_FAIL);

	// MoveInfo
	m_tMoveInfo.fMoveSpeed = 10.f;
	m_tMoveInfo.fRotSpeed = 1.f;

	// Stat Info
	//m_tStatInfo.bDead = false;


	// Transform 
	m_pTransformCom->Set_Scale(_vec3{ 1.44f, 1.48f, 2.f });
	//m_pTransformCom->Set_Pos(_vec3{ 300.f, m_pTransformCom->Get_Scale().y, 300.f });

	m_pTransformCom->Set_Pos(_vec3{ VTXCNTX * 0.9f, m_pTransformCom->Get_Scale().y, 30.f });

	m_pTransformCom->Set_Dir({ 0.f, 0.f, 1.f });

	m_vOriginPos = m_pTransformCom->Get_Info(INFO_POS);

	fPatternTime = 2.f;


#pragma region State Add

	CState* pState;

	// Patrol
	pState = CRamState_Patrol::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::PATROL, pState);

	// Chase
	pState = CRamState_Chase::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::CHASE, pState);


	// ComeBack
	pState = CRamState_ComeBack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::COMEBACK, pState);

	// Attack
	pState = CRamState_Attack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_ATTACK, pState);

#pragma endregion

	// ���� ���� - ���¸� ��� ����
	m_pStateMachineCom->Set_State(STATE_TYPE::PATROL);


	return S_OK;
}

_int CRam::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CMonster::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);





	


	return iExit;
}

void CRam::LateUpdate_Object()
{
	
	__super::LateUpdate_Object();

}

void CRam::Render_Object()
{

	// �ִϸ����� ��� x
	m_pTextureCom[14]->Render_Texture();
	
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	
	m_pBufferCom->Render_Buffer();
	
	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	
	// monster class���� �������� �ٷ� ������
	CGameObject::Render_Object(); // �ݶ��̴� ���
}

void CRam::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CRam::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CRam::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CRam::Add_Component()
{
	CComponent*		pComponent = nullptr;

	// AI
	pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);


	


#pragma region Texture

	pComponent = m_pTextureCom[_uint(STATE_TYPE::PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Ram", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	pComponent = m_pTextureCom[_uint(STATE_TYPE::CHASE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Ram", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


#pragma endregion


	return S_OK;
}



CRam* CRam::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRam* pInstance = new CRam(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Ram Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRam::Free()
{
	__super::Free();
}
