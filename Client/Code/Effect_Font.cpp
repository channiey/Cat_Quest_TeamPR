#include "stdafx.h"
#include "Effect_Font.h"

#include "Export_Function.h"

CEffect_Font::CEffect_Font(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pOwner, _uint iNumb, FONT_TYPE eFont)
	: CEffect(pGraphicDev, pOwner, OBJ_ID::EFFECT_FONT), m_iNumb(iNumb), m_eFontType(eFont)
{
}

CEffect_Font::CEffect_Font(const CEffect_Font& rhs)
	: CEffect(rhs)
{
}

CEffect_Font::~CEffect_Font()
{
}

HRESULT CEffect_Font::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);



	switch (m_eFontType)
	{
	case Engine::FONT_TYPE::DAMAGE:
		m_strFont = to_wstring(m_iNumb);
		break;
	case Engine::FONT_TYPE::HIT:
		m_strFont = L"-" + to_wstring(m_iNumb);
		break;
	case Engine::FONT_TYPE::GOLD:
		m_strFont = L"+" + to_wstring(m_iNumb);
		break;
	case Engine::FONT_TYPE::EXP:
		m_strFont = L"+" + to_wstring(m_iNumb) + L"xp";
		break;
	default:
		break;
	}

	rcFont.left = m_pOwnerobject->Get_Transform()->Get_Info(INFO::INFO_POS).x - 50;


	return S_OK;
}

_int CEffect_Font::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);


	return iExit;
}

void CEffect_Font::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEffect_Font::Render_Object()
{

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	__super::Render_Object();
}

HRESULT CEffect_Font::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CEffect_Font::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CEffect_Font* CEffect_Font::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pOwner, _uint iNumb, FONT_TYPE eFont)
{
	CEffect_Font* pInstance = new CEffect_Font(pGraphicDev, pOwner, iNumb, eFont);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Effect_Font Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffect_Font::Free()
{
	__super::Free();
}
