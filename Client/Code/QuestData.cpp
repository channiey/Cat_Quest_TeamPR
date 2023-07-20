#include "stdafx.h"
#include "QuestData.h"

#include "IndicatorUI.h"

#include "Export_Function.h"

CQuestData::CQuestData() 
	: m_iLevel(0)
	, m_strQuestName(L"")
	, m_pPlayer(nullptr)
{
}

CQuestData::~CQuestData()
{
	Free();
}

void CQuestData::Free()
{
}
