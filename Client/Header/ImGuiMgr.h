#pragma once

#include "Engine_Define.h"
#include "Base.h"

class CImGuiMgr : public CBase
{
	DECLARE_SINGLETON(CImGuiMgr)

private:
	explicit CImGuiMgr();
	virtual ~CImGuiMgr();


public: /* MainApp���� ���ư��� �� �⺻���� �Լ��� */
	HRESULT						ImGui_SetUp(LPDIRECT3DDEVICE9 pGraphicDev);
	void						ImGui_Update();
	void						ImGui_Render();

private:
	virtual void				Free();
};

