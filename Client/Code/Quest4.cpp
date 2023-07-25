#include "stdafx.h"
#include "Quest4.h"

#include "Export_Function.h"

#include "Player.h"
#include "TalkMgr.h"
#include "Management.h"
#include "GraphicDev.h"
#include "IndicatorUI.h"

#include "Npc_BlackSmith.h"
#include "Npc_Citizen1.h"

#include "WarriorWeapon.h"

CQuest4::CQuest4(wstring _QuestName, LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
	: m_iKillCount(0), m_bBossKill(false)
{
	m_strQuestName = _QuestName;
	Init(m_pGraphicDev, _pPlayer);
}

CQuest4::~CQuest4()
{
}

void CQuest4::Init(LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
{
	m_pPlayer = _pPlayer;

	// Item Warrior
	CGameObject* pGameObject = CWarriorWeapon::Create(m_pGraphicDev);
	CEventMgr::GetInstance()->Add_Obj(L"냥서커의 보물", pGameObject);
	m_vItemList.push_back(pGameObject);
	pGameObject->Set_Maintain(true);

}

_bool CQuest4::Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble)
{

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

				// 대화 후 다음 단계
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"))->Get_IsCol())
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 400, OBJ_ID::NPC_BLACKSMITH))
					{
						m_iLevel += 1;
						*_IsAble = false;
						break;
					}
				}
			}
		}
		break;
	case 1: // 해상 전투
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// 모든 해상몹들을 잡았다면
			for (_int i = 0; i < CEventMgr::GetInstance()->Get_VecDeleteObj().size(); ++i)
			{
				if (CEventMgr::GetInstance()->Get_VecDeleteObj()[i]->Get_Name() == L"Monster_Fish")
				{
					m_iKillCount += 1;
				}
				if (CEventMgr::GetInstance()->Get_VecDeleteObj()[i]->Get_Name() == L"Monster_Serpent")
				{
					m_iKillCount += 1;
				}
			}
			if (m_iKillCount >= 9)
			{
				if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 1000, OBJ_ID::NPC_BLACKSMITH))
				{
					m_iLevel += 1;
					*_IsAble = false;
					break;
				}
			}
		}
		break;
	case 2: // 죽음의 섬 전투
		m_iLevel += 1;
		*_IsAble = false;
		break;
	case 3: // 보스전 돌입 전 NPC 대화
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc가 존재 한다면
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen1") != nullptr))
			{
				if (!*_IsAble)
				{
					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen1")));
					*_IsAble = true;
				}

				// 대화 후 다음 단계
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen1"))->Get_IsCol())
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 410, OBJ_ID::NPC_CITIZEN_1))
					{
						m_iLevel += 1;
						*_IsAble = false;
						dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Item(
							m_vItemList[0]);
						break;
					}
				}
			}
		}
		break;
	case 4: // 보스전
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// 보스를 처치했다면
			for (_int i = 0; i < CEventMgr::GetInstance()->Get_VecDeleteObj().size(); ++i)
			{
				if (CEventMgr::GetInstance()->Get_VecDeleteObj()[i]->Get_Name() == L"Monster_VioletDragon")
				{
					m_bBossKill = true;
				}
			}
			if (m_bBossKill)
			{
				if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 1001, OBJ_ID::NPC_CITIZEN_1))
				{
					m_iLevel += 1;
					*_IsAble = false;
					break;
				}
			}
		}

		break;
	case 5: // 보스전
		m_iLevel = 99;
		*_IsAble = false;
		// return true;
		break;
	}

	return false;
}
