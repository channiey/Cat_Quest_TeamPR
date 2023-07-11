#pragma once

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class CGameObject;

END

class CImGuiMgr : public CBase
{
	DECLARE_SINGLETON(CImGuiMgr)

private:
	explicit CImGuiMgr();
	virtual ~CImGuiMgr();


public: /* MainApp에서 돌아가야 할 기본적인 함수들 */
	HRESULT						ImGui_SetUp(LPDIRECT3DDEVICE9 pGraphicDev);
	void						ImGui_Update();
	void						ImGui_Render();

public:


private:
	LPDIRECT3DDEVICE9			m_pGraphicDev;
	

private:
	virtual void				Free();
};


