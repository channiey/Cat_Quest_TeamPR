#include "stdafx.h"
#include "Quest1.h"

#include "Export_Function.h"

#include "Player.h"
#include "TalkMgr.h"
#include "Management.h"
#include "GraphicDev.h"

#include "IndicatorUI.h"

#include "Skill.h"
#include "Npc_BlackSmith.h"
#include "Skill_Player_Fire.h"

CQuest1::CQuest1(wstring _QuestName, LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
	: m_iKillCount(0)
{
	m_strQuestName = _QuestName;
	Init(m_pGraphicDev, _pPlayer);
}

CQuest1::~CQuest1()
{
}

void CQuest1::Init(LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
{
	m_pPlayer = _pPlayer;

	// Fire Skill
	CSkill* pSkill = CSkill_Player_Fire::Create(m_pGraphicDev, m_pPlayer);
	CEventMgr::GetInstance()->Add_Obj(L"Skill_Fire", pSkill);
	m_vSkillList.push_back(pSkill);
	pSkill->Set_Maintain(true);

	m_iKillCount = 0;
}

_bool CQuest1::Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble)
{
	switch (m_iLevel)
	{
	case 0: // 대장장이에게 가기
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc가 존재 한다면
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith") != nullptr))
			{
				// 인디케이터 설정
				if (!*_IsAble)
				{
					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith")));

					*_IsAble = true;
				}

				// 대장장이에게 말 걸기
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"))->Get_IsCol())
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 100, OBJ_ID::NPC_BLACKSMITH)) {
						m_iLevel += 1;
						if (*_IsAble)
						{
						//	dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						//		dynamic_cast<CEnvironment*>(CManagement::GetInstance()->
						//			Get_GameObject(OBJ_TYPE::ENVIRONMENT, L"Dungeon_Grass")));
							*_IsAble = false;
						}
						break;
					}
				}

			}
		}
		break;

	case 1: // 고슴도치 5마리 소탕
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// 고슴도치 5마리를 잡았다면
			//if (CManagement::GetInstance()->
			//	Get_CurScene()->
			//	Get_Layer(OBJ_TYPE::MONSTER)->Get_ObjectMap().empty())
			for (_int i = 0; i < CEventMgr::GetInstance()->Get_VecDeleteObj().size(); ++i)
			{
				if (CEventMgr::GetInstance()->Get_VecDeleteObj()[i]->Get_Name() == L"Monster_Hedgehog")
				{
					m_iKillCount += 1;
				}
			}
			if (m_iKillCount >= 5)
			{
				{
					// Npc가 존재 한다면
					if ((CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith") != nullptr))
					{
						// 인디케이터 설정
						if (!*_IsAble)
						{
							dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
								dynamic_cast<CNpc*>(CManagement::GetInstance()->
									Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith")));
							*_IsAble = true;
						}
						// 대화 후 보상
						if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"))->Get_IsCol())
						{
							if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 101, OBJ_ID::NPC_BLACKSMITH))
							{
								m_iLevel += 1;
								dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Skill(
									m_vSkillList[0]);
								*_IsAble = false;
								break;
							}
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
