#include "stdafx.h"
#include "QuestMgr.h"

#include "Export_Function.h"

#include "EventMgr.h"
#include "IndicatorUI.h"

#include "Quest1.h"
#include "Quest2.h"
#include "Quest3.h"
#include "Quest4.h"

IMPLEMENT_SINGLETON(CQuestMgr)

CQuestMgr::CQuestMgr()
	: m_iQuestID(10)
{
}

CQuestMgr::~CQuestMgr()
{
	Free();
}

HRESULT CQuestMgr::Init(LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
{
	m_mapQuestList.insert(make_pair(10, new CQuest1(L"대장장이의 부탁", m_pGraphicDev, _pPlayer)));
	m_mapQuestList.insert(make_pair(20, new CQuest2(L"던전 정리", m_pGraphicDev, _pPlayer)));
	m_mapQuestList.insert(make_pair(30, new CQuest3(L"드래곤에게 향하기 위해", m_pGraphicDev, _pPlayer)));
	m_mapQuestList.insert(make_pair(40, new CQuest4(L"죽음의 섬으로", m_pGraphicDev, _pPlayer)));


	m_iQuestID = 40;

	m_bInit = true;

	m_pIndicator = CIndicatorUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(m_pIndicator, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"UI_Indicator", m_pIndicator);
	m_pIndicator->Set_Maintain(true);

	m_bIsAble = false;

	return S_OK;
}

void CQuestMgr::Update(LPDIRECT3DDEVICE9 pGraphicDev)
{
	if (m_mapQuestList[m_iQuestID]->Update(pGraphicDev, m_pIndicator, &m_bIsAble))
	{
		m_iQuestID += 10;
	}
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
