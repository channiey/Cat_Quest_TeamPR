#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx9.h"

#include "ImGuiMgr.h"

#include "stdafx.h"
#include "MainApp.h"
#include "InputDev.h"
#include "Calculator.h"

// ��������
// �̹��� ����
ImTextureID 			imgThumbnail; // ��� ū �̹���
ImTextureID				imgListFile; // ��� �̹���
ImTextureID				tempImage; //   �̹��� �ӽ� ����.
int						imagesPerRow; // �� �ٿ� ����� �̹��� ����.

vector<ImTextureID>     vecImgListFile; // ��� �̹��� �迭

IMPLEMENT_SINGLETON(CImGuiMgr)

static _bool bInit = false;

////////////////////////////

CImGuiMgr::CImGuiMgr()
	: m_eArgTag(ARG_TILE), m_iTileType(TILE_GRASS_FIELD)
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

	imagesPerRow = 4;

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

	// ��ũ�� ��ǥ
	POINT pClientPt;
	GetCursorPos(&pClientPt);
	ScreenToClient(g_hWnd, &pClientPt);

	if (CInputDev::GetInstance()->Get_DIMouseState(DIM_LB))
	{
		_vec3 temp = CCalculator::GetInstance()->Mouse_Picking(m_pGraphicDev, pClientPt);

		Safe_Release(m_pGraphicDev); // ���� �߰�
	}


	// Mouse ���̾ƿ�
	ImGui::Begin("MousePos(Client)");

	ImGui::Text("MouseX : %d", pClientPt.x);
	ImGui::Text("MouseY : %d", pClientPt.y);

	ImGui::End();

	// Arrangement ���̾ƿ�
	ImGui::Begin("Arrangement");
	Show_Arrangement(); // Tab ����
	ImGui::End();

	// Line ���̾ƿ�
	ImGui::Begin("Line");
	Show_Line();
	ImGui::End();
}

void CImGuiMgr::ImGui_Render()
{
	// �̺�Ʈ �Ŵ��� ���� �� �ӽ� ó��
	if (!bInit)
	{
		bInit = true;
		return;
	}
	ImGui::Render();

	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

// ���� ���
void CImGuiMgr::FindFileList(const wstring& folderPath, vector<wstring>& fileList)
{
	wstring searchPath = folderPath + L"\\*.png";

	WIN32_FIND_DATA findData;
	HANDLE hFind = FindFirstFile(searchPath.c_str(), &findData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				continue;

			fileList.push_back(findData.cFileName);
		} while (FindNextFile(hFind, &findData));

		FindClose(hFind);
	}
}

// wstring utf8 �������� ��ȯ.
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

// ��η� �̹��� ��������.
LPDIRECT3DTEXTURE9 CImGuiMgr::LoadImageFile(const char* filePath)
{
	LPDIRECT3DTEXTURE9 pTexture = nullptr;

	D3DXIMAGE_INFO imageInfo;
	HRESULT hr = D3DXGetImageInfoFromFileA(filePath, &imageInfo);

	if (FAILED(hr)) return nullptr;

	hr = D3DXCreateTextureFromFileA(m_pGraphicDev, filePath, &pTexture);
	// Safe_Release(m_pGraphicDev);

	if (FAILED(hr)) return nullptr;

	//	imgThumbnail = pTexture; // �ʱ� NonSelect���� �� ��ȭ�� ����

	return pTexture;
}

