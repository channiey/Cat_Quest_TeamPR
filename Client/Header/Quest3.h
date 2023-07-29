#pragma once
#include "QuestData.h"

class CQuest3 : public CQuestData
{
public:
	explicit CQuest3(wstring _QuestName, LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer);
	virtual ~CQuest3();

public:
	virtual void  Init(LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)   override;
	virtual _bool Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble) override;

private:
	_bool			m_bCreateQItem;
	CGameObject*	m_pWorldFlight;
};

