#include "stdafx.h"

#include "Export_Function.h"

#include "ItemSparkle.h"

CItemSparkle::CItemSparkle(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_MOVEDUST)
{
	m_pOwnerobject = _pOwnerObject;
}

CItemSparkle::CItemSparkle(const CItemSparkle& rhs)
	: CEffect(rhs), m_pTextureCom(rhs.m_pTextureCom)
{
}

CItemSparkle::~CItemSparkle()
{
}

HRESULT CItemSparkle::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_bActive = true;
	m_bPlay = true;
	m_bSizeUp = true;
	m_bPositionUp = false;
	m_fSize = 0.f;
	m_iReplayTime = GetTickCount64() + 500;
	return S_OK;
}

_int CItemSparkle::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_WDUI, this); // 무조건 아이템보다 늦게 그려지게

	if (!m_bPositionUp)
	{
		m_pTransformCom->Set_Pos(_vec3{ m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).x + m_pOwnerobject->Get_Transform()->Get_Scale().x * 0.5f,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y - m_pOwnerobject->Get_Transform()->Get_Scale().y * 0.5f,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).z });
	}
	else 
	{
		m_pTransformCom->Set_Pos(_vec3{ m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).x - m_pOwnerobject->Get_Transform()->Get_Scale().x * 0.5f,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y + m_pOwnerobject->Get_Transform()->Get_Scale().y * 0.5f,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).z});
	}

	m_pTransformCom->Set_Scale(_vec3{ m_fSize, m_fSize, m_fSize });


	if (!m_pOwnerobject->Is_Active())
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
		return iExit;
	}

	if (m_bPlay)
	{
		if (m_bSizeUp)
		{
			m_fSize += 0.05f;
			if (m_fSize > 1.f)
				m_bSizeUp = false;
		}
		else
		{
			m_fSize -= 0.05f;
			if (m_fSize < 0.f)
			{
				m_iReplayTime = GetTickCount64() + 1000;
				m_bPlay = false;
			}
		}
	}


	return iExit;
}

void CItemSparkle::LateUpdate_Object()
{
	if(!m_bPlay)
	{
		if (m_iReplayTime < GetTickCount64())
		{
			m_bPlay = true;
			m_bSizeUp = true;
			if (!m_bPositionUp)
				m_bPositionUp = true;
			else
				m_bPositionUp = false;
		}
	}
	
	__super::LateUpdate_Object();
}

void CItemSparkle::Render_Object()
{
	m_pTextureCom->Render_Texture();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
}

HRESULT CItemSparkle::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_ItemSparkle", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CItemSparkle::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CItemSparkle* CItemSparkle::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CItemSparkle* pInstance = new CItemSparkle(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("ItemSparkle Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CItemSparkle::Free()
{
	__super::Free();
}
