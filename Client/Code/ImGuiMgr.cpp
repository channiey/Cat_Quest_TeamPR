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

// 
#include "House.h"
//
#include "TerrainTool.h"
#include "TerrainWorld.h"
#include "TerrainIceWorld.h"
#include "TerrainIceDungeon.h"

// 전역변수
// 이미지 관련
ImTextureID 			imgThumbnail; // 상단 큰 이미지
ImTextureID				imgListFile; // 요소 이미지
int						imagesPerRow; // 한 줄에 출력할 이미지 개수.

vector<ImTextureID>     vecImgObjListFile; // 터레인 제외 이미지 배열
vector<ImTextureID>     vecImgTerListFile; // 터레인 이미지 배열

IMPLEMENT_SINGLETON(CImGuiMgr)

static _bool bInit = false;

////////////////////////////

CImGuiMgr::CImGuiMgr()
	: m_eArgTag(ARG_TERRAIN), m_iObjType(OBJ_BUILDING)
	, iHouseCnt(0)
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

	// 터레인 파일들 최초에 한번만 초기화
	folderPath = L"../Bin/Resource/Texture/Terrain";
	FindFileList(folderPath, m_objFileList);

	vecImgTerListFile.resize(m_objFileList.size());

	for (int i = 0; i < m_objFileList.size(); ++i) {
		// 이미지 출력.
		wstring imgPath = folderPath + L"/" + m_objFileList[i];
		imgListFile = LoadImageFile(wstring_to_utf8(imgPath).c_str());
		vecImgTerListFile[i] = imgListFile;

		// ImGui::TextWrapped("%s", wstring_to_utf8(fileName).c_str()); // 파일명.
		iImgCount++;
	}

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


	_vec3 vArgPos;

	// 마우스가 눌리면
	//if (CInputDev::GetInstance()->Key_Down(MK_LBUTTON) && m_eArgTag == ARG_OBJ && 
	//	CCalculator::GetInstance()->Mouse_Picking(m_pGraphicDev, pClientPt, &vArgPos))
	//{
	//	// 해당하는 키값이 존재하지 않으면(중복 안된다면) -> 중복처리를 하니 9개 까지밖에 설치가 안됐다. 중복처리 안하니 잘 동작
	//	//if (!Engine::CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::ENVIRONMENT, L"Building" + iHouseCnt)) {
	//		
	//		// 추가하고
	//		Engine::CGameObject* pGameObject = __super::Create(m_pGraphicDev);
	//		NULL_CHECK(pGameObject);
	//		CEventMgr::GetInstance()->Add_Obj(L"Building" + iHouseCnt, pGameObject);
	//
	//		// 현재 버퍼들의 위치를 전부 이동시켰기에 그에 맞춰 임시로 위치 설정.
	//		pGameObject->Get_Transform()->Set_Pos(_vec3(vArgPos.x, vArgPos.y + 3, (vArgPos.z) - VTXCNTZ / 2));
	//
	//		// 카운트 증가.
	//		iHouseCnt += 1;
	//}
	// 
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
void CImGuiMgr::FindFileList(const wstring& folderPath, vector<wstring>& m_objFileList)
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

			m_objFileList.push_back(findData.cFileName);
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
	Safe_Release(m_pGraphicDev); // 지우지 마세요 (레퍼런스 카운트 맞춰뒀습니다)

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
		if (ImGui::BeginTabItem("Terrain")) {
			m_eArgTag = ARG_TERRAIN;
			ImGui::EndTabItem();
		}
		// 오브젝트 탭
		if (ImGui::BeginTabItem("Object")) {
			m_eArgTag = ARG_OBJ;
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

	// 지형 컨텐츠
	if (m_eArgTag == ARG_TERRAIN) {
		Show_Arg_Terrain();
	}

	// 오브젝트 컨텐츠
	if (m_eArgTag == ARG_OBJ) {
		Show_Arg_Obj();
	}
}

