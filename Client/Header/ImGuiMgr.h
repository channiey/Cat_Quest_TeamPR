#pragma once

#include "Engine_Define.h"
#include "Base.h"

#pragma region Global

enum class				IMG_OBJ_TYPE { TERRAIN, ENVIRONMENT, MONSTER, NPC, ITEM, LINE, TYPEEND };

static const char*		arr_ImgObjType[(UINT)IMG_OBJ_TYPE::TYPEEND] = { "Trrain", "Environment", "Monster", "Npc", "Item", "Line" };

static _bool			bInit = false;

static const int		g_iImagPerRow = 4;

#pragma endregion


BEGIN(Engine)
END

class CImGuiMgr : public CBase
{
	DECLARE_SINGLETON(CImGuiMgr)

private:
	explicit CImGuiMgr();
	virtual ~CImGuiMgr();


public: 
	HRESULT						ImGui_SetUp(LPDIRECT3DDEVICE9 pGraphicDev);
	void						ImGui_Update();
	void						ImGui_Render();

private:
	void						Show_Header_Scene();
	void						Show_Header_Object();
	void						Show_Header_Light();

	HRESULT						Set_ImgPath(); // 맵 및 오브젝트 이미지 경로 셋업

private:
	LPDIRECT3DTEXTURE9			LoadImageFile(const char* filePath); 
	string						wstring_to_utf8(const std::wstring& str); 

private:
	LPDIRECT3DDEVICE9			m_pGraphicDev;
	
private:
	virtual void				Free();
};


