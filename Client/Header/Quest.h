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
	vector<CGameObject*> m_vecNpc; // ���� NPC
	CGameObject*		 m_pPlayer; // �÷��̾�

	CGameObject*		 m_pMonster; // ��� ���
	_int				 m_iKillCount; // ��ƾ� �� ���� ��

	CGameObject*		 m_pRewardItem; // ���� ������
	_int				 m_iRewardGold; // ���� ���

	QUEST_LEVEL			 m_eLevel; // ���� �ܰ�
	vector<_tchar*>		 m_vecTalk; // ��� ����
};

