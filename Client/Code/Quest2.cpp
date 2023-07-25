#include "stdafx.h"
#include "Quest2.h"

#include "Export_Function.h"

#include "Player.h"
#include "TalkMgr.h"
#include "Management.h"
#include "GraphicDev.h"
#include "IndicatorUI.h"

#include "Npc_BlackSmith.h"
#include "Npc_Citizen2.h"
#include "Dungeon_Grass.h"

#include "NinjaWeapon.h"
#include "Skill_Player_Thunder.h"
#include "Key.h"

CQuest2::CQuest2(wstring _QuestName, LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
{
	m_strQuestName = _QuestName;
	Init(m_pGraphicDev, _pPlayer);
}

CQuest2::~CQuest2()
{
	//if (m_pKey)
	//{
	//	Safe_Release(m_pKey);
	//}
}

void CQuest2::Init(LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
{
	m_pPlayer = _pPlayer;

	// Fire Skill
	CSkill* pSkill = CSkill_Player_Thunder::Create(m_pGraphicDev, m_pPlayer);
	CEventMgr::GetInstance()->Add_Obj(L"Skill_Thunder", pSkill);
	m_vSkillList.push_back(pSkill);
	pSkill->Set_Maintain(true);

	// Item Ninja
	CGameObject* pGameObject = CNinjaWeapon::Create(m_pGraphicDev);
	CEventMgr::GetInstance()->Add_Obj(L"Item_NinjaWeapon", pGameObject);
	m_vItemList.push_back(pGameObject);
	pGameObject->Set_Maintain(true);

	//m_bCreateKey = false;
	//m_pKey = nullptr;
}

_bool CQuest2::Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble)
{

	// ����
	// ����Ʈ �ܰ谡 1�ܰ��̰� ���忡 Ű�� ������ �ȵ��� �� + (�ߺ� ���� ����)
	//if (m_iLevel == 1 && !m_bCreateKey &&
	//	CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
	//{
	//	m_pKey = CKey::Create(pGraphicDev);
	//	CEventMgr::GetInstance()->Add_Obj(L"Item_Key", m_pKey);
	//	m_bCreateKey = true;
	//}
	//// �� �̵��� m_bCreateKey false�� ����. ���� �˾Ƽ� ������.
	//if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() != SCENE_TYPE::WORLD)
	//{
	//	m_bCreateKey = false;
	//}
	///////////////////////////////////////


	switch (m_iLevel)
	{
	case 0: // �������̿� ��ȭ
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc�� ���� �Ѵٸ�
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith") != nullptr))
			{
				if (!*_IsAble)
				{
					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith")));
					*_IsAble = true;
				}

				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"))->Get_IsCol())
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 200, OBJ_ID::NPC_BLACKSMITH)) {
						m_iLevel += 1;
						if (*_IsAble)
						{
							dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
								dynamic_cast<CEnvironment*>(CManagement::GetInstance()->
									Get_GameObject(OBJ_TYPE::ENVIRONMENT, L"Dungeon_Grass")));
							*_IsAble = false;
						}
						break;
					}
				}
			}
		}
		break;
	case 1: // ���� ���� ��� �����ϱ�!
		// ���� ã��
		// if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		// {
		// 	if (m_bCreateKey)
		// 	{
		// 		if (dynamic_cast<CKey*>(m_pKey)->Get_IsCol())
		// 		{
		// 			dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Set_HaveKey(true);
		// 			m_iLevel += 1;
		// 		}
		// 	}
		// }	
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::DUNGEON_SWAMP)
		{
			if (CManagement::GetInstance()->
				Get_CurScene()->
				Get_Layer(OBJ_TYPE::MONSTER)->Get_ObjectMap().empty())
			{
				// Npc�� ���� �Ѵٸ�
				if ((CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen2") != nullptr))
				{
					// �ε������� ����
					if (!*_IsAble)
					{
						dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
							dynamic_cast<CNpc*>(CManagement::GetInstance()->
								Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen2")));
						*_IsAble = true;
					}
					// ��ȭ �� ����
					if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen2"))->Get_IsCol())
					{
						if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 201, OBJ_ID::NPC_CITIZEN_1))
						{
							m_iLevel += 1;
							dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Skill(
								m_vSkillList[0]);
							dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Item(
								m_vItemList[0]);
							break;
						}
					}
				}
			}

		}
		break;
	case 2:
		// ���ڿտ��� ����
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_King") != nullptr))
			{
				if (!*_IsAble)
				{
					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_King")));
					*_IsAble = true;
				}

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
		}
		break;
	case 3:
		m_iLevel = 99;
		*_IsAble = false; // ���� ����Ʈ�� ��
		// return true;
		break;
	}

	return false;
}
