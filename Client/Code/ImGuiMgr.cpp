#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx9.h"

#include "ImGuiMgr.h"

#include "stdafx.h"
#include "MainApp.h"
#include "InputDev.h"
#include "Calculator.h"

#include "Export_Function.h"
#include "TerrainTex.h"

#include <iostream>


#pragma region ImGui

vector<ImTextureID>			g_vecObjImgPath[(UINT)IMG_OBJ_TYPE::TYPEEND];

#pragma endregion


IMPLEMENT_SINGLETON(CImGuiMgr)

CImGuiMgr::CImGuiMgr()
	: m_pGraphicDev(nullptr)
{
}

CImGuiMgr::~CImGuiMgr()
{
	Free();
}

HRESULT CImGuiMgr::ImGui_SetUp(LPDIRECT3DDEVICE9 pGraphicDev)
{
	m_pGraphicDev = pGraphicDev;
	if (m_pGraphicDev)
		m_pGraphicDev->AddRef();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX9_Init(pGraphicDev);

	Set_ImgPath(); // 맵 및 오브젝트 이미지 경로 셋업

	return S_OK;
}

void CImGuiMgr::ImGui_Update()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Tool Tab");

	if (ImGui::CollapsingHeader("Scene"))
	{
		Show_Header_Scene();
	}
	if (ImGui::CollapsingHeader("Object"))
	{
		Show_Header_Object();
	}
	/*if (ImGui::CollapsingHeader("Light"))
	{
		Show_Header_Light();
	}*/

	ImGui::End();
}

void CImGuiMgr::ImGui_Render()
{
	// 이벤트 매니저 생성 전 임시 처방
	if (!bInit)
	{
		bInit = true;
		return;
	}
	ImGui::Render();

	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void CImGuiMgr::Show_Header_Scene()
{	
	// 01. Button (Action)
	ImGui::SeparatorText("Action Button");
	if (ImGui::Button("New"))
	{
	}
	ImGui::SameLine();
	if (ImGui::Button("Save"))
	{
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete"))
	{
	}

	// 02. List Box (Scene Image)
	ImGui::SeparatorText("Scene Prefab List");

	int			iCurIdxRow		= 0; // 줄 맞추기 위한 변수
	static int	iCurIdx_Scene	= 0; // 현재 선택된 인덱스

	wstring strImgPath = L"../Bin/Resource/Texture/Object/Bush/forest_5.png";
	ImTextureID image = LoadImageFile(wstring_to_utf8(strImgPath).c_str());


	if (ImGui::BeginListBox(" ", ImVec2(280.f, 180.f)))
	{
		for (int i = 0; i < 10; ++i)
		{
			if (ImGui::ImageButton(image, ImVec2(50.f, 50.f))) // 이미지 출력
			{
				iCurIdx_Scene = i;
			}

			if (iCurIdxRow < g_iImagPerRow - 1) // 정렬
			{
				ImGui::SameLine();
				iCurIdxRow++;
			}
			else
				iCurIdxRow = 0;
		}
		ImGui::EndListBox();
	}
}

void CImGuiMgr::Show_Header_Object()
{
	// 01. Combo (Object Type)
	ImGui::SeparatorText("Object Type");
	static int iCurIdx_Object_Type = 0; // 현재 선택된 인덱스
	static ImGuiComboFlags flags = 0;

	const char* combo_preview_value = arr_ImgObjType[iCurIdx_Object_Type];

	if (ImGui::BeginCombo("  ", combo_preview_value, flags))
	{
		for (int n = 0; n < IM_ARRAYSIZE(arr_ImgObjType); n++)
		{
			const bool is_selected = (iCurIdx_Object_Type == n);
			if (ImGui::Selectable(arr_ImgObjType[n], is_selected))
				iCurIdx_Object_Type = n;

			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	// 02. List Box (Object Image)
	int			iCurIdxRow		= 0; // 줄 맞추기 위한 변수
	static int	iCurIdx_Object	= 0; // 현재 선택된 인덱스

	ImGui::SeparatorText("Object Prefab List");
	wstring strImgPath = L"../Bin/Resource/Texture/Object/Bush/forest_3.png";
	ImTextureID image = LoadImageFile(wstring_to_utf8(strImgPath).c_str());

	if (ImGui::BeginListBox("  ", ImVec2(280.f, 180.f)))
	{
		for (int i = 0; i < 10; ++i)
		{
			if (ImGui::ImageButton(image, ImVec2(50.f, 50.f))) // 이미지 출력
			{
				iCurIdx_Object = i;
			}

			if (iCurIdxRow < g_iImagPerRow - 1) // 정렬
			{
				ImGui::SameLine();
				iCurIdxRow++;
			}
			else
				iCurIdxRow = 0;
		}
		ImGui::EndListBox();
	}
}

void CImGuiMgr::Show_Header_Light()
{
}

HRESULT CImGuiMgr::Set_ImgPath()
{
	return S_OK;
	map<const _tchar*, CGameObject*> mapObj;

	// TERRAIN, ENVIRONMENT, MONSTER, NPC, ITEM, LINE, TYPEEND

	// Terrain
	mapObj = CManagement::GetInstance()->Get_Layer(OBJ_TYPE::TERRAIN)->Get_ObjectMap();
	
	for (auto iter = mapObj.begin(); iter != mapObj.end(); ++iter)
	{
		wstring imgPath = dynamic_cast<CTexture*>
			(iter->second->Get_Component
			(COMPONENT_TYPE::TEXTURE, ID_STATIC))->Get_TexturePath();

		ImTextureID fildID = LoadImageFile(wstring_to_utf8(imgPath).c_str());

		g_vecObjImgPath[(UINT)IMG_OBJ_TYPE::TERRAIN].push_back(fildID);
	}

	return S_OK;
}

LPDIRECT3DTEXTURE9 CImGuiMgr::LoadImageFile(const char* filePath)
{
	LPDIRECT3DTEXTURE9 pTexture = nullptr;

	D3DXIMAGE_INFO imageInfo;
	HRESULT hr = D3DXGetImageInfoFromFileA(filePath, &imageInfo);

	if (FAILED(hr)) return nullptr;

	hr = D3DXCreateTextureFromFileA(m_pGraphicDev, filePath, &pTexture);
	Safe_Release(m_pGraphicDev); 

	if (FAILED(hr)) return nullptr;

	return pTexture;
}

string CImGuiMgr::wstring_to_utf8(const std::wstring& str)
{
	string result;
	int size = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, nullptr, 0, nullptr, nullptr);
	if (size > 0)
	{
		result.resize(size);
		WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, &result[0], size, nullptr, nullptr);
	}
	return result;
}

void CImGuiMgr::Free()
{
	Safe_Release(m_pGraphicDev);

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}