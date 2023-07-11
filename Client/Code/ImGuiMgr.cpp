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

IMPLEMENT_SINGLETON(CImGuiMgr)

CImGuiMgr::CImGuiMgr()
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

	return S_OK;
}

void CImGuiMgr::ImGui_Update()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Tool Tab");

#pragma region Scene Header
	if (ImGui::CollapsingHeader("Scene"))
	{
#pragma region Button
		if (ImGui::Button("New"))                         
		{

		}
		ImGui::SameLine();
		if (ImGui::Button("Load"))                        
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
#pragma endregion
#pragma region List Box (Image)

		//folderPath = L"../Bin/Resource/Texture/Terrain";
		//wstring imgPath = L"../Bin/Resource/Texture/Object/Bush/forest_5.png";

		//ImTextureID image = LoadImageFile()
		//	//L"../Bin/Resource/Texture/Object/Bush/forest_5.png";

		//if (ImGui::BeginListBox("##", ImVec2(280.f, 300.f)))
		//{
		//	for (int i = 0; i < 1; ++i) 
		//	{

		//		if (ImGui::ImageButton(image, ImVec2(50.f, 50.f)))
		//		{

		//		}
		//		// 한 줄에 4개씩 이미지 출력

		//	}
		//	ImGui::EndListBox();
		//}
#pragma endregion
	}
#pragma endregion
#pragma region Obj Header
	if (ImGui::CollapsingHeader("Object"))
	{
#pragma region Combo
		static ImGuiComboFlags flags = 0;

		const char* items[] = { "Trrain", "Environment", "Monster", "Npc" };
		static int item_current_idx = 0; 
		const char* combo_preview_value = items[item_current_idx];

		if (ImGui::BeginCombo("Object Type", combo_preview_value, flags))
		{
			for (int n = 0; n < IM_ARRAYSIZE(items); n++)
			{
				const bool is_selected = (item_current_idx == n);
				if (ImGui::Selectable(items[n], is_selected))
					item_current_idx = n;

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
#pragma endregion
	}
#pragma endregion
#pragma region Light Header
	if (ImGui::CollapsingHeader("Light"))
	{
	}
#pragma endregion

	ImGui::End();

}

static _bool bInit = false;
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

void CImGuiMgr::Free()
{
	Safe_Release(m_pGraphicDev);

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}