#pragma once

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class CLayer;
END

class CImGuiMgr : public CBase
{
	DECLARE_SINGLETON(CImGuiMgr)

private:
	explicit CImGuiMgr();
	virtual ~CImGuiMgr();


public: 
	HRESULT						ImGui_SetUp(LPDIRECT3DDEVICE9 pGraphicDev); // 이벤트 매니저 생성 전
	void						ImGui_Update();
	void						ImGui_Render();

private:
	void						Show_Header_Scene();
	void						Show_Header_Object();
	void						Show_Header_Light();

private:
	HRESULT						Set_ImgPath(); // 맵 및 오브젝트 이미지 경로 셋업

	HRESULT						Clone_Object(const _vec3 _vClonePos); // 피킹시 오브젝트 클론


private:
	LPDIRECT3DTEXTURE9			LoadImageFile(const char* filePath); 
	string						wstring_to_utf8(const std::wstring& str); 
	const _vec3&				Get_ClickPos();

private:
	LPDIRECT3DDEVICE9			m_pGraphicDev;
	
private:
	virtual void				Free();
};


