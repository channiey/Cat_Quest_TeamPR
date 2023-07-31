#include "stdafx.h"

#include "Effect_Rain.h"

#include "Export_Function.h"


CEffect_Rain::CEffect_Rain(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 pPos)
	: CEffect(pGraphicDev, OBJ_ID::EFFECT_POLLEN)
{
	m_InitPos = pPos;
}

CEffect_Rain::CEffect_Rain(const CEffect_Rain& rhs)
	: CEffect(rhs), m_pTextureCom(rhs.m_pTextureCom)
{
}

CEffect_Rain::~CEffect_Rain()
{
}

HRESULT CEffect_Rain::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_fSpeed = 5 + rand() % 5;

	_float fMin = 0.1;
	_float fMax = 0.25;
	_float	fScale = fMin + (float)(rand()) / ((float)(RAND_MAX / (fMax - fMin)));
	fScale = floor(fScale * 100) / 100;
	m_pTransformCom->Set_Scale(_vec3{ fScale, fScale, fScale });


	m_pTransformCom->Set_Pos(m_InitPos);

	m_fAccTime = 0.f;

	m_vWindVelo.x = (double)rand() / RAND_MAX - 0.5;
	m_vWindVelo.y = (double)rand() / RAND_MAX - 0.5;
	m_vWindVelo.z = (double)rand() / RAND_MAX - 0.5;

	m_bActive = true;

	return S_OK;
}

_int CEffect_Rain::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);


	m_vWindVelo.x += (double)rand() / RAND_MAX * WINDFORCE - WINDFORCE / 2.0;
	m_vWindVelo.y -= (double)rand() / RAND_MAX * WINDFORCE * 1;
	//m_vWindVelo.z += (double)rand() / RAND_MAX * WINDFORCE - WINDFORCE / 2.0;

	m_pTransformCom->Set_Dir(m_vWindVelo);
	m_pTransformCom->Translate(fTimeDelta * m_fSpeed);

	_vec3 vRainPos = m_pTransformCom->Get_Info(INFO::INFO_POS);

	if (vRainPos.y <= 0.05f)
		CEventMgr::GetInstance()->Delete_Obj(this);

	return iExit;
}

void CEffect_Rain::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEffect_Rain::Render_Object()
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

HRESULT CEffect_Rain::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Rain", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CEffect_Rain::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
}

CEffect_Rain* CEffect_Rain::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 pPos)
{
	CEffect_Rain* pInstance = new CEffect_Rain(pGraphicDev, pPos);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Effect_Rain Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffect_Rain::Free()
{
	__super::Free();
}