// ū �� �з�
void CImGuiMgr::Show_Arrangement()
{
	// �� ����
	if (ImGui::BeginTabBar("Tag")) {
		// Ÿ�� ��
		if (ImGui::BeginTabItem("Tile")) {
			m_eArgTag = ARG_TILE;
			ImGui::EndTabItem();
		}
		// ������Ʈ ��
		if (ImGui::BeginTabItem("Object")) {
			m_eArgTag = ARG_OBJ;
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

	// Ÿ�� ������
	if (m_eArgTag == ARG_TILE) {
		Show_Arg_Tile();
	}

	// ������Ʈ ������
	if (m_eArgTag == ARG_OBJ) {
		Show_Arg_Obj();
	}

}

// Ÿ�� ��� �ٿ�
void CImGuiMgr::Show_Arg_Tile()
{
	// �����
	if (imgThumbnail)
		ImGui::Image(imgThumbnail, ImVec2(100.f, 100.f));
	else {
		ImGui::Image(nullptr, ImVec2(100.f, 100.f), ImVec2(), ImVec2(), ImVec4(0.5f, 0.5f, 0.5f, 0.f), ImVec4(0.5f, 0.5f, 0.2f, 1.f));
	}

	// �޺� �ڽ�(���� �з�)
	const char* Tileitems[] = { "GrassField",
		"FieldWater", "IceField", "IceDungeon",
		"StoneDungeon1", "StoneDungeon2", "TempleDungeon", "Smith" };
	ImGui::Text("Terrain Type");
	if (ImGui::Combo("##Terrain Type", &m_iTileType, Tileitems, IM_ARRAYSIZE(Tileitems))) {
		fileList.clear();
		bLoadFile = true;
		iImgCount = 0;
	}

	// ����(�ʿ�) �ʵ�
	if (m_iTileType == TILE_GRASS_FIELD) {
		folderPath = L"../Bin/Resource/Texture/Tile/GrassField";
		m_iTileType = TILE_GRASS_FIELD;
	}
	// �� �ʵ�
	if (m_iTileType == TILE_WATER_FIELD) {
		folderPath = L"../Bin/Resource/Texture/Tile/FieldWater";
		m_iTileType = TILE_WATER_FIELD;
	}
	// ���� �ʵ�
	if (m_iTileType == TILE_ICE_FIELD) {
		folderPath = L"../Bin/Resource/Texture/Tile/IceField";
		m_iTileType = TILE_ICE_FIELD;
	}
	// ���� ����
	if (m_iTileType == TILE_ICE_DUNGEON) {
		folderPath = L"../Bin/Resource/Texture/Tile/IceDungeon";
		m_iTileType = TILE_ICE_DUNGEON;
	}
	// �� ���� 1
	if (m_iTileType == TILE_STONE_DUNGEON) {
		folderPath = L"../Bin/Resource/Texture/Tile/StoneDungeon1";
		m_iTileType = TILE_STONE_DUNGEON;
	}
	// �� ���� 2
	if (m_iTileType == TILE_STONE_DUNGEON2) {
		folderPath = L"../Bin/Resource/Texture/Tile/StoneDungeon2";
		m_iTileType = TILE_STONE_DUNGEON2;
	}
	// ���(����) ����
	if (m_iTileType == TILE_TEMPLE_DUNGEON) {
		folderPath = L"../Bin/Resource/Texture/Tile/TempleDungeon";
		m_iTileType = TILE_TEMPLE_DUNGEON;
	}
	// ���尣
	if (m_iTileType == TILE_SMITH) {
		folderPath = L"../Bin/Resource/Texture/Tile/Smith";
		m_iTileType = TILE_SMITH;
	}


	if (bLoadFile) {
		FindFileList(folderPath, fileList); // ���� ��θ� ã�Ƽ� �� �ȿ� �ִ� png ���� �迭�� ���.

		vecImgListFile.resize(fileList.size());

		for (int i = 0; i < fileList.size(); ++i) {
			// �̹��� ���.
			wstring imgPath = folderPath + L"/" + fileList[i];
			imgListFile = LoadImageFile(wstring_to_utf8(imgPath).c_str());
			vecImgListFile[i] = imgListFile;

			// ImGui::TextWrapped("%s", wstring_to_utf8(fileName).c_str()); // ���ϸ�.
			iImgCount++;
		}
	}

	Show_ImageButton();
}

void CImGuiMgr::Show_Arg_Obj()
{
}

void CImGuiMgr::Show_Line()
{
}

// �̹��� 4x4 ���
void CImGuiMgr::Show_ImageButton()
{
	int currentImageIndex = 0; // �̹����� 4���� ����ϱ� ���� ����
	int iSelect = 0; // ���õ� �̹����� ����Ϸ� ǥ���ϱ� ����.

	// ���ǹ� �ȿ� �������� �׽�Ʈ �غ���
	if (ImGui::BeginListBox("##", ImVec2(280.f, 300.f))) {
		for (int i = 0; i < vecImgListFile.size(); ++i) {

			if (ImGui::ImageButton(vecImgListFile[i], ImVec2(50.f, 50.f))) {
				imgThumbnail = vecImgListFile[i];
			}

			// �� �ٿ� 4���� �̹��� ���
			if (currentImageIndex < imagesPerRow - 1)
			{
				ImGui::SameLine(); // ���������� �̵�.
				currentImageIndex++;
			}
			else
			{
				currentImageIndex = 0; // 0���� �ʱ�ȭ �԰� ���ÿ� �ڵ����� �����ٷ�.
			}
		}

		ImGui::EndListBox();
	}

	if (iImgCount) bLoadFile = false;
}

void CImGuiMgr::Free()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	Safe_Release(m_pGraphicDev);
}