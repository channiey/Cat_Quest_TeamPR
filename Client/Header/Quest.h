#pragma once
#include "GameObject.h"

BEGIN(Engine)

END
class CQuest : public CBase
{
public:
	explicit CQuest(LPDIRECT3DDEVICE9 pGraphicDev);
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
	// 다음 단계 준비 여부
	void				 Set_ReadyNext(_bool _isNext) { m_bReadyNext = true; }
	void				 Set_NextLevel() { m_iLevel += 1; }
protected:
	vector<CGameObject*> m_vecNpc; // 관련 NPC
	CGameObject*		 m_pPlayer; // 플레이어
	_bool				 m_bReadyNext; // 다음 단계로 진행 가능여부
	_int				 m_iLevel; // 현재 단계

	CGameObject*		 m_pMonster; // 토벌 대상			 // 나중에 필요한 애들만 추가
	_int				 m_iKillCount; // 잡아야 할 몬스터 수 //  나중에 필요한 애들만 추가

	CGameObject*		 m_pRewardItem; // 보상 아이템
	_int				 m_iRewardGold; // 보상 골드

	QUEST_PROGRESS		 m_eProgress; // 진행 단계
	vector<_tchar*>		 m_vecTalk; // 대사 모음

	_bool				 m_bAdd; // npc 모두 생성된 후 엔터단계에서 한번만 추가.


	LPDIRECT3DDEVICE9	 m_pGraphicDev;
};
