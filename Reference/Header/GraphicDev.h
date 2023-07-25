#pragma once

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CGraphicDev : public CBase
{
	DECLARE_SINGLETON(CGraphicDev)

private:
	explicit CGraphicDev();
	virtual ~CGraphicDev();

public:
	LPDIRECT3DDEVICE9		Get_GraphicDev() { return m_pGraphicDev; }
	LPD3DXFONT				Get_Font(void) { return m_pFont; }
	LPD3DXFONT				Get_TitleFont(void) { return m_pTitleFont; }
	LPD3DXFONT				Get_InGameFont(void) { return m_pInGameFont; }
	LPD3DXFONT				Get_LevelFont(void) { return m_pLevelFont; }
	LPD3DXFONT				Get_SkillFont(void) { return m_pSkillFont; }
	LPD3DXFONT				Get_EffectFont(void) { return m_pEffectFont; }

public:

public:
	HRESULT					Ready_GraphicDev(HWND hWnd, WINMODE eMode, const _uint& iSizeX, const _uint& iSizeY, CGraphicDev** ppGraphicDev);
	void					Render_Begin(D3DXCOLOR Color);
	void					Render_End();

private:
	LPDIRECT3D9				m_pSDK;
	LPDIRECT3DDEVICE9		m_pGraphicDev;
	LPD3DXFONT				m_pFont;
	LPD3DXFONT				m_pTitleFont;
	LPD3DXFONT				m_pInGameFont;
	LPD3DXFONT				m_pLevelFont;
	LPD3DXFONT				m_pSkillFont;
	LPD3DXFONT				m_pEffectFont;


public:
	virtual void	Free();
};

END
