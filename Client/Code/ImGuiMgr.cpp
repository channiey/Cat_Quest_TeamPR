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

#include "TerrainTool.h"

#include <iostream>


#pragma region Global

// �̺�Ʈ �Ŵ��� ���� �� �ʱ�ȭ ����

static _bool			g_bInit = false;

static _bool			g_bPathInit = false; 

// ����ü
enum class				IMG_OBJ_TYPE { TERRAIN, ENVIRONMENT, MONSTER, NPC, ITEM, LINE, TYPEEND };

static const char*		arr_ImgObjType[(UINT)IMG_OBJ_TYPE::TYPEEND] = { "Trrain", "Environment", "Monster", "Npc", "Item", "Line" };


// ���� ���� ����

static _int				g_iSelScene = -1; // ���� ���õ� �� �ε���

static IMG_OBJ_TYPE     g_eSelObjType = IMG_OBJ_TYPE::TYPEEND; // ���� ���õ� ������Ʈ Ÿ�� �ε���

static _int				g_iSelObj = -1; // ���� ���õ� ������Ʈ �ε���



// ��Ÿ
vector<ImTextureID>		g_vecObjImgPath[(UINT)IMG_OBJ_TYPE::TYPEEND]; // �̹��� ���̵� ��� ���� ���� �迭

vector<CGameObject*>	g_vecObjOrigin[(UINT)IMG_OBJ_TYPE::TYPEEND]; // ���� ��ü ���� �迭

CGameObject*			g_pVtxTerrain = nullptr; // ��ŷó���� ���� ���ؽ� �ͷ���

static const _int		g_iImagPerRow = 4; // ���ٴ� ������ �̹��� ��

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

	g_pVtxTerrain = CTerrainTool::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(g_pVtxTerrain, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"TerrainTool", g_pVtxTerrain);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TerrainTool", g_pVtxTerrain), E_FAIL);
	return S_OK;
}

void CImGuiMgr::ImGui_Update()
{
	if (!g_bPathInit)
	{
		g_bPathInit = !g_bPathInit;
		Set_ImgPath(); // �� �� ������Ʈ �̹��� ��� �¾�
	}

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
	if (ImGui::CollapsingHeader("Light"))
	{
		Show_Header_Light();
	}

	ImGui::End();

	if (/*g_pCurGameObject != nullptr &&*/ CInputDev::GetInstance()->Key_Down(MK_LBUTTON)) // �� ���� ������ ���� ����ó��
	{
		Clone_Object(Get_ClickPos());
	}
}

