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
	void	 Init(LPDIRECT3DDEVICE9 pGraphicDev);
	void     Play_Quest();
	void	 Enter();
	void	 Update();
	void	 Exit();

public:
	// ����Ʈ�� �÷��̾� ����
	void	 Set_Player(CGameObject* _pPlayer) { 
		m_pPlayer = _pPlayer;
		m_pQuest->Set_Player(_pPlayer);
	}
	CQuest*	 Set_HaveQuest(const _tchar* _name); // npc���� ����Ʈ �Ҵ�.
	void	 Set_Quest(CQuest* _pQuest); // ó�� ����Ʈ ���� �� ���� npc�� ������ �ִ� ����Ʈ ����
	_bool    Get_Active() { return m_bActive; } // ���� ����Ʈ�� ���� ������ Ȯ��
	void     Set_Active(_bool _isActive) { m_bActive = _isActive; } // ����Ʈ Ȱ�� ���� ����.

	void	 Set_ReadyNext(_bool _isNext); // ���� ����Ʈ ����Ű����
	void	 Set_NextLevel(); // ���� ����

private:
	map<const _tchar*, CQuest*> m_mapQuest;
	CGameObject*				m_pPlayer;
	CQuest*						m_pQuest;
	_bool						m_bActive;
private:
	virtual void			Free();
};

END
