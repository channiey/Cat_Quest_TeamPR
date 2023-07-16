#include "stdafx.h"
#include "Npc_King.h"

#include "Export_Function.h"

#include "Shadow_Npc.h"
#include "QuestMgr.h"
#include "Quest1.h"
#include "Quest2.h"

CNpc_King::CNpc_King(LPDIRECT3DDEVICE9 pGraphicDev)
	: CNpc(pGraphicDev, OBJ_ID::NPC_KING)
{
}

CNpc_King::CNpc_King(const CNpc& rhs)
	: CNpc(rhs)
{
}


CNpc_King::~CNpc_King()
{
}

HRESULT CNpc_King::Ready_Object()
{
	CNpc::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.1f, true);

	m_pTransformCom->Set_Pos(_vec3{ 125.f, m_pTransformCom->Get_Scale().y + 1.5f, 55.f });
	m_pTransformCom->Set_Scale(_vec3{ 3.f, 3.f, 3.f });

	CEventMgr::GetInstance()->Add_Obj(L"Npc_King_Shadow", CShadow_Npc::Create(m_pGraphicDev, this));

	m_pHaveQuest.push_back(CQuestMgr::GetInstance()->Set_HaveQuest(L"힘의 증명1"));
	m_pHaveQuest.push_back(CQuestMgr::GetInstance()->Set_HaveQuest(L"힘의 증명2"));
	m_pHaveQuest.push_back(CQuestMgr::GetInstance()->Set_HaveQuest(L"드라코스"));
	m_pHaveQuest.push_back(CQuestMgr::GetInstance()->Set_HaveQuest(L"죽음의 섬"));
	m_bReadyQuest = true;
	

	return S_OK;
}

_int CNpc_King::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CNpc::Update_Object(fTimeDelta);

	return iExit;
}

void CNpc_King::LateUpdate_Object()
{
	CNpc::LateUpdate_Object();
}

void CNpc_King::Render_Object()
{
	CNpc::Render_Object();
}

void CNpc_King::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CNpc_King::OnCollision_Stay(CGameObject* _pColObj)
{
	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::PLAYER:
	{
		// 충돌 검사.

		// 충돌 성공 시
		// 퀘스트 매니저에게 전달해서 퀘스트를 다음 단계로 넘기게 하자.
		// bool변수도 하나 필요할듯
		// 현재 본인이 퀘스트에 해당할 때만 다음 단계로 넘겨야 한다.
		// 
		CQuestMgr::GetInstance()->Npc_NextPointer();
	}
		break;
	
	default:
		break;
	}
}

void CNpc_King::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CNpc_King::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Npc_King", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CNpc_King* CNpc_King::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNpc_King* pInstance = new CNpc_King(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Npc_King Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CNpc_King::Free()
{
	CNpc::Free();
}
