#include "stdafx.h"
#include "Zeolite.h"

#include "Export_Function.h"

#include "Shadow_Npc.h"
#include "TalkMgr.h"
#include "QuestMgr.h"

#include "ZeoliteDust.h"

CZeolite::CZeolite(LPDIRECT3DDEVICE9 pGraphicDev)
	: CNpc(pGraphicDev, OBJ_ID::NPC_ZEOLITE)
	, m_bDelete(false)
{
}

CZeolite::CZeolite(const CNpc& rhs)
	: CNpc(rhs)
{
}


CZeolite::~CZeolite()
{
}

HRESULT CZeolite::Ready_Object()
{
	CNpc::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 156.f, m_pTransformCom->Get_Scale().y + 5.4f, 102.f });
	m_pTransformCom->Set_Scale(_vec3{ 5.f, 8.75f, 5.f });

	// 가라앉기
	m_tPosDownLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tPosDownLerp.Set_Lerp(5.f, m_pTransformCom->Get_Info(INFO_POS).y, 5.4f);

	// 먼지 생성
	m_tDustCreateLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tDustCreateLerp.Set_Lerp(0.25f, 1.f, 0.f);

	m_szName = L"Npc_Zeolite";

	return S_OK;
}

_int CZeolite::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CGameObject::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	if (m_bDelete)
	{
		m_tPosDownLerp.Update_Lerp(fTimeDelta);
		if (!m_tPosDownLerp.bActive)
		{
			CEventMgr::GetInstance()->Delete_Obj(this);
			// 그럴 일은 없겠지만 혹시라도 다음 프레임에 못들어오게
			m_bDelete = true; 
		}

		m_tDustCreateLerp.Update_Lerp(fTimeDelta);
		if (!m_tDustCreateLerp.bActive)
		{
			CGameObject* pDust = CZeoliteDust::Create(m_pGraphicDev, this);
			m_tDustCreateLerp.Init_Lerp(LERP_MODE::EASE_IN);
			m_tDustCreateLerp.Set_Lerp(0.25f, 1.f, 0.f);
		}
	}

	return iExit;
}

void CZeolite::LateUpdate_Object()
{
	CNpc::LateUpdate_Object();
}

void CZeolite::Render_Object()
{
	m_pTextureCom->Render_Texture();
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	CGameObject::Render_Object(); // 콜라이더 출력
}

void CZeolite::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CZeolite::OnCollision_Stay(CGameObject* _pColObj)
{
	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::PLAYER:
	{
		m_bCol = true;
	}
	break;
	default:
		break;
	}
}

void CZeolite::OnCollision_Exit(CGameObject* _pColObj)
{
	m_bCol = false;
}

HRESULT CZeolite::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Npc_Zeolite", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CZeolite* CZeolite::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CZeolite* pInstance = new CZeolite(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Npc_Zeolite Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CZeolite::Free()
{
	CGameObject::Free();
}
