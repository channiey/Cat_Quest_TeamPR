#include "stdafx.h"
#include "Quest2.h"

#include "Export_Function.h"

#include "Player.h"
#include "TalkMgr.h"
#include "Management.h"
#include "GraphicDev.h"

#include "Npc_King.h"
#include "Npc_Citizen2.h"
#include "Dungeon_Grass.h"

#include "MageWeapon.h"
#include "Key.h"

CQuest2::CQuest2(wstring _QuestName, LPDIRECT3DDEVICE9 m_pGraphicDev)
{
	m_strQuestName = _QuestName;
	Init(m_pGraphicDev);
}

CQuest2::~CQuest2()
{
	if (m_pKey)
	{
		Safe_Release(m_pKey);
	}
}

void CQuest2::Init(LPDIRECT3DDEVICE9 m_pGraphicDev)
{
	// Mage
	CGameObject* pGameObject = CMageWeapon::Create(m_pGraphicDev);
	CEventMgr::GetInstance()->Add_Obj(L"Item_MageWeapon", pGameObject);
	m_vItemList.push_back(pGameObject);
	pGameObject->Set_Maintain(true);

	m_iKillCount = 0;
	m_bCreateKey = false;
	m_pKey = nullptr;
}

_bool CQuest2::Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator)
{
	if (!m_pPlayer)
	{
		m_pPlayer = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player");
	}

	// ����
	// ����Ʈ �ܰ谡 1�ܰ��̰� ���忡 Ű�� ������ �ȵ��� �� + (�ߺ� ���� ����)
	if (m_iLevel == 1 && !m_bCreateKey &&
		CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
	{
		m_pKey = CKey::Create(pGraphicDev);
		CEventMgr::GetInstance()->Add_Obj(L"Item_Key", m_pKey);
		m_bCreateKey = true;
	}
	// �� �̵��� m_bCreateKey false�� ����. ���� �˾Ƽ� ������.
	if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() != SCENE_TYPE::WORLD)
	{
		m_bCreateKey = false;
	}
	///////////////////////////////////////


	switch (m_iLevel)
	{
	case 0: // ������ ��ȭ
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::DUNGEON)
		{
			if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen2"))->Get_IsCol())
			{
				if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 21, OBJ_ID::NPC_CITIZEN_2)) {
					m_iLevel += 1;
					break;
				}
			}
		}
		break;
	case 1:
		// ���� ã��
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			if (m_bCreateKey)
			{
				if (dynamic_cast<CKey*>(m_pKey)->Get_IsCol())
				{
					dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Set_HaveKey(true);
					m_iLevel += 1;
				}
			}
		}		
		break;
	case 2:
		// ���ڿտ��� ����
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_King"))->Get_IsCol() &&
				dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Get_HaveKey() >= 1)
			{
				if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 11, OBJ_ID::NPC_KING)) {
					dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Set_HaveKey(false);
					dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Item(m_vItemList[0]);
					m_iLevel += 1;
				}
			}
		}
		break;
	case 3:
		m_iLevel = 99;
		// return true;
		break;
	}

	return false;
}
