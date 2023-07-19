#include "stdafx.h"
#include "Quest1.h"

#include "Export_Function.h"

#include "Player.h"
#include "TalkMgr.h"
#include "Management.h"
#include "GraphicDev.h"

#include "Npc_King.h"
#include "Npc_Mage.h"
#include "Npc_BlackSmith.h"

#include "WarriorWeapon.h"
#include "MageWeapon.h"
#include "NinjaWeapon.h"

CQuest1::CQuest1(wstring _QuestName, LPDIRECT3DDEVICE9 m_pGraphicDev)
{
	m_strQuestName = _QuestName;
	Init(m_pGraphicDev);
}

CQuest1::~CQuest1()
{
}

void CQuest1::Init(LPDIRECT3DDEVICE9 m_pGraphicDev)
{
	// Ninja
	CGameObject* pGameObject = CNinjaWeapon::Create(m_pGraphicDev);
	CEventMgr::GetInstance()->Add_Obj(L"Item_NinjaeWeapon", pGameObject);
	m_vItemList.push_back(pGameObject);
	// Warrior
	pGameObject = CWarriorWeapon::Create(m_pGraphicDev);
	CEventMgr::GetInstance()->Add_Obj(L"Item_WarriorWeapon", pGameObject);
	m_vItemList.push_back(pGameObject);
	// Mage
	pGameObject = CMageWeapon::Create(m_pGraphicDev);
	CEventMgr::GetInstance()->Add_Obj(L"Item_MageWeapon", pGameObject);
	m_vItemList.push_back(pGameObject);

	m_iKillCount = 0;
}

_bool CQuest1::Update(LPDIRECT3DDEVICE9 pGraphicDev)
{
	if (!m_pPlayer)
	{
		m_pPlayer = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player");
	}

	switch (m_iLevel)
	{
	case 0:
		// 사자왕에게 말 걸기
		//dynamic_cast<CNpc*>(CManagement::GetInstance()->
		//	Get_GameObject(OBJ_TYPE::NPC, L"Npc_King"))->Get_Collider()->Is_Collision();
		if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
			Get_GameObject(OBJ_TYPE::NPC, L"Npc_King"))->Get_IsCol())
		{
			if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 10, OBJ_ID::NPC_KING)) {
				m_iLevel += 1;
			}
		}
		break;
	case 1:
		// 고슴도치 2마리 잡고 사자왕에게 말걸기
		m_iKillCount += 1;
		if (m_iKillCount >= 2)
		{
			// 사자왕에게 말 걸기
			if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_King"))->Get_IsCol())
			{
				if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 11, OBJ_ID::NPC_KING))
				{
					m_iLevel += 1;
					dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Item(
						m_vItemList[0]);
				}
			}
		}
		break;
	case 2:
		// 대장장이 찾아가기
		if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
			Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"))->Get_IsCol())
		{
			if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 30, OBJ_ID::NPC_BLACKSMITH))
			{
				m_iLevel += 1; 
				dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Item(
					m_vItemList[1]);
				
			}
		}
		break;
	case 3:
		// 마법사 찾아가기
		if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
			Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage"))->Get_IsCol())
		{
			if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 20, OBJ_ID::NPC_MAGE))
			{
				m_iLevel += 1;
				dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Item(
					m_vItemList[2]);
			}
		}
		break;
	case 4:
		// 사자왕에게 돌아가기
		if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
			Get_GameObject(OBJ_TYPE::NPC, L"Npc_King"))->Get_IsCol())
		{
			if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 12, OBJ_ID::NPC_KING))
				m_iLevel += 1;
		}
		break;
	}

	return false;
}
