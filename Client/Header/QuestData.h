#pragma once
#include "GameObject.h"
#include "Skill.h"

BEGIN(Engine)

END

enum NPC_NAME
{
	KING, MAGE, SMITH, SOLDIER, CITIZEN1, CITIZEN2
};

struct tagQuestContent
{
	wstring					m_strQuestContent; // 퀘스트 내용
	_bool					m_bClear; // 클리어 여부
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
	virtual wstring					Get_QuestName()	   { return m_strQuestName; }
	virtual vector<tagQuestContent> Get_QuestContent() { return m_tQuestContent; }
	virtual _bool					Get_ShowQuestView() { return m_bShowQuestView; }
protected:
	wstring					m_strQuestName; // 퀘스트 이름
	vector<tagQuestContent> m_tQuestContent; // 퀘스트 내용
	vector<CGameObject*>	m_vNpcList;		// 관련 Npc를 담을 배열
	vector<CGameObject*>	m_vItemList;	// 보상 아이템을 담을 배열
	vector<CSkill*>			m_vSkillList;	// 보상 스킬을 담을 배열
	_int					m_iLevel;		// 퀘스트 단계
	CGameObject*			m_pPlayer;      // 플레이어

	_bool					m_bShowQuestView; // 퀘스트 내용을 띄우고 싶을때만

private:
	virtual void			Free();
};

