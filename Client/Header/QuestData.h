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
	wstring					m_strQuestName; // ����Ʈ �̸�
	wstring					m_strQuestContent; // ����Ʈ ����
	vector<CGameObject*>	m_vNpcList;		// ���� Npc�� ���� �迭
	vector<CGameObject*>	m_vItemList;	// ���� �������� ���� �迭
	vector<CSkill*>			m_vSkillList;	// ���� ��ų�� ���� �迭
	_int					m_iLevel;		// ����Ʈ �ܰ�
	CGameObject*			m_pPlayer;      // �÷��̾�
	

private:
	virtual void			Free();
};

