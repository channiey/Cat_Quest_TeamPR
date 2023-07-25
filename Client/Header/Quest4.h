#pragma once
#include "QuestData.h"

class CQuest4 : public CQuestData
{
public:
	explicit CQuest4(wstring _QuestName, LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer);
	virtual ~CQuest4();

public:
	virtual void  Init(LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)   override;
	virtual _bool Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble) override;

private:
	_int	m_iKillCount;
	_bool	m_bBossKill;

};

