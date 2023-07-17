#include "stdafx.h"

#include "Export_Function.h"

#include "MobCutEffect.h"

CMobCutEffect::CMobCutEffect(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos)
	: CEffect(pGraphicDev, OBJ_ID::EFFECT_MOBCUTEFFECT)
{
	m_vPos = _pPos;
}

CMobCutEffect::CMobCutEffect(const CMobCutEffect& rhs)
	: CEffect(rhs), m_pTextureCom(rhs.m_pTextureCom)
{
}

CMobCutEffect::~CMobCutEffect()
{
}

HRESULT CMobCutEffect::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_bActive = true;
	m_fSize = 0.f;
	return S_OK;
}

_int CMobCutEffect::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_WDUI, this); // 무조건 플레이어보다 늦게 그려지게 

	m_pTransformCom->Set_Pos(m_vPos);

	m_pTransformCom->Set_Scale(_vec3{ m_fSize, m_fSize, m_fSize });

	return iExit;
}

void CMobCutEffect::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CMobCutEffect::Render_Object()
{
	m_pTextureCom->Render_Texture();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
}

HRESULT CMobCutEffect::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Monster_Cut_Effect", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CMobCutEffect::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CMobCutEffect* CMobCutEffect::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos)
{
	CMobCutEffect* pInstance = new CMobCutEffect(pGraphicDev, _pPos);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Monster Cut Effect Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CMobCutEffect::Free()
{
	__super::Free();
}
