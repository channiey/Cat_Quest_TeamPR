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
	_int				   m_iQuestID; // ���� �������� ����Ʈ ID
	map<_int, CQuestData*> m_mapQuestList; // ��� ����Ʈ ���

private:
	virtual void			Free();
};

END

