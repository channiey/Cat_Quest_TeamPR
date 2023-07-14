#include "stdafx.h"
#include "Pollen.h"

#include "Export_Function.h"

#include "Cloud1_Shadow.h"

CPollen::CPollen(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 pPos)
	: CEffect(pGraphicDev, OBJ_ID::EFFECT_POLLEN)
{
	m_InitPos = pPos;
}

CPollen::CPollen(const CPollen& rhs)
	: CEffect(rhs), m_pTextureCom(rhs.m_pTextureCom)
{
}

CPollen::~CPollen()
{
}

HRESULT CPollen::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	D3DVIEWPORT9 viewPort =
		CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_ViewPort();

	m_pTransformCom->Set_Pos(m_InitPos);
	m_pTransformCom->Set_Scale(_vec3{ 0.3f, 0.3f, 0.3f });

	m_fSpeed = 4.f;

	return S_OK;
}

_int CPollen::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	m_pTransformCom->Translate(DIR_RIGHT, fTimeDelta * m_fSpeed);
	m_pTransformCom->Translate(DIR_UP, fTimeDelta * (m_fSpeed / 3.f));

	return iExit;
}

void CPollen::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CPollen::Render_Object()
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

HRESULT CPollen::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Pollen", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CPollen::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CPollen* CPollen::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 pPos)
{
	CPollen* pInstance = new CPollen(pGraphicDev, pPos);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Effect_Pollen Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPollen::Free()
{
	__super::Free();
}
