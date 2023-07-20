#pragma once
#include "QuestData.h"

class CQuest2 : public CQuestData
{
public:
	explicit CQuest2(wstring _QuestName, LPDIRECT3DDEVICE9 m_pGraphicDev);
	virtual ~CQuest2();

public:
	virtual void  Init(LPDIRECT3DDEVICE9 m_pGraphicDev)   override;
	virtual _bool Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator) override;

private:
	_int			m_iKillCount;
	_bool			m_bCreateKey;
	CGameObject*	m_pKey;
};

