#include "stdafx.h"
#include "Quest1.h"

#include "Export_Function.h"

#include "Player.h"
#include "TalkMgr.h"
#include "Management.h"
#include "GraphicDev.h"

#include "IndicatorUI.h"

#include "Npc_King.h"
#include "Npc_Citizen2.h"
#include "Dungeon_Grass.h"

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
	// Warrior
	CGameObject* pGameObject = CWarriorWeapon::Create(m_pGraphicDev);
	CEventMgr::GetInstance()->Add_Obj(L"Item_WarriorWeapon", pGameObject);
	m_vItemList.push_back(pGameObject);
	pGameObject->Set_Maintain(true);

	m_iKillCount = 0;
}

_bool CQuest1::Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble)
{
	if (!m_pPlayer)
	{
		m_pPlayer = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player");
	}

	switch (m_iLevel)
	{
	case 0: // ���ڿտ��� ����
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc�� ���� �Ѵٸ�
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_King") != nullptr))
			{
				// �ε������� ����
				if (!*_IsAble)
				{
					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_King")));

					*_IsAble = true;
				}

				// ���ڿտ��� �� �ɱ�
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_King"))->Get_IsCol())
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 10, OBJ_ID::NPC_KING)) {
						m_iLevel += 1;
						if (*_IsAble)
						{
							dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
								dynamic_cast<CEnvironment*>(CManagement::GetInstance()->
									Get_GameObject(OBJ_TYPE::ENVIRONMENT, L"Dungeon_Grass")));
						}
						break;
					}
				}

			}
		}
		break;

	case 1: // ���� ���� ���� �� ����
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::DUNGEON_SWAMP)
		{
			// ��� �� óġ ��
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
						if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 20, OBJ_ID::NPC_CITIZEN_2))
						{
							m_iLevel += 1;
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
			m_iLevel = 99;
			return true;
		break;
	}

	return false;
}
