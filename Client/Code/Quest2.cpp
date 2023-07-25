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
	CEventMgr::GetInstance()->Add_Obj(L"라이트 냥", pSkill);
	m_vSkillList.push_back(pSkill);
	pSkill->Set_Maintain(true);

	// Item Ninja
	CGameObject* pGameObject = CNinjaWeapon::Create(m_pGraphicDev);
	CEventMgr::GetInstance()->Add_Obj(L"닌자냥이 세트", pGameObject);
	m_vItemList.push_back(pGameObject);
	pGameObject->Set_Maintain(true);

	//m_bCreateKey = false;
	//m_pKey = nullptr;
}

_bool CQuest2::Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble)
{

	// 열쇠
	// 퀘스트 단계가 1단계이고 월드에 키가 생성이 안됐을 때 + (중복 생성 방지)
	//if (m_iLevel == 1 && !m_bCreateKey &&
	//	CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
	//{
	//	m_pKey = CKey::Create(pGraphicDev);
	//	CEventMgr::GetInstance()->Add_Obj(L"Item_Key", m_pKey);
	//	m_bCreateKey = true;
	//}
	//// 씬 이동시 m_bCreateKey false로 변경. 차피 알아서 지워줌.
	//if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() != SCENE_TYPE::WORLD)
	//{
	//	m_bCreateKey = false;
	//}
	///////////////////////////////////////


	switch (m_iLevel)
	{
	case 0: // 대장장이와 대화
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc가 존재 한다면
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
	case 1: // 던전 몬스터 모두 소탕하기!
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
				// Npc가 존재 한다면
				if ((CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen2") != nullptr))
				{
					// 인디케이터 설정
					if (!*_IsAble)
					{
						dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
							dynamic_cast<CNpc*>(CManagement::GetInstance()->
								Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen2")));
						*_IsAble = true;
					}
					// 대화 후 보상
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
		m_iLevel = 99;
		*_IsAble = false; 
		return true;
		break;
	}

	return false;
}
