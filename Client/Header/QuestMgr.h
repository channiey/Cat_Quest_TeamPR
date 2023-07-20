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
	_bool	Get_IsAble() { return m_bIsAble; }
	void 	Set_IsAble(_bool _IsAble) { m_bIsAble = _IsAble; }
	void	NextLevel();

private:
	_int				   m_iQuestID; // 현재 진행중인 퀘스트 ID
	map<_int, CQuestData*> m_mapQuestList; // 모든 퀘스트 담기

	_bool				   m_bInit = false;
	_bool				   m_bIsAble;

	CGameObject*		   m_pIndicator;
private:
	virtual void			Free();
};

END