void CImGuiMgr::ImGui_Render()
{
	// �̺�Ʈ �Ŵ��� ���� �� �ӽ� ó��
	if (!g_bInit)
	{
		g_bInit = true;
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

	int			iCurIdxRow		= 0; // �� ���߱� ���� ����
	static int	iCurIdx_Scene	= 0; // ���� ���õ� �ε���

	wstring strImgPath = L"../Bin/Resource/Texture/Object/Bush/forest_5.png";
	ImTextureID image = LoadImageFile(wstring_to_utf8(strImgPath).c_str());


	if (ImGui::BeginListBox(" ", ImVec2(280.f, 180.f)))
	{
		for (int i = 0; i < 10; ++i)
		{
			if (ImGui::ImageButton(image, ImVec2(50.f, 50.f))) // �̹��� ���
			{
				iCurIdx_Scene = i;
				g_iSelScene = iCurIdx_Scene;
			}

			if (iCurIdxRow < g_iImagPerRow - 1) // ����
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
	static int iCurIdx_Object_Type = 0; // ���� ���õ� �ε���
	static ImGuiComboFlags flags = 0;

	const char* combo_preview_value = arr_ImgObjType[iCurIdx_Object_Type];

	if (ImGui::BeginCombo("  ", combo_preview_value, flags))
	{
		for (int n = 0; n < IM_ARRAYSIZE(arr_ImgObjType); n++)
		{
			const bool is_selected = (iCurIdx_Object_Type == n);
			if (ImGui::Selectable(arr_ImgObjType[n], is_selected))
			{
				iCurIdx_Object_Type = n;
				g_eSelObjType = (IMG_OBJ_TYPE)iCurIdx_Object_Type;
			}

			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	// 02. List Box (Object Image)
	int			iCurIdxRow		= 0; // �� ���߱� ���� ����
	static int	iCurIdx_Object	= 0; // ���� ���õ� �ε���

	ImGui::SeparatorText("Object Prefab List");

	if (ImGui::BeginListBox("  ", ImVec2(280.f, 180.f)))
	{
		for (int i = 0; i < g_vecObjImgPath[iCurIdx_Object_Type].size(); ++i)
		{
			if (ImGui::ImageButton(g_vecObjImgPath[iCurIdx_Object_Type][i], ImVec2(50.f, 50.f))) // �̹��� ���
			{
				iCurIdx_Object = i;

				g_iSelObj = iCurIdx_Object;
			}

			if (iCurIdxRow < g_iImagPerRow - 1) // ����
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
	multimap<const _tchar*, CGameObject*> mapObj;
	
	mapObj = CManagement::GetInstance()->Get_Layer(OBJ_TYPE::TERRAIN)->Get_ObjectMap();

	for (auto iter = mapObj.begin(); iter != mapObj.end(); ++iter)
	{
		g_vecObjOrigin[(UINT)IMG_OBJ_TYPE::TERRAIN].push_back(iter->second);

		if (nullptr == iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC)) 
			continue;
		
		wstring imgPath = dynamic_cast<CTexture*>(iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC))->Get_TexturePath();
		g_vecObjImgPath[(UINT)IMG_OBJ_TYPE::TERRAIN].push_back(LoadImageFile(wstring_to_utf8(imgPath).c_str()));
	}

	// Environment
	mapObj = CManagement::GetInstance()->Get_Layer(OBJ_TYPE::ENVIRONMENT)->Get_ObjectMap();
	for (auto iter = mapObj.begin(); iter != mapObj.end(); ++iter)
	{
		g_vecObjOrigin[(UINT)IMG_OBJ_TYPE::ENVIRONMENT].push_back(iter->second);

		if (nullptr == iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC))
			continue;
		wstring imgPath = dynamic_cast<CTexture*>(iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC))->Get_TexturePath();
		g_vecObjImgPath[(UINT)IMG_OBJ_TYPE::ENVIRONMENT].push_back(LoadImageFile(wstring_to_utf8(imgPath).c_str()));
	}

	// Monster
	mapObj = CManagement::GetInstance()->Get_Layer(OBJ_TYPE::MONSTER)->Get_ObjectMap();
	for (auto iter = mapObj.begin(); iter != mapObj.end(); ++iter)
	{
		g_vecObjOrigin[(UINT)IMG_OBJ_TYPE::MONSTER].push_back(iter->second);

		if (nullptr == iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC))
			continue;
		wstring imgPath = dynamic_cast<CTexture*>(iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC))->Get_TexturePath();
		g_vecObjImgPath[(UINT)IMG_OBJ_TYPE::MONSTER].push_back(LoadImageFile(wstring_to_utf8(imgPath).c_str()));
	}

	// Npc
	mapObj = CManagement::GetInstance()->Get_Layer(OBJ_TYPE::NPC)->Get_ObjectMap();
	for (auto iter = mapObj.begin(); iter != mapObj.end(); ++iter)
	{
		g_vecObjOrigin[(UINT)IMG_OBJ_TYPE::NPC].push_back(iter->second);

		if (nullptr == iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC))
			continue;
		wstring imgPath = dynamic_cast<CTexture*>(iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC))->Get_TexturePath();
		g_vecObjImgPath[(UINT)IMG_OBJ_TYPE::NPC].push_back(LoadImageFile(wstring_to_utf8(imgPath).c_str()));
	}
	
	// Item
	/*mapObj = CManagement::GetInstance()->Get_Layer(OBJ_TYPE::ITEM)->Get_ObjectMap();
	for (auto iter = mapObj.begin(); iter != mapObj.end(); ++iter)
	{
			g_vecObjOrigin[(UINT)IMG_OBJ_TYPE::TERRAIN].push_back(iter->second);

	if (nullptr == iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC)) 
			continue;
		wstring imgPath = dynamic_cast<CTexture*>(iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC))->Get_TexturePath();
		g_vecObjImgPath[(UINT)IMG_OBJ_TYPE::ITEM].push_back(LoadImageFile(wstring_to_utf8(imgPath).c_str()));
	}*/

	// Line
	/*mapObj = CManagement::GetInstance()->Get_Layer(OBJ_TYPE::LINE)->Get_ObjectMap();
	for (auto iter = mapObj.begin(); iter != mapObj.end(); ++iter)
	{		g_vecObjOrigin[(UINT)IMG_OBJ_TYPE::TERRAIN].push_back(iter->second);
if (nullptr == iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC)) 
			continue;
		wstring imgPath = dynamic_cast<CTexture*>(iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC))->Get_TexturePath();
		g_vecObjImgPath[(UINT)IMG_OBJ_TYPE::LINE].push_back(LoadImageFile(wstring_to_utf8(imgPath).c_str()));
	}*/

	return S_OK;
}

HRESULT CImGuiMgr::Clone_Object(const _vec3 _vClonePos)
{
	// ����ó��
	if (IMG_OBJ_TYPE::TYPEEND == g_eSelObjType || 0 > g_iSelObj || g_vecObjOrigin[(UINT)g_eSelObjType].size() < g_iSelObj)
		return E_FAIL;

	CGameObject* pClone = g_vecObjOrigin[(UINT)g_eSelObjType][g_iSelObj]; // Ŭ��

	NULL_CHECK_RETURN(pClone, E_FAIL);

	pClone->Get_Transform()->Set_Pos(_vClonePos); // ������ ����

	// �̸� ��� �ұ�?
	
	//CEventMgr::GetInstance()->Add_Obj(pClone->Get)

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

const _vec3& CImGuiMgr::Get_ClickPos()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	_vec3 vPickPos;
	ZeroMemory(&vPickPos, sizeof(_vec3));

	CCalculator::GetInstance()->Mouse_Picking(m_pGraphicDev, pt, &vPickPos);

	return vPickPos;

}

void CImGuiMgr::Free()
{
	Safe_Release(m_pGraphicDev);

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}