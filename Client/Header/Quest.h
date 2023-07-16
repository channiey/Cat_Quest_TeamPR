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
	// 현재 단계 확인 및 세팅
	void				 Set_Progress(QUEST_PROGRESS _level) { m_eProgress = _level; }
	QUEST_PROGRESS		 Get_Progress()						 { return m_eProgress; }
	// 플레이어 세팅
	void				 Set_Player(CGameObject* _pPlayer) { m_pPlayer = _pPlayer; }
	// 다음 npc를 가리키도록 변경
	void				 Npc_NextPoint();
protected:
	vector<CGameObject*> m_vecNpc; // 관련 NPC
	CGameObject*		 m_pPlayer; // 플레이어
	_int				 m_iNpcID; // 퀘스트 진행을 위한 NPC 순서

	CGameObject*		 m_pMonster; // 토벌 대상			 // 나중에 필요한 애들만 추가
	_int				 m_iKillCount; // 잡아야 할 몬스터 수 //  나중에 필요한 애들만 추가

	CGameObject*		 m_pRewardItem; // 보상 아이템
	_int				 m_iRewardGold; // 보상 골드

	QUEST_PROGRESS		 m_eProgress; // 진행 단계
	vector<_tchar*>		 m_vecTalk; // 대사 모음

	_bool				 m_bAdd; // npc 모두 생성된 후 엔터단계에서 한번만 추가.
};
