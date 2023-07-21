#include "stdafx.h"

#include "Export_Function.h"
#include "EventMgr.h"

#include "Circle_Stemp.h"

CCircle_Stemp::CCircle_Stemp(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos)
	: CEffect(pGraphicDev, OBJ_ID::EFFECT_CIRCLE_STEMP)
{
	m_vPos = _pPos;
}

CCircle_Stemp::CCircle_Stemp(const CCircle_Stemp& rhs)
	: CEffect(rhs)
{
}

CCircle_Stemp::~CCircle_Stemp()
{
}

HRESULT CCircle_Stemp::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_bActive = true;

	m_fSize = 0.f;
	m_iAlpha = 250;
	m_iTranslucent = 250;
	m_fSpeed = 0.20f;
	return S_OK;
}

_int CCircle_Stemp::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_WDUI, this);

	// 웨이브
	m_pTransformCom->Set_Rot(_vec3{22.5f, 0.f, 0.f});
	m_pTransformCom->Set_Scale(_vec3{ m_fSize, m_fSize, m_fSize });
	m_pTransformCom->Set_Pos(_vec3{ m_vPos.x, m_vPos.y, m_vPos.z});

	return iExit;
}

void CCircle_Stemp::LateUpdate_Object()
{
	m_fSize += m_fSpeed;
	m_iTranslucent -= 10;
	
	if (m_iTranslucent <= 10)
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
	}

	__super::LateUpdate_Object();
}

void CCircle_Stemp::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iTranslucent, 255, 255, 255));

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));


}

HRESULT CCircle_Stemp::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Hedgehog_Stemp", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// 버퍼
	pComponent = m_pBufferCom = dynamic_cast<CTerrainRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, pComponent);
}

CCircle_Stemp* CCircle_Stemp::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos)
{
	CCircle_Stemp* pInstance = new CCircle_Stemp(pGraphicDev, _pPos);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Hedgehog_Stemp Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CCircle_Stemp::Free()
{
	__super::Free();
}
