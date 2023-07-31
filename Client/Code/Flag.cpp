#include "stdafx.h"
#include "..\Header\Flag.h"
#include "EventMgr.h"
#include "Export_Function.h"
#include "FlagOwner.h"
#include "SoundMgr.h"

CFlag::CFlag(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::FLAG, _eID)
	, m_iCurIn(0)
	, m_iPrevIn(0)
	, m_eCurCollison(PLAYER_COLLISION2::NONE)
{

}

CFlag::CFlag(const CFlag& rhs)
	: Engine::CGameObject(rhs)
{
}

CFlag::~CFlag()
{
}

HRESULT CFlag::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	FAILED_CHECK_RETURN(Add_RangeObj(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 4.f, 4.f, 4.f });

	return S_OK;
}

_int CFlag::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	Check_Player_Collision();

	if (PLAYER_COLLISION2::ENTER == m_eCurCollison)
		Enter_Player();
	else if (PLAYER_COLLISION2::EXIT == m_eCurCollison)
		Exit_Player();



	return iExit;
}

void CFlag::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CFlag::Render_Object()
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	_matrix matWorld = m_pTransformCom->Get_WorldMat();
	_matrix matBill;
	//_vec3 vPos;
	//
	//memcpy(&vPos, &matWorld.m[3], sizeof(_vec3));
	
	matWorld *= *D3DXMatrixInverse(&matBill, NULL, &CCameraMgr::GetInstance()->Get_Billboard_X());
	//memcpy(&matWorld.m[3], &vPos, sizeof(_vec3));
}

void CFlag::OnCollision_Enter(CGameObject* _pColObj)
{
	NULL_CHECK(m_pFlagOwner);
	m_pFlagOwner->Check_Player_Collision(m_eID);
	++m_iCurIn;
}

void CFlag::OnCollision_Stay(CGameObject* _pColObj)
{

}

void CFlag::OnCollision_Exit(CGameObject* _pColObj)
{
	--m_iCurIn;
}

HRESULT CFlag::Add_Component()
{
	CComponent* pComponent = nullptr;

	// Buffer
	pComponent = m_pBufferCom = dynamic_cast<CTerrainRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, pComponent);

	return S_OK;
}

HRESULT CFlag::Add_RangeObj()
{
	return S_OK;
}

void CFlag::Check_Player_Collision()
{
	if (0 == m_iPrevIn && 0 < m_iCurIn)
	{
		m_eCurCollison = PLAYER_COLLISION2::ENTER;
		m_iPrevIn = m_iCurIn;

		return;
	}
	else if (0 < m_iPrevIn && 0 == m_iCurIn)
	{
		m_eCurCollison = PLAYER_COLLISION2::EXIT;
		m_iPrevIn = m_iCurIn;

		return;
	}

	if (0 < m_iCurIn)
		m_eCurCollison = PLAYER_COLLISION2::STAY;
	else
		m_eCurCollison = PLAYER_COLLISION2::NONE;

	m_iPrevIn = m_iCurIn;

}

void CFlag::Enter_Player()
{
}

void CFlag::Exit_Player()
{
}


void CFlag::Free()
{
	__super::Free();
}
