#include "Quest.h"
#include "Export_Function.h"
CQuest::CQuest()
	: m_pPlayer(nullptr)
	, m_pMonster(nullptr)
	, m_pRewardItem(nullptr)
	, m_iKillCount(0)
	, m_iNpcID(0)
	, m_bAdd(false)
	, m_eProgress(QUEST_PROGRESS::QUEST_NONE)
{
}
CQuest::~CQuest()
{
}

void CQuest::Npc_NextPoint()
{
	m_iNpcID += 1;
}

