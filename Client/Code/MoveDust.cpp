#include "stdafx.h"
#include "Cloud1.h"

#include "Export_Function.h"

#include "MoveDust.h"

CMoveDust::CMoveDust(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CEffect(pGraphicDev, _pOwnerObject)
{
	m_pOwnerobject = _pOwnerObject;
}

CMoveDust::CMoveDust(const CMoveDust& rhs)
	: CEffect(rhs), m_pTextureCom(rhs.m_pTextureCom)
{
}

CMoveDust::~CMoveDust()
{
}

HRESULT CMoveDust::Ready_Object()
{
	__super::Ready_Object();

	// CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.1f, true);

	m_pTransformCom->Set_Pos(_vec3{ m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).x,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y - m_pOwnerobject->Get_Transform()->Get_Scale().y * 0.5f,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).z });
	m_pTransformCom->Set_Scale(_vec3{ 1.2f, 1.2f, 1.2f });

	m_bActive = true;
	m_iTranslucent = 200;

	return S_OK;
}

_int CMoveDust::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	m_pTransformCom->Set_Pos({ 
		m_pTransformCom->Get_Info(INFO_POS).x,
		m_pTransformCom->Get_Info(INFO_POS).y + 0.05f,
		m_pTransformCom->Get_Info(INFO_POS).z
		});

	m_pAnimation->Update_Animation(fTimeDelta);

	m_iTranslucent -= 5;

	if (m_pAnimation->Is_End()) 
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
	}
		
	
	return iExit;
}

void CMoveDust::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CMoveDust::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iTranslucent, 255, 255, 255));
	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pAnimation->Render_Animation();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	
	// CEffect::Render_Object();

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CMoveDust::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_MOVE_DUST", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CMoveDust::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CMoveDust* CMoveDust::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CMoveDust* pInstance = new CMoveDust(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("MOVE_DUST Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CMoveDust::Free()
{
	m_pAnimation->Release();
	__super::Free();
}
