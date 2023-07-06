#pragma once

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CEventMgr : public CBase
{
	DECLARE_SINGLETON(CEventMgr)

public:
	explicit CEventMgr();
	virtual ~CEventMgr();

public:
	void					Update_Event();

public:
	HRESULT					Add_Obj(CGameObject* const _pObj);
	HRESULT					Delete_Obj(CGameObject* const _pObj);
	HRESULT					Return_Obj(CGameObject* const _pObj);
	HRESULT					Change_Scene(const SCENE_TYPE& _eSceneType);

private:
	HRESULT					Add_Event(const EVENT& _event);
	HRESULT					Execute_Event(const EVENT& _event);

private:
	vector<EVENT>			m_vecEvent;
	vector<CGameObject*>	m_vecDeleteObj;
	vector<CGameObject*>	m_vecReturnObj;

private:
	virtual void			Free();
};

END
