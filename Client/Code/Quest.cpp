#include "Quest.h"

CQuest::CQuest()
	: m_pPlayer(nullptr)
	, m_pMonster(nullptr)
	, m_pRewardItem(nullptr)
	, m_iKillCount(0)
	, m_eLevel(QUEST_LEVEL::QUEST_NONE)
{
}
CQuest::~CQuest()
{
}
