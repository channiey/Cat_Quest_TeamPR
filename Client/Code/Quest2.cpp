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
}

void CQuest2::Init(LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
{
	m_pPlayer = _pPlayer;

	// Fire Skill
	CSkill* pSkill = CSkill_Player_Thunder::Create(m_pGraphicDev, m_pPlayer);
	CEventMgr::GetInstance()->Add_Obj(L"����Ʈ ��", pSkill);
	m_vSkillList.push_back(pSkill);
	pSkill->Set_Maintain(true);

	// Item Ninja
	CGameObject* pGameObject = CNinjaWeapon::Create(m_pGraphicDev);
	CEventMgr::GetInstance()->Add_Obj(L"���ڳ��� ��Ʈ", pGameObject);
	m_vItemList.push_back(pGameObject);
	pGameObject->Set_Maintain(true);

	m_tQuestContent.push_back({ L"1.���� �� ��� ���� ����", false });
	m_tQuestContent.push_back({ L"2.��� ���� �� ���� �� \n�������� ã��", false });
}

_bool CQuest2::Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble)
{
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
						*_IsAble = false;
						break;
					}
				}
			}
		}
		break;
	case 1: // ���� ���� ��� �����ϱ�!
		m_bShowQuestView = true;
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			if (!*_IsAble)
			{
				dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
					dynamic_cast<CDungeon_Grass*>(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::ENVIRONMENT, L"Dungeon_Grass")));
				*_IsAble = true;
			}
		}

		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::DUNGEON_SWAMP)
		{
			if (CManagement::GetInstance()->
				Get_CurScene()->
				Get_Layer(OBJ_TYPE::MONSTER)->Get_ObjectMap().empty())
			{
				m_tQuestContent[0].m_strQuestContent = L"1.���� �� ��� ���� ����\n�Ϸ�";
				m_tQuestContent[0].m_bClear = true;
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
			else
			{
				m_tQuestContent[0].m_strQuestContent = L"1.���� �� ��� ���� ����\n" + to_wstring(CManagement::GetInstance()->
					Get_CurScene()->
					Get_Layer(OBJ_TYPE::MONSTER)->Get_ObjectMap().size()) + L"���� ����";
			}

		}
		break;
	case 2:
		m_iLevel = 99;
		*_IsAble = false; 
		m_bShowQuestView = false;
		return true;
		break;
	}

	return false;
}