// 터레인
void CImGuiMgr::Show_Arg_Terrain()
{
	// 썸네일
	if (imgThumbnail)
		ImGui::Image(imgThumbnail, ImVec2(100.f, 100.f));
	else {
		ImGui::Image(nullptr, ImVec2(100.f, 100.f), ImVec2(), ImVec2(), ImVec4(0.5f, 0.5f, 0.5f, 0.f), ImVec4(0.5f, 0.5f, 0.2f, 1.f));
	}
	ImGui::SameLine();

	if (ImGui::Button("Create")) {
		// 맵 정보 지우기
		CManagement::GetInstance()->Get_Scene()->Empty_Layer(OBJ_TYPE::TERRAIN);

		if (m_iSelTerrain == TERRAIN_WORLD) {
			Engine::CGameObject* pGameObject = CTerrainTool::Create(m_pGraphicDev);
			NULL_CHECK(pGameObject);
			CEventMgr::GetInstance()->Add_Obj(L"TerrainTool", pGameObject);

			pGameObject = CTerrainWorld::Create(m_pGraphicDev);
			NULL_CHECK(pGameObject);
			CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pGameObject);

			// if (m_pGraphicDev) Safe_Release(m_pGraphicDev);

		}
		else if (m_iSelTerrain == TERRAIN_TEMP)
		{
			Engine::CGameObject* pGameObject = CTerrainTool::Create(m_pGraphicDev);
			NULL_CHECK(pGameObject);
			CEventMgr::GetInstance()->Add_Obj(L"TerrainTool", pGameObject);

			pGameObject = CTerrainIceWorld::Create(m_pGraphicDev);
			NULL_CHECK(pGameObject);
			CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld_Ice", pGameObject);

			// if (m_pGraphicDev) Safe_Release(m_pGraphicDev);
		}
		else if (m_iSelTerrain == TERRAIN_DUNGEON_ICE)
		{
			Engine::CGameObject* pGameObject = CTerrainTool::Create(m_pGraphicDev);
			NULL_CHECK(pGameObject);
			CEventMgr::GetInstance()->Add_Obj(L"TerrainTool", pGameObject);

			pGameObject = CTerrainIceDungeon::Create(m_pGraphicDev);
			NULL_CHECK(pGameObject);
			CEventMgr::GetInstance()->Add_Obj(L"TerrainDungeon_Ice", pGameObject);

			// if(m_pGraphicDev) Safe_Release(m_pGraphicDev);
		}
	}

	Show_ImageButton();
}

