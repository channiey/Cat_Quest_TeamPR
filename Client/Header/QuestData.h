#pragma once
#include "GameObject.h"

BEGIN(Engine)

END

class CQuestData : public CBase
{
public:
	explicit CQuestData();
	virtual ~CQuestData();

public:
	virtual void  Init()   = 0;
	virtual _bool Update(LPDIRECT3DDEVICE9 pGraphicDev) = 0;

public:
	virtual _int Get_Level() { return m_iLevel; }
	virtual void Next_Level() { m_iLevel += 1; }
protected:
	wstring				m_strQuestName; // 퀘스트 이름
	vector<OBJ_ID>		m_vNpcList;		// 관련 Npc를 담을 배열
	_int				m_iLevel;
	
private:
	virtual void			Free();
};

