#pragma once
#include "GameObject.h"
#include "QuestData.h"

BEGIN(Engine)

class CQuestMgr : public CBase
{
	DECLARE_SINGLETON(CQuestMgr)
private:
	explicit CQuestMgr();
	virtual ~CQuestMgr();

public:
	HRESULT	Init(LPDIRECT3DDEVICE9 m_pGraphicDev);
	void	Update(LPDIRECT3DDEVICE9 pGraphicDev);

public:
	_bool	CheckQuest(_int _iQuestID, _int _iLevelID);
	_bool	Get_IsInit() { return m_bInit; }
	void	NextLevel();

private:
	_int				   m_iQuestID; // ���� �������� ����Ʈ ID
	map<_int, CQuestData*> m_mapQuestList; // ��� ����Ʈ ���

	_bool				   m_bInit = false;

	CGameObject*		   m_pIndicator;
private:
	virtual void			Free();
};

END

