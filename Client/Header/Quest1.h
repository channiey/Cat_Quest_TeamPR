#pragma once
#include "QuestData.h"

class CQuest1 : public CQuestData
{
public:
	explicit CQuest1(wstring _QuestName);
	virtual ~CQuest1();

public:
	virtual void  Init()   override;
	virtual _bool Update(LPDIRECT3DDEVICE9 pGraphicDev) override;

private:
	_int			m_iKillCount;

};

