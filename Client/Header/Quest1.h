#pragma once
#include "QuestData.h"

class CQuest1 : public CQuestData
{
public:
	explicit CQuest1(wstring _QuestName, LPDIRECT3DDEVICE9 m_pGraphicDev);
	virtual ~CQuest1();

public:
	virtual void  Init(LPDIRECT3DDEVICE9 m_pGraphicDev)   override;
	virtual _bool Update(LPDIRECT3DDEVICE9 pGraphicDev) override;

private:
	_int			m_iKillCount;

};