// 오브젝트
void CImGuiMgr::Show_Arg_Obj()
{
	// 썸네일
	if (imgThumbnail)
		ImGui::Image(imgThumbnail, ImVec2(100.f, 100.f));
	else {
		ImGui::Image(nullptr, ImVec2(100.f, 100.f), ImVec2(), ImVec2(), ImVec4(0.5f, 0.5f, 0.5f, 0.f), ImVec4(0.5f, 0.5f, 0.2f, 1.f));
	}

	// 콤보 박스(하위 분류)
	const char* Objitems[] = { "Building",
		"Chest", "Environment", "MageShop",
		"SmithHouse", "Tower", "Other"};
	ImGui::Text("Object Type");
	if (ImGui::Combo("##Object Type", &m_iObjType, Objitems, IM_ARRAYSIZE(Objitems))) {
		m_objFileList.clear();
		bLoadFile = true;
		iImgCount = 0;
	}

	// 빌딩(집)
	if (m_iObjType == OBJ_BUILDING) {
		folderPath = L"../Bin/Resource/Texture/Object/Building";
		m_iObjType = OBJ_BUILDING;
	}
	// 상자
	if (m_iObjType == OBJ_CHEST) {
		folderPath = L"../Bin/Resource/Texture/Object/Chest";
		m_iObjType = OBJ_CHEST;
	}
	// 환경
	if (m_iObjType == OBJ_ENVIRONMENT) {
		folderPath = L"../Bin/Resource/Texture/Object/Environment";
		m_iObjType = OBJ_ENVIRONMENT;
	}
	// 매직 숍
	if (m_iObjType == OBJ_MAGESHOP) {
		folderPath = L"../Bin/Resource/Texture/Object/MageShop";
		m_iObjType = OBJ_MAGESHOP;
	}
	// 대장간
	if (m_iObjType == OBJ_SMITHHOUSE) {
		folderPath = L"../Bin/Resource/Texture/Object/SmithHouse";
		m_iObjType = OBJ_SMITHHOUSE;
	}
	// 타워
	if (m_iObjType == OBJ_TOWER) {
		folderPath = L"../Bin/Resource/Texture/Object/Tower";
		m_iObjType = OBJ_TOWER;
	}
	// 그 외
	if (m_iObjType == OBJ_OTHER) {
		folderPath = L"../Bin/Resource/Texture/Object/Other";
		m_iObjType = OBJ_OTHER;
	}


	if (bLoadFile) {
		FindFileList(folderPath, m_objFileList); // 폴더 경로를 찾아서 그 안에 있는 png 전부 배열에 담기.

		vecImgObjListFile.resize(m_objFileList.size());

		for (int i = 0; i < m_objFileList.size(); ++i) {
			// 이미지 출력.
			wstring imgPath = folderPath + L"/" + m_objFileList[i];
			imgListFile = LoadImageFile(wstring_to_utf8(imgPath).c_str());
			vecImgObjListFile[i] = imgListFile;

			// ImGui::TextWrapped("%s", wstring_to_utf8(fileName).c_str()); // 파일명.
			iImgCount++;
		}
	}

	Show_ImageButton();
}

void CImGuiMgr::Show_Line()
{
}

// 이미지 4x4 출력
void CImGuiMgr::Show_ImageButton()
{
	int currentImageIndex = 0; // 이미지를 4개씩 출력하기 위한 변수
	int iSelect = 0; // 선택된 이미지를 썸네일로 표시하기 위해.

	if (m_eArgTag == ARG_OBJ) {
		if (ImGui::BeginListBox("##", ImVec2(280.f, 300.f))) {
			for (int i = 0; i < vecImgObjListFile.size(); ++i) {

				if (ImGui::ImageButton(vecImgObjListFile[i], ImVec2(50.f, 50.f))) {
					imgThumbnail = vecImgObjListFile[i];
				}
				// 한 줄에 4개씩 이미지 출력
				if (currentImageIndex < imagesPerRow - 1)
				{
					ImGui::SameLine(); // 오른쪽으로 이동.
					currentImageIndex++;
				}
				else
					currentImageIndex = 0; // 0으로 초기화 함과 동시에 자동으로 다음줄로.
			}
			ImGui::EndListBox();
		}

		if (iImgCount) bLoadFile = false;
	}

	// 이미지가 계속해서 출력되겠지만 얼마 안되기 때문에 그냥 진행.
	else if (m_eArgTag == ARG_TERRAIN) {
		if (ImGui::BeginListBox("##", ImVec2(280.f, 300.f))) {
			for (int i = 0; i < vecImgTerListFile.size(); ++i) {

				if (ImGui::ImageButton(vecImgTerListFile[i], ImVec2(50.f, 50.f))) {
					imgThumbnail = vecImgTerListFile[i];
					m_iSelTerrain = i;
				}
				// 한 줄에 4개씩 이미지 출력
				if (currentImageIndex < imagesPerRow - 1)
				{
					ImGui::SameLine(); // 오른쪽으로 이동.
					currentImageIndex++;
				}
				else
					currentImageIndex = 0; // 0으로 초기화 함과 동시에 자동으로 다음줄로.
			}
			ImGui::EndListBox();
		}

		if (iImgCount) bLoadFile = false;
	}
	
}

void CImGuiMgr::Free()
{
	Safe_Release(m_pGraphicDev); // 지우지 마세요 (레퍼런스 카운트 맞춰뒀습니다)

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}