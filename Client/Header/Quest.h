#pragma once
#include "GameObject.h"

BEGIN(Engine)

END
class CQuest : public CBase
{
public:
	explicit CQuest();
	virtual ~CQuest();

public:
	virtual void Init() {};
	virtual void Enter() {};
	virtual void Update() {};
	virtual void Exit() {};

public:
	// ���� �ܰ� Ȯ�� �� ����
	void				 Set_Progress(QUEST_PROGRESS _level) { m_eProgress = _level; }
	QUEST_PROGRESS		 Get_Progress()						 { return m_eProgress; }
	// �÷��̾� ����
	void				 Set_Player(CGameObject* _pPlayer) { m_pPlayer = _pPlayer; }
	// ���� npc�� ����Ű���� ����
	void				 Npc_NextPoint();
protected:
	vector<CGameObject*> m_vecNpc; // ���� NPC
	CGameObject*		 m_pPlayer; // �÷��̾�
	_int				 m_iNpcID; // ����Ʈ ������ ���� NPC ����

	CGameObject*		 m_pMonster; // ��� ���			 // ���߿� �ʿ��� �ֵ鸸 �߰�
	_int				 m_iKillCount; // ��ƾ� �� ���� �� //  ���߿� �ʿ��� �ֵ鸸 �߰�

	CGameObject*		 m_pRewardItem; // ���� ������
	_int				 m_iRewardGold; // ���� ���

	QUEST_PROGRESS		 m_eProgress; // ���� �ܰ�
	vector<_tchar*>		 m_vecTalk; // ��� ����

	_bool				 m_bAdd; // npc ��� ������ �� ���ʹܰ迡�� �ѹ��� �߰�.
};
