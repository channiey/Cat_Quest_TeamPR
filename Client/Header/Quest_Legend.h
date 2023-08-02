#pragma once
#include "QuestData.h"

class CQuest_Legend : public CQuestData
{
public:
	explicit CQuest_Legend(wstring _QuestName, LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer);
	virtual ~CQuest_Legend();

public:
	virtual void  Init(LPDIRECT3DDEVICE9 _pGraphicDev, CGameObject* _pPlayer)   override;
	virtual _bool Update(LPDIRECT3DDEVICE9 _pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble) override;

private:
};

