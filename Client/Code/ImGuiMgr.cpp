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

// ��������
// �̹��� ����
ImTextureID 			imgThumbnail; // ��� ū �̹���
ImTextureID				imgListFile; // ��� �̹���
int						imagesPerRow; // �� �ٿ� ����� �̹��� ����.

vector<ImTextureID>     vecImgObjListFile; // �ͷ��� ���� �̹��� �迭
vector<ImTextureID>     vecImgTerListFile; // �ͷ��� �̹��� �迭

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

	// �ͷ��� ���ϵ� ���ʿ� �ѹ��� �ʱ�ȭ
	folderPath = L"../Bin/Resource/Texture/Terrain";
	FindFileList(folderPath, m_objFileList);

	vecImgTerListFile.resize(m_objFileList.size());

	for (int i = 0; i < m_objFileList.size(); ++i) {
		// �̹��� ���.
		wstring imgPath = folderPath + L"/" + m_objFileList[i];
		imgListFile = LoadImageFile(wstring_to_utf8(imgPath).c_str());
		vecImgTerListFile[i] = imgListFile;

		// ImGui::TextWrapped("%s", wstring_to_utf8(fileName).c_str()); // ���ϸ�.
		iImgCount++;
	}

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


	_vec3 vArgPos;

	// ���콺�� ������
	//if (CInputDev::GetInstance()->Key_Down(MK_LBUTTON) && m_eArgTag == ARG_OBJ && 
	//	CCalculator::GetInstance()->Mouse_Picking(m_pGraphicDev, pClientPt, &vArgPos))
	//{
	//	// �ش��ϴ� Ű���� �������� ������(�ߺ� �ȵȴٸ�) -> �ߺ�ó���� �ϴ� 9�� �����ۿ� ��ġ�� �ȵƴ�. �ߺ�ó�� ���ϴ� �� ����
	//	//if (!Engine::CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::ENVIRONMENT, L"Building" + iHouseCnt)) {
	//		
	//		// �߰��ϰ�
	//		Engine::CGameObject* pGameObject = __super::Create(m_pGraphicDev);
	//		NULL_CHECK(pGameObject);
	//		CEventMgr::GetInstance()->Add_Obj(L"Building" + iHouseCnt, pGameObject);
	//
	//		// ���� ���۵��� ��ġ�� ���� �̵����ױ⿡ �׿� ���� �ӽ÷� ��ġ ����.
	//		pGameObject->Get_Transform()->Set_Pos(_vec3(vArgPos.x, vArgPos.y + 3, (vArgPos.z) - VTXCNTZ / 2));
	//
	//		// ī��Ʈ ����.
	//		iHouseCnt += 1;
	//}
	// 
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
	Safe_Release(m_pGraphicDev); // ������ ������ (���۷��� ī��Ʈ ����׽��ϴ�)

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
		if (ImGui::BeginTabItem("Terrain")) {
			m_eArgTag = ARG_TERRAIN;
			ImGui::EndTabItem();
		}
		// ������Ʈ ��
		if (ImGui::BeginTabItem("Object")) {
			m_eArgTag = ARG_OBJ;
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

	// ���� ������
	if (m_eArgTag == ARG_TERRAIN) {
		Show_Arg_Terrain();
	}

	// ������Ʈ ������
	if (m_eArgTag == ARG_OBJ) {
		Show_Arg_Obj();
	}
}

