#include "stdafx.h"
#include "Quest1.h"

#include "Export_Function.h"

#include "TalkMgr.h"
#include "Management.h"

#include "Npc_King.h"
#include "Npc_Mage.h"
#include "Npc_BlackSmith.h"

CQuest1::CQuest1(wstring _QuestName)
{
	m_strQuestName = _QuestName;
	Init();
}

CQuest1::~CQuest1()
{
}

void CQuest1::Init()
{
	m_iKillCount = 0;
}

_bool CQuest1::Update(LPDIRECT3DDEVICE9 pGraphicDev)
{
	switch (m_iLevel)
	{
	case 0:
		// 사자왕에게 말 걸기
		if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
			Get_GameObject(OBJ_TYPE::NPC, L"Npc_King"))->Get_IsCol())
		{
			if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 10, OBJ_ID::NPC_KING))
				m_iLevel += 1;
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
					m_iLevel += 1;
			}
		}
		break;
	case 2:
		// 대장장이 찾아가기
		if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
			Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"))->Get_IsCol())
		{
			if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 30, OBJ_ID::NPC_BLACKSMITH))
				m_iLevel += 1;
		}
		break;
	case 3:
		// 마법사 찾아가기
		if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
			Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage"))->Get_IsCol())
		{
			if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 20, OBJ_ID::NPC_MAGE))
				m_iLevel += 1;
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
