#include "stdafx.h"
#include "Cloud1.h"

#include "Export_Function.h"

#include "Cloud1_Shadow.h"

CCloud1::CCloud1(LPDIRECT3DDEVICE9 pGraphicDev)
	: CEffect(pGraphicDev, OBJ_ID::EFFECT_CLOUD_1)
{
}

CCloud1::CCloud1(const CCloud1& rhs)
	: CEffect(rhs), m_pTextureCom(rhs.m_pTextureCom)
{
}

CCloud1::~CCloud1()
{
}

HRESULT CCloud1::Ready_Object()
{
	// __super::Ready_Object();

	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 100, m_pTransformCom->Get_Scale().y + 12.f, 100 });
	m_pTransformCom->Set_Scale(_vec3{ 5.f, 3.f, 5.f });

	// Add_GameObject를 호출할 때 this가 NULL이다 확인하자.
	CEventMgr::GetInstance()->Add_Obj(L"Cloud1_Shadow", CCloud1_Shadow::Create(m_pGraphicDev, this));

	return S_OK;
}

_int CCloud1::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	m_pTransformCom->Set_Pos(
		{this->m_pTransformCom->Get_Info(INFO_POS).x + 0.2f * fTimeDelta * 3.f ,
		 this->m_pTransformCom->Get_Info(INFO_POS).y ,
		 this->m_pTransformCom->Get_Info(INFO_POS).z }
	);

	return iExit;
}

void CCloud1::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CCloud1::Render_Object()
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

HRESULT CCloud1::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Colud1", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CCloud1::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CCloud1* CCloud1::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCloud1* pInstance = new CCloud1(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Effect_Cloud1 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CCloud1::Free()
{
	__super::Free();
}
