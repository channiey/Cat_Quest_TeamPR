#pragma once
#include "GameObject.h"
#include "QuestData.h"

BEGIN(Engine)

class CQuestMgr : public CBase
{
	DECLARE_SINGLETON(CQuestMgr)
private:
	explicit CQuestMgr();
	virtual ~CQuestMgr();

public:
	void	Init(LPDIRECT3DDEVICE9 m_pGraphicDev);
	void	Update(LPDIRECT3DDEVICE9 pGraphicDev);

public:
	_bool	CheckQuest(_int _iQuestID, _int _iLevelID);
	void	NextLevel();

private:
	_int				   m_iQuestID; // 현재 진행중인 퀘스트 ID
	map<_int, CQuestData*> m_mapQuestList; // 모든 퀘스트 담기

private:
	virtual void			Free();
};

END

