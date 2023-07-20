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
	_bool	Get_Talk(LPDIRECT3DDEVICE9 pGraphicDev, _int _iTalkID, OBJ_ID _eObjID);
	_bool	Get_IsInit() { return m_bInit; }

private:
	map<int, vector<wstring>>	  m_mapTalkData;
	_int						  m_iTalkIndex;

	_bool						  m_bInit = false;

private:
	virtual void			Free();
};

END

