#pragma once

#include "Base.h"
#include "Engine_Define.h"

class CLoadingThread : public CBase
{
public:
	CLoadingThread(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLoadingThread();

public:
	LOADING_THREAD_TYPE			Get_LoadingID() { return m_eID; }
	CRITICAL_SECTION*			Get_Crt()		{ return &m_Crt; }
	_bool						Get_Finish()	{ return m_bFinish; }

public:
	static unsigned	int	CALLBACK Thread_Main(void* pArg);

public:
	HRESULT						Ready_Loading(LOADING_THREAD_TYPE eLoadingID);
	_uint						Loading_For_World();
	_uint						Loading_For_Tool();
	_uint						Loading_For_Boss();

private:
	HANDLE						m_hThread;
	CRITICAL_SECTION			m_Crt;
	LOADING_THREAD_TYPE			m_eID;

	LPDIRECT3DDEVICE9			m_pGraphicDev;
	_bool						m_bFinish;

public:
	static	CLoadingThread*		Create(LPDIRECT3DDEVICE9 pGraphicDev, LOADING_THREAD_TYPE eID);

private:
	virtual void				Free();
};

