#include "Quest.h"
#include "Export_Function.h"
#include "Npc.h"
CQuest::CQuest(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pPlayer(nullptr)
	, m_pMonster(nullptr)
	, m_pRewardItem(nullptr)
	, m_iKillCount(0)
	, m_iLevel(0)
	, m_bReadyNext(false)
	, m_bAdd(false)
	, m_eProgress(QUEST_PROGRESS::QUEST_NONE)
{
	m_pGraphicDev = pGraphicDev;
}
CQuest::~CQuest()
{
}

