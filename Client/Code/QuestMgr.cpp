#include "QuestMgr.h"

#include "Quest1.h"
#include "Quest2.h"
#include "Quest3.h"
#include "Quest4.h"
#include "Quest5.h"
#include "Quest6.h"

IMPLEMENT_SINGLETON(CQuestMgr)

CQuestMgr::CQuestMgr() 
	: m_bActive(false)
	, m_pPlayer(nullptr)
	, m_pQuest(nullptr)
{
}

CQuestMgr::~CQuestMgr()
{
	Free();
}

void CQuestMgr::Init(LPDIRECT3DDEVICE9 pGraphicDev)
{
	m_mapQuest.insert({ L"ÈûÀÇ Áõ¸í1",	new CQuest1(pGraphicDev) });
	m_mapQuest.insert({ L"ÈûÀÇ Áõ¸í2",	new CQuest2(pGraphicDev) });
	m_mapQuest.insert({ L"µµµÏ Àâ±â" ,	new CQuest3(pGraphicDev) });
	m_mapQuest.insert({ L"µå¶óÄÚ½º"  ,	new CQuest4(pGraphicDev) });
	m_mapQuest.insert({ L"Á×À½ÀÇ ¼¶" ,	new CQuest5(pGraphicDev) });
	m_mapQuest.insert({ L"ÃÖÁ¾Àå"    ,	new CQuest6(pGraphicDev) });
}

void CQuestMgr::Play_Quest()
{
	if (m_pQuest->Get_Progress() == QUEST_PROGRESS::QUEST_CLEAR) 
		m_bActive = false;

	Enter();
	Update();
	Exit();
}

void CQuestMgr::Enter()
{
	if (m_pQuest) 
	{
		if (m_pQuest->Get_Progress() == QUEST_PROGRESS::QUEST_ENTER) 
			m_pQuest->Enter();
	}
}

void CQuestMgr::Update()
{
	if (m_pQuest)
	{
		if (m_pQuest->Get_Progress() == QUEST_PROGRESS::QUEST_UPDATE) 
			m_pQuest->Update();
	}
}

void CQuestMgr::Exit()
{
	if (m_pQuest) 
	{
		if (m_pQuest->Get_Progress() == QUEST_PROGRESS::QUEST_EXIT) 
			m_pQuest->Exit();
	}
}

CQuest* CQuestMgr::Set_HaveQuest(const _tchar* _name)
{
	auto iter = m_mapQuest.find(_name);

	if (&iter) 
		return iter->second;

	return nullptr;
}

void CQuestMgr::Set_Quest(CQuest* _pQuest)
{
	if (_pQuest) 
	{
		m_pQuest = _pQuest;
		m_pQuest->Set_Progress(QUEST_PROGRESS::QUEST_ENTER);
	}
}

void CQuestMgr::Set_ReadyNext(_bool _isNext)
{
	if (m_pQuest)
		m_pQuest->Set_ReadyNext(_isNext);
}

void CQuestMgr::Set_NextLevel()
{
	if (m_pQuest)
		m_pQuest->Set_NextLevel();
}

void CQuestMgr::Free()
{
	for_each(m_mapQuest.begin(), m_mapQuest.end(), CDeleteMap());
	m_mapQuest.clear();
}