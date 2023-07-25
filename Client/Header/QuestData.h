#pragma once
#include "GameObject.h"
#include "Skill.h"

BEGIN(Engine)

END

enum NPC_NAME
{
	KING, MAGE, SMITH, SOLDIER, CITIZEN1, CITIZEN2
};

class CQuestData : public CBase
{
public:
	explicit CQuestData();
	virtual ~CQuestData();

public:
	virtual void  Init(LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)   = 0;
	virtual _bool Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble) = 0;

public:
	virtual _int Get_Level() { return m_iLevel; }
	virtual void Next_Level() { m_iLevel += 1; }

	virtual wstring Get_QuestName() { return m_strQuestName; }
	virtual wstring Get_QuestContent() { return m_strQuestContent; }
protected:
	wstring					m_strQuestName; // 퀘스트 이름
	wstring					m_strQuestContent; // 퀘스트 내용
	vector<CGameObject*>	m_vNpcList;		// 관련 Npc를 담을 배열
	vector<CGameObject*>	m_vItemList;	// 보상 아이템을 담을 배열
	vector<CSkill*>			m_vSkillList;	// 보상 스킬을 담을 배열
	_int					m_iLevel;		// 퀘스트 단계
	CGameObject*			m_pPlayer;      // 플레이어
	

private:
	virtual void			Free();
};