// �ͷ���
void CImGuiMgr::Show_Arg_Terrain()
{
	// �����
	if (imgThumbnail)
		ImGui::Image(imgThumbnail, ImVec2(100.f, 100.f));
	else {
		ImGui::Image(nullptr, ImVec2(100.f, 100.f), ImVec2(), ImVec2(), ImVec4(0.5f, 0.5f, 0.5f, 0.f), ImVec4(0.5f, 0.5f, 0.2f, 1.f));
	}
	ImGui::SameLine();

	if (ImGui::Button("Create")) {
		// �� ���� �����
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

// ������Ʈ
void CImGuiMgr::Show_Arg_Obj()
{
	// �����
	if (imgThumbnail)
		ImGui::Image(imgThumbnail, ImVec2(100.f, 100.f));
	else {
		ImGui::Image(nullptr, ImVec2(100.f, 100.f), ImVec2(), ImVec2(), ImVec4(0.5f, 0.5f, 0.5f, 0.f), ImVec4(0.5f, 0.5f, 0.2f, 1.f));
	}

	// �޺� �ڽ�(���� �з�)
	const char* Objitems[] = { "Building",
		"Chest", "Environment", "MageShop",
		"SmithHouse", "Tower", "Other"};
	ImGui::Text("Object Type");
	if (ImGui::Combo("##Object Type", &m_iObjType, Objitems, IM_ARRAYSIZE(Objitems))) {
		m_objFileList.clear();
		bLoadFile = true;
		iImgCount = 0;
	}

	// ����(��)
	if (m_iObjType == OBJ_BUILDING) {
		folderPath = L"../Bin/Resource/Texture/Object/Building";
		m_iObjType = OBJ_BUILDING;
	}
	// ����
	if (m_iObjType == OBJ_CHEST) {
		folderPath = L"../Bin/Resource/Texture/Object/Chest";
		m_iObjType = OBJ_CHEST;
	}
	// ȯ��
	if (m_iObjType == OBJ_ENVIRONMENT) {
		folderPath = L"../Bin/Resource/Texture/Object/Environment";
		m_iObjType = OBJ_ENVIRONMENT;
	}
	// ���� ��
	if (m_iObjType == OBJ_MAGESHOP) {
		folderPath = L"../Bin/Resource/Texture/Object/MageShop";
		m_iObjType = OBJ_MAGESHOP;
	}
	// ���尣
	if (m_iObjType == OBJ_SMITHHOUSE) {
		folderPath = L"../Bin/Resource/Texture/Object/SmithHouse";
		m_iObjType = OBJ_SMITHHOUSE;
	}
	// Ÿ��
	if (m_iObjType == OBJ_TOWER) {
		folderPath = L"../Bin/Resource/Texture/Object/Tower";
		m_iObjType = OBJ_TOWER;
	}
	// �� ��
	if (m_iObjType == OBJ_OTHER) {
		folderPath = L"../Bin/Resource/Texture/Object/Other";
		m_iObjType = OBJ_OTHER;
	}


	if (bLoadFile) {
		FindFileList(folderPath, m_objFileList); // ���� ��θ� ã�Ƽ� �� �ȿ� �ִ� png ���� �迭�� ���.

		vecImgObjListFile.resize(m_objFileList.size());

		for (int i = 0; i < m_objFileList.size(); ++i) {
			// �̹��� ���.
			wstring imgPath = folderPath + L"/" + m_objFileList[i];
			imgListFile = LoadImageFile(wstring_to_utf8(imgPath).c_str());
			vecImgObjListFile[i] = imgListFile;

			// ImGui::TextWrapped("%s", wstring_to_utf8(fileName).c_str()); // ���ϸ�.
			iImgCount++;
		}
	}

	Show_ImageButton();
}

void CImGuiMgr::Show_Line()
{
}

// �̹��� 4x4 ���
void CImGuiMgr::Show_ImageButton()
{
	int currentImageIndex = 0; // �̹����� 4���� ����ϱ� ���� ����
	int iSelect = 0; // ���õ� �̹����� ����Ϸ� ǥ���ϱ� ����.

	if (m_eArgTag == ARG_OBJ) {
		if (ImGui::BeginListBox("##", ImVec2(280.f, 300.f))) {
			for (int i = 0; i < vecImgObjListFile.size(); ++i) {

				if (ImGui::ImageButton(vecImgObjListFile[i], ImVec2(50.f, 50.f))) {
					imgThumbnail = vecImgObjListFile[i];
				}
				// �� �ٿ� 4���� �̹��� ���
				if (currentImageIndex < imagesPerRow - 1)
				{
					ImGui::SameLine(); // ���������� �̵�.
					currentImageIndex++;
				}
				else
					currentImageIndex = 0; // 0���� �ʱ�ȭ �԰� ���ÿ� �ڵ����� �����ٷ�.
			}
			ImGui::EndListBox();
		}

		if (iImgCount) bLoadFile = false;
	}

	// �̹����� ����ؼ� ��µǰ����� �� �ȵǱ� ������ �׳� ����.
	else if (m_eArgTag == ARG_TERRAIN) {
		if (ImGui::BeginListBox("##", ImVec2(280.f, 300.f))) {
			for (int i = 0; i < vecImgTerListFile.size(); ++i) {

				if (ImGui::ImageButton(vecImgTerListFile[i], ImVec2(50.f, 50.f))) {
					imgThumbnail = vecImgTerListFile[i];
					m_iSelTerrain = i;
				}
				// �� �ٿ� 4���� �̹��� ���
				if (currentImageIndex < imagesPerRow - 1)
				{
					ImGui::SameLine(); // ���������� �̵�.
					currentImageIndex++;
				}
				else
					currentImageIndex = 0; // 0���� �ʱ�ȭ �԰� ���ÿ� �ڵ����� �����ٷ�.
			}
			ImGui::EndListBox();
		}

		if (iImgCount) bLoadFile = false;
	}
	
}

void CImGuiMgr::Free()
{
	Safe_Release(m_pGraphicDev); // ������ ������ (���۷��� ī��Ʈ ����׽��ϴ�)

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}