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
	// 퀘스트에 플레이어 설정
	void	 Set_Player(CGameObject* _pPlayer) { 
		m_pPlayer = _pPlayer;
		m_pQuest->Set_Player(_pPlayer);
	}
	CQuest*	 Set_HaveQuest(const _tchar* _name); // npc에게 퀘스트 할당.
	void	 Set_Quest(CQuest* _pQuest); // 처음 퀘스트 진입 시 최초 npc가 가지고 있는 퀘스트 세팅
	_bool    Get_Active() { return m_bActive; } // 현제 퀘스트를 진행 중인지 확인
	void     Set_Active(_bool _isActive) { m_bActive = _isActive; } // 퀘스트 활성 여부 설정.

	void	 Set_ReadyNext(_bool _isNext); // 다음 퀘스트 가리키도록
	void	 Set_NextLevel(); // 다음 레벨

private:
	map<const _tchar*, CQuest*> m_mapQuest;
	CGameObject*				m_pPlayer;
	CQuest*						m_pQuest;
	_bool						m_bActive;
private:
	virtual void			Free();
};

END
