#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx9.h"

#include "ImGuiMgr.h"

#include "stdafx.h"
#include "MainApp.h"
#include "InputDev.h"
#include "Calculator.h"

// 전역변수
// 이미지 관련
ImTextureID 			imgThumbnail; // 상단 큰 이미지
ImTextureID				imgListFile; // 요소 이미지
ImTextureID				tempImage; //   이미지 임시 저장.
int						imagesPerRow; // 한 줄에 출력할 이미지 개수.

vector<ImTextureID>     vecImgListFile; // 요소 이미지 배열

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

	// 스크린 좌표
	POINT pClientPt;
	GetCursorPos(&pClientPt);
	ScreenToClient(g_hWnd, &pClientPt);

	if (CInputDev::GetInstance()->Get_DIMouseState(DIM_LB))
	{
		_vec3 temp = CCalculator::GetInstance()->Mouse_Picking(m_pGraphicDev, pClientPt);

		Safe_Release(m_pGraphicDev); // 여기 추가
	}


	// Mouse 레이아웃
	ImGui::Begin("MousePos(Client)");

	ImGui::Text("MouseX : %d", pClientPt.x);
	ImGui::Text("MouseY : %d", pClientPt.y);

	ImGui::End();

	// Arrangement 레이아웃
	ImGui::Begin("Arrangement");
	Show_Arrangement(); // Tab 관련
	ImGui::End();

	// Line 레이아웃
	ImGui::Begin("Line");
	Show_Line();
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

// 파일 경로
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

// wstring utf8 형식으로 변환.
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

// 경로로 이미지 가져오기.
LPDIRECT3DTEXTURE9 CImGuiMgr::LoadImageFile(const char* filePath)
{
	LPDIRECT3DTEXTURE9 pTexture = nullptr;

	D3DXIMAGE_INFO imageInfo;
	HRESULT hr = D3DXGetImageInfoFromFileA(filePath, &imageInfo);

	if (FAILED(hr)) return nullptr;

	hr = D3DXCreateTextureFromFileA(m_pGraphicDev, filePath, &pTexture);
	// Safe_Release(m_pGraphicDev);

	if (FAILED(hr)) return nullptr;

	//	imgThumbnail = pTexture; // 초기 NonSelect상태 시 빈화면 방지

	return pTexture;
}

// 큰 탭 분류
void CImGuiMgr::Show_Arrangement()
{
	// 탭 선택
	if (ImGui::BeginTabBar("Tag")) {
		// 타일 탭
		if (ImGui::BeginTabItem("Tile")) {
			m_eArgTag = ARG_TILE;
			ImGui::EndTabItem();
		}
		// 오브젝트 탭
		if (ImGui::BeginTabItem("Object")) {
			m_eArgTag = ARG_OBJ;
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

	// 타일 컨텐츠
	if (m_eArgTag == ARG_TILE) {
		Show_Arg_Tile();
	}

	// 오브젝트 컨텐츠
	if (m_eArgTag == ARG_OBJ) {
		Show_Arg_Obj();
	}

}

// 타일 드롭 다운
void CImGuiMgr::Show_Arg_Tile()
{
	// 썸네일
	if (imgThumbnail)
		ImGui::Image(imgThumbnail, ImVec2(100.f, 100.f));
	else {
		ImGui::Image(nullptr, ImVec2(100.f, 100.f), ImVec2(), ImVec2(), ImVec4(0.5f, 0.5f, 0.5f, 0.f), ImVec4(0.5f, 0.5f, 0.2f, 1.f));
	}

	// 콤보 박스(하위 분류)
	const char* Tileitems[] = { "GrassField",
		"FieldWater", "IceField", "IceDungeon",
		"StoneDungeon1", "StoneDungeon2", "TempleDungeon", "Smith" };
	ImGui::Text("Terrain Type");
	if (ImGui::Combo("##Terrain Type", &m_iTileType, Tileitems, IM_ARRAYSIZE(Tileitems))) {
		fileList.clear();
		bLoadFile = true;
		iImgCount = 0;
	}

	// 육지(초원) 필드
	if (m_iTileType == TILE_GRASS_FIELD) {
		folderPath = L"../Bin/Resource/Texture/Tile/GrassField";
		m_iTileType = TILE_GRASS_FIELD;
	}
	// 물 필드
	if (m_iTileType == TILE_WATER_FIELD) {
		folderPath = L"../Bin/Resource/Texture/Tile/FieldWater";
		m_iTileType = TILE_WATER_FIELD;
	}
	// 얼음 필드
	if (m_iTileType == TILE_ICE_FIELD) {
		folderPath = L"../Bin/Resource/Texture/Tile/IceField";
		m_iTileType = TILE_ICE_FIELD;
	}
	// 얼음 던전
	if (m_iTileType == TILE_ICE_DUNGEON) {
		folderPath = L"../Bin/Resource/Texture/Tile/IceDungeon";
		m_iTileType = TILE_ICE_DUNGEON;
	}
	// 돌 던전 1
	if (m_iTileType == TILE_STONE_DUNGEON) {
		folderPath = L"../Bin/Resource/Texture/Tile/StoneDungeon1";
		m_iTileType = TILE_STONE_DUNGEON;
	}
	// 돌 던전 2
	if (m_iTileType == TILE_STONE_DUNGEON2) {
		folderPath = L"../Bin/Resource/Texture/Tile/StoneDungeon2";
		m_iTileType = TILE_STONE_DUNGEON2;
	}
	// 사원(유적) 던전
	if (m_iTileType == TILE_TEMPLE_DUNGEON) {
		folderPath = L"../Bin/Resource/Texture/Tile/TempleDungeon";
		m_iTileType = TILE_TEMPLE_DUNGEON;
	}
	// 대장간
	if (m_iTileType == TILE_SMITH) {
		folderPath = L"../Bin/Resource/Texture/Tile/Smith";
		m_iTileType = TILE_SMITH;
	}


	if (bLoadFile) {
		FindFileList(folderPath, fileList); // 폴더 경로를 찾아서 그 안에 있는 png 전부 배열에 담기.

		vecImgListFile.resize(fileList.size());

		for (int i = 0; i < fileList.size(); ++i) {
			// 이미지 출력.
			wstring imgPath = folderPath + L"/" + fileList[i];
			imgListFile = LoadImageFile(wstring_to_utf8(imgPath).c_str());
			vecImgListFile[i] = imgListFile;

			// ImGui::TextWrapped("%s", wstring_to_utf8(fileName).c_str()); // 파일명.
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

// 이미지 4x4 출력
void CImGuiMgr::Show_ImageButton()
{
	int currentImageIndex = 0; // 이미지를 4개씩 출력하기 위한 변수
	int iSelect = 0; // 선택된 이미지를 썸네일로 표시하기 위해.

	// 조건문 안에 들어오는지 테스트 해보자
	if (ImGui::BeginListBox("##", ImVec2(280.f, 300.f))) {
		for (int i = 0; i < vecImgListFile.size(); ++i) {

			if (ImGui::ImageButton(vecImgListFile[i], ImVec2(50.f, 50.f))) {
				imgThumbnail = vecImgListFile[i];
			}

			// 한 줄에 4개씩 이미지 출력
			if (currentImageIndex < imagesPerRow - 1)
			{
				ImGui::SameLine(); // 오른쪽으로 이동.
				currentImageIndex++;
			}
			else
			{
				currentImageIndex = 0; // 0으로 초기화 함과 동시에 자동으로 다음줄로.
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