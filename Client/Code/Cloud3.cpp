#include "stdafx.h"
#include "Cloud3.h"

#include "Export_Function.h"

#include "Cloud3_Shadow.h"

CCloud3::CCloud3(LPDIRECT3DDEVICE9 pGraphicDev)
	: CEffect(pGraphicDev, OBJ_ID::EFFECT_CLOUD_3)
{
}

CCloud3::CCloud3(const CCloud3& rhs)
	: CEffect(rhs), m_pTextureCom(rhs.m_pTextureCom)
{
}

CCloud3::~CCloud3()
{
}

HRESULT CCloud3::Ready_Object()
{
	// __super::Ready_Object();

	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 100, m_pTransformCom->Get_Scale().y + 12.f, 100 });
	m_pTransformCom->Set_Scale(_vec3{ 5.f, 3.f, 5.f });

	// Add_GameObject를 호출할 때 this가 NULL이다 확인하자.
	CEventMgr::GetInstance()->Add_Obj(L"Cloud3_Shadow", CCloud3_Shadow::Create(m_pGraphicDev, this));

	return S_OK;
}

_int CCloud3::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	m_pTransformCom->Set_Pos(
		{ this->m_pTransformCom->Get_Info(INFO_POS).x + 0.2f * fTimeDelta * 1.5f ,
		 this->m_pTransformCom->Get_Info(INFO_POS).y ,
		 this->m_pTransformCom->Get_Info(INFO_POS).z }
	);

	return iExit;
}

void CCloud3::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CCloud3::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(200, 255, 255, 255));

	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	CEffect::Render_Object();

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CCloud3::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Colud3", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CCloud3::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CCloud3* CCloud3::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCloud3* pInstance = new CCloud3(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Effect_Cloud3 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CCloud3::Free()
{
	__super::Free();
}
