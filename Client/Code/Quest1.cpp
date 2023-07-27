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

#include "SkillGetEffect.h"
#include "ShadeUI.h"

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
	CEventMgr::GetInstance()->Add_Obj(L"갸르릉 플레임", pSkill);
	m_vSkillList.push_back(pSkill);
	pSkill->Set_Maintain(true);

	m_tQuestContent.push_back({ L"1. 고슴도치 5마리 처치", false });

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
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 100, OBJ_ID::NPC_BLACKSMITH)) 
					{
						m_iLevel += 1;
						*_IsAble = false;
						break;
					}
				}

			}
		}
		break;

	case 1: // 고슴도치 5마리 소탕
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			m_bShowQuestView = true;
			// 고슴도치 5마리를 잡았다면
			for (_int i = 0; i < CEventMgr::GetInstance()->Get_VecDeleteObj().size(); ++i)
			{
				if (CEventMgr::GetInstance()->Get_VecDeleteObj()[i]->Get_Name() == L"Monster_Hedgehog")
				{
					m_iKillCount += 1;
				}
			}
			if (m_iKillCount <= 5)
			{
				m_tQuestContent[0].m_strQuestContent = L"1.고슴도치 5마리 처치  \n" + to_wstring(m_iKillCount) + L" / 5";
			}
			if (m_iKillCount >= 5)
			{
				{
					m_tQuestContent[0].m_strQuestContent = L"1. 고슴도치 5마리 처치  \n완료";
					m_tQuestContent[0].m_bClear = true;
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
								// 배경 검은색
								CShadeUI* pShadeUI = CShadeUI::Create(pGraphicDev);
								NULL_CHECK_RETURN(pShadeUI, E_FAIL);
								CEventMgr::GetInstance()->Add_Obj(L"ShadeUI", pShadeUI);

								// 스킬 획득 연출
								m_pSkillGetUI = CSkillGetEffect::Create(pGraphicDev, m_vSkillList[0]);
								NULL_CHECK_RETURN(m_pSkillGetUI, E_FAIL);
								CEventMgr::GetInstance()->Add_Obj(L"pSkillGetUI", m_pSkillGetUI);							
							}
						}
					}
					if (m_bReadyNext)
					{
						// 실제 스킬 인벤토리에 추가.
						dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Skill(
							m_vSkillList[0]);
						m_bStartQuest = true;
						m_bReadyNext = false;
						m_iLevel += 1;
					}
					break;
				}
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
