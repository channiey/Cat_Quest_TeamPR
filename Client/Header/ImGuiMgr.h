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
	void						Set_UnActive_Origin(); // 초기 프리팹 모두 비활성화 상태로 전환

	HRESULT						Clone_Object(const _vec3 _vPickPos); // 좌 클릭 오브젝트 클론
	HRESULT						Delete_Object(const _vec3 _vPickPos); // 우 클릭 오브젝트 삭제

	HRESULT						Save() { return S_OK; }; // 기존 오리진은 날려야 하는데 벡터 하나 잡아둘까?
	HRESULT						Load() { return S_OK; };

private:
	LPDIRECT3DTEXTURE9			LoadImageFile(const char* filePath); 
	string						wstring_to_utf8(const std::wstring& str); 
	const _vec3&				Get_ClickPos();

private:
	LPDIRECT3DDEVICE9			m_pGraphicDev;
	
private:
	virtual void				Free();
};


