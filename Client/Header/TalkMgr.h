#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CTalkMgr : public CBase
{
	DECLARE_SINGLETON(CTalkMgr)
private:
	explicit CTalkMgr();
	virtual ~CTalkMgr();

public:
	void	Init();

public:
	void Get_Talk(LPDIRECT3DDEVICE9 pGraphicDev, TALK_ID _eTalkID, OBJ_ID _eObjID);

private:
	map<TALK_ID, vector<wstring>> m_mapTalkData;
	_int						  m_iTalkIndex;

private:
	virtual void			Free();
};

END

