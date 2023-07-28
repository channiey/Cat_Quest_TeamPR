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

#include "WeaponGetEffect.h"

CQuest4::CQuest4(wstring _QuestName, LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
	: m_iMonsterCount(0), m_bBossKill(false)
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

	m_tQuestContent.push_back({ L"1.바다 위 모든 몬스터 소탕", false });

}

_bool CQuest4::Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble)
{
	// 대화 가능 상태 여부 확인
	ePlayerState = dynamic_cast<CPlayer*>(m_pPlayer)->Get_StateM()->Get_CurState();
	m_bReadyTalk = (ePlayerState == STATE_TYPE::BACK_IDLE ||
		ePlayerState == STATE_TYPE::FRONT_IDLE) ? true : false;

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
					Set_ReadyTalk(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"), true);

					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith")));
					*_IsAble = true;
				}

				// 대화 후 다음 단계
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"))->Get_IsCol()
					&& m_bReadyTalk)
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 400, OBJ_ID::NPC_BLACKSMITH))
					{
						Set_ReadyTalk(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"), false);

						multimap<const _tchar*, CGameObject*> tempMap
							= CManagement::GetInstance()->
							Get_CurScene()->
							Get_Layer(OBJ_TYPE::MONSTER)->Get_ObjectMap();

						for (auto iter = tempMap.begin(); iter != tempMap.end(); ++iter)
						{
							if(iter->second->Get_Name() == L"Monster_Fish")
								m_iMonsterCount += 1;

							if (iter->second->Get_Name() == L"Monster_Serpent")
								m_iMonsterCount += 1;
						}

						m_iLevel += 1;
						*_IsAble = false;
						m_bShowQuestView = true;
						break;
					}
				}
			}
		}
		break;
	case 1: // 해상 전투
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// 해상 몹 소탕 여부 검사
			for (_int i = 0; i < CEventMgr::GetInstance()->Get_VecDeleteObj().size(); ++i)
			{
				if (CEventMgr::GetInstance()->Get_VecDeleteObj()[i]->Get_Name() == L"Monster_Fish")
				{
					m_iMonsterCount -= 1;
				}
				if (CEventMgr::GetInstance()->Get_VecDeleteObj()[i]->Get_Name() == L"Monster_Serpent")
				{
					m_iMonsterCount -= 1;
				}
			}
			// 모든 해상몹들을 잡았다면
			if (m_iMonsterCount <= 0)
			{
				m_tQuestContent[0].m_bClear = true;
				m_tQuestContent.push_back({ L"2. 죽음의 섬에 있는 정찰냥 만나기", false });
				m_tQuestContent[0].m_strQuestContent = L"1.바다 위 모든 몬스터 소탕\n완료";
				m_iLevel += 1;
				*_IsAble = false;
				break;
			}
			else
			{
				m_tQuestContent[0].m_strQuestContent = L"1.바다 위 모든 몬스터 소탕\n" 
					+ to_wstring(m_iMonsterCount) + L"마리 생존";

				//m_strQuestContent = L"남은 해상 몬스터 수 : " + to_wstring(m_iMonsterCount);
			}
		}
		break;
	case 2: // 보스전 돌입 전 NPC 대화
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc가 존재 한다면
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen1") != nullptr))
			{
				if (!*_IsAble)
				{
					Set_ReadyTalk(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen1"), true);

					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen1")));
					*_IsAble = true;
				}

				// 대화 후 다음 단계
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen1"))->Get_IsCol()
					&& m_bReadyTalk)
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 410, OBJ_ID::NPC_CITIZEN_1))
					{
						Set_ReadyTalk(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen1"), false);

						m_tQuestContent[1].m_bClear = true;
						m_tQuestContent.push_back({ L"3.드래곤 처치", false });

						// 배경 검은색
						m_pShadeUI = CShadeUI::Create(pGraphicDev);
						NULL_CHECK_RETURN(m_pShadeUI, E_FAIL);
						CEventMgr::GetInstance()->Add_Obj(L"ShadeUI", m_pShadeUI);

						// 무기 획득
						m_pWeaponGetUI = CWeaponGetEffect::Create(pGraphicDev, m_vItemList[0]);
						NULL_CHECK_RETURN(m_pWeaponGetUI, E_FAIL);
						CEventMgr::GetInstance()->Add_Obj(L"pWeaponGetUI", m_pWeaponGetUI);
					}
				}
				if (m_bReadyNext)
				{
					dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Item(
						m_vItemList[0]);
					m_iLevel += 1;
					*_IsAble = false;
					m_bStartQuest = true;
					m_bReadyNext = false;
				}
				break;
			}
		}
		break;
	case 3: // 보스전
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
				m_tQuestContent[2].m_bClear = true;
				m_iLevel += 1;
				*_IsAble = false;
				break;
			}
		}

		break;
	case 4: 
		m_iLevel = 99;
		*_IsAble = false;
		// return true;
		break;
	}

	return false;
}
