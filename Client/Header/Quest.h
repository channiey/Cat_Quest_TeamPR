#pragma once
#include "GameObject.h"

class CQuest : public CBase
{
public:
	explicit CQuest();
	virtual ~CQuest();

public:
	virtual void Init()		= 0;
	virtual void Enter()	= 0;
	virtual void Update()	= 0;
	virtual void Exit()		= 0;

public:
	//void  Set_Active(_bool _isActive) { m_bActive = _isActive; }
	//_bool Get_Active()				  { return m_bActive; }

	void		Set_Level(QUEST_LEVEL _level) { m_eLevel = _level; }
	QUEST_LEVEL Get_Level()					  { return m_eLevel; }
protected:
	vector<CGameObject*> m_vecNpc; // 관련 NPC
	CGameObject*		 m_pPlayer; // 플레이어

	CGameObject*		 m_pMonster; // 토벌 대상
	_int				 m_iKillCount; // 잡아야 할 몬스터 수

	CGameObject*		 m_pRewardItem; // 보상 아이템
	_int				 m_iRewardGold; // 보상 골드

	QUEST_LEVEL			 m_eLevel; // 진행 단계
	vector<_tchar*>		 m_vecTalk; // 대사 모음
};

