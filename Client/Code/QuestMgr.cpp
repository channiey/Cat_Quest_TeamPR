#include "stdafx.h"
#include "QuestMgr.h"

#include "Export_Function.h"

#include "EventMgr.h"

#include "Quest1.h"

IMPLEMENT_SINGLETON(CQuestMgr)

CQuestMgr::CQuestMgr()
{
}

CQuestMgr::~CQuestMgr()
{
	Free();
}

void CQuestMgr::Init(LPDIRECT3DDEVICE9 m_pGraphicDev)
{
	m_mapQuestList.insert(make_pair(10, new CQuest1(L"µàÅä¸®¾ó", m_pGraphicDev)));

	m_iQuestID = 10;
}

void CQuestMgr::Update(LPDIRECT3DDEVICE9 pGraphicDev)
{
	m_mapQuestList[m_iQuestID]->Update(pGraphicDev);
}

_bool CQuestMgr::CheckQuest(_int _iQuestID, _int _iLevelID)
{
	if (m_iQuestID == _iQuestID && m_mapQuestList[m_iQuestID]->Get_Level() == _iLevelID)
		return true;

	return false;
}

void CQuestMgr::NextLevel()
{
	auto iter = m_mapQuestList.find(m_iQuestID);

	if (&iter)
		iter->second->Next_Level();
}

void CQuestMgr::Free()
{
	for_each(m_mapQuestList.begin(), m_mapQuestList.end(), CDeleteMap());
	m_mapQuestList.clear();
}
