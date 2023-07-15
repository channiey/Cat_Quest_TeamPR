#pragma once
#include "Quest.h"
#include "GameObject.h"

BEGIN(Engine)

class CQuestMgr : public CBase
{
	DECLARE_SINGLETON(CQuestMgr)

private:
	explicit CQuestMgr();
	virtual ~CQuestMgr();

public:
	void	 Init();
	void     Play_Quest();
	void	 Enter();
	void	 Update();
	void	 Exit();

public:
	void	 Set_Player(CGameObject* _pPlayer) { m_pPlayer = _pPlayer; }
	CQuest*	 Set_HaveQuest(const _tchar* _name);
	void	 Set_Quest(CQuest* _pQuest);
	_bool    Get_Active() { return m_bActive; }
	void     Set_Active(_bool _isActive) { m_bActive = _isActive; }


private:
	map<const _tchar*, CQuest*> m_mapQuest;
	CGameObject*				m_pPlayer;
	CQuest*						m_pQuest;
	_bool						m_bActive;
private:
	virtual void			Free();
};

END
