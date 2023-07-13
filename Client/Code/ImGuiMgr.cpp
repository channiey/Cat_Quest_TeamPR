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

#include "TerrainWorld.h"
#include "TerrainTool.h"
#include "TerrainIceWorld.h"
#include "TerrainIceDungeon.h"
// 빌딩(집)
#include "House1.h"
#include "House2.h"
#include "House3.h"
#include "House4.h"
#include "House5.h"
#include "House6.h"
#include "KingHouse.h"
#include "Smithy.h"
#include "MagicShop.h"
// 부쉬
#include "Bush1.h"
#include "Bush2.h"
#include "Bush3.h"
#include "Bush4.h"
#include "Bush5.h"
#include "Bush6.h"
#include "Bush7.h"
#include "Bush8.h"
#include "Bush9.h"
#include "Bush10.h"
#include "Bush11.h"
// 산
#include "Mountain_Grass.h"
#include "Mountain_Ice.h"
// 돌
#include "Rock1.h"
#include "Rock2.h"
#include "Rock3.h"
#include "Rock4.h"
// 기둥
#include "Rock_Pillar1.h"
#include "Rock_Pillar2.h"
#include "Rock_Pillar3.h"
#include "Ice_Pillar1.h"
#include "Temple_Pillar1.h"
#include "Temple_Pillar2.h"
// 던전
#include "Dungeon_Grass.h"
#include "Dungeon_Ice.h"
#include "Dungeon_Temple.h"
// 타워
#include "Tower1.h"
#include "Tower2.h"
#include "Tower3.h"
// 상자
#include "Chest_Cosmetic.h"
#include "Chest_Gold.h"
#include "Chest_Regular.h"
// NPC
#include "Npc_King.h"
#include "Npc_Mage.h"
#include "Npc_BlackSmith.h"
#include "Npc_Soldier.h"
#include "Npc_Citizen1.h"
#include "Npc_Citizen2.h"
// Monster
#include "ExpUI.h"
#include "EnterUI.h"
#include "Hedgehog.h"
#include "LineObject.h"
#include "Bat.h"
#include "Dragon.h"
#include "Ram.h"
#include "Fox.h"
#include "Wyvern.h"
#include "Squirrel.h"
#include "Player.h"
#include "CuteMonster.h"
#include "Environment.h"
#include "Tool_Camera.h"
#include "CameraTargetObj.h"
#include <iostream>


#pragma region Global

// 이벤트 매니저 생성 전 초기화 관련

static _bool			g_bInit = false;

static _bool			g_bPathInit = false; 

// 열거체
enum class				IMG_OBJ_TYPE { TERRAIN, ENVIRONMENT, MONSTER, NPC, ITEM, LINE, TYPEEND };

static const char*		arr_ImgObjType[(UINT)IMG_OBJ_TYPE::TYPEEND] = { "Trrain", "Environment", "Monster", "Npc", "Item", "Line" };


// 공용 변수 관련

static _int				g_iSelScene = -1; // 현재 선택된 씬 인덱스

static IMG_OBJ_TYPE     g_eSelObjType = IMG_OBJ_TYPE::TYPEEND; // 현재 선택된 오브젝트 타입 인덱스

static _int				g_iSelObj = -1; // 현재 선택된 오브젝트 인덱스



// 기타
vector<ImTextureID>		g_vecObjImgPath[(UINT)IMG_OBJ_TYPE::TYPEEND]; // 이미지 아이디 경로 저장 벡터 배열

vector<CGameObject*>	g_vecObjOrigin[(UINT)IMG_OBJ_TYPE::TYPEEND]; // 원본 객체 최초 저장 배열

CGameObject*			g_pVtxTerrain = nullptr; // 피킹처리를 위한 버텍스 터레인

static const _int		g_iImagPerRow = 4; // 한줄당 나열할 이미지 수

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
		Set_ImgPath(); // 맵 및 오브젝트 이미지 경로 셋업
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

	if (CInputDev::GetInstance()->Key_Down(MK_LBUTTON))
	{
		_vec3 vPickPos = Get_ClickPos();

		if(vec3.zero != vPickPos) // 터레인 영역을 벗어난 피킹에 대한 예외 처리
			Clone_Object(vPickPos);
	}
}

void CImGuiMgr::ImGui_Render()
{
	// 이벤트 매니저 생성 전 임시 처방
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
				g_iSelScene = iCurIdx_Scene;
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
	int			iCurIdxRow		= 0; // 줄 맞추기 위한 변수
	static int	iCurIdx_Object	= 0; // 현재 선택된 인덱스

	ImGui::SeparatorText("Object Prefab List");

	if (ImGui::BeginListBox("  ", ImVec2(280.f, 180.f)))
	{
		for (int i = 0; i < g_vecObjImgPath[iCurIdx_Object_Type].size(); ++i)
		{
			if (ImGui::ImageButton(g_vecObjImgPath[iCurIdx_Object_Type][i], ImVec2(50.f, 50.f))) // 이미지 출력
			{
				iCurIdx_Object = i;

				g_iSelObj = iCurIdx_Object;
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

HRESULT CImGuiMgr::Clone_Object(const _vec3 _vPickPos)
{
	return S_OK;
	// 예외처리
	if (IMG_OBJ_TYPE::TYPEEND == g_eSelObjType || 0 > g_iSelObj || g_vecObjOrigin[(UINT)g_eSelObjType].size() < g_iSelObj)
		return E_FAIL;

	// 클론
	CGameObject* pClone = nullptr;

#pragma region Clone Logic

	switch (IMG_OBJ_TYPE(g_eSelObjType))
	{
	case IMG_OBJ_TYPE::TERRAIN:
	{
		switch (g_iSelObj)
		{
		case 0:
			pClone = CTerrainWorld::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 1:
			pClone = CTerrainIceWorld::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld_Ice", pClone), E_FAIL);
			break;
		case 2:
			pClone = CTerrainIceDungeon::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainDungeon_Ice", pClone), E_FAIL);
			break;
		case 3:
			break;
		default:
			break;
		}
	}
		break;
	case IMG_OBJ_TYPE::ENVIRONMENT:
	{
		switch (g_iSelObj)
		{
		case 0:
			pClone = CHouse1::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"House1", pClone), E_FAIL); // 00.Building - 00.House
			break;
		case 1:
			pClone = CHouse2::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"House2", pClone), E_FAIL);
			break;
		case 2:
			pClone = CHouse3::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"House3", pClone), E_FAIL);
			break;
		case 3:
			pClone = CHouse4::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"House4", pClone), E_FAIL);
			break;
		case 4:
			pClone = CHouse5::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"House5", pClone), E_FAIL);
			break;
		case 5:
			pClone = CHouse6::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"House6", pClone), E_FAIL);
			break;
		case 6:
			pClone = CKingHouse::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"KingHouse", pClone), E_FAIL); 
			break;
		case 7:
			pClone = CSmithy::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Smithy", pClone), E_FAIL); 
			break;
		case 8:
			pClone = CMagicShop::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"MagicShop", pClone), E_FAIL); 
			break;
		case 9:
			pClone = CBush1::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL); // 01.Bush
			break;
		case 10:
			pClone = CBush2::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 11:
			pClone = CBush3::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 12:
			pClone = CBush4::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 13:
			pClone = CBush5::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 14:
			pClone = CBush6::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 15:
			pClone = CBush7::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 16:
			pClone = CBush8::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 17:
			pClone = CBush9::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 18:
			pClone = CBush10::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 19:
			pClone = CBush11::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 20:
			pClone = CMountain_Grass::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL); // 02.Mountain
			break;
		case 21:
			pClone = CMountain_Ice::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 22:
			pClone = CRock1::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL); // 03.Rock
			break;
		case 23:
			pClone = CRock2::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 24:
			pClone = CRock3::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 25:
			pClone = CRock4::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 26:
			pClone = CRock_Pillar1::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL); // 04.Pillar
			break;
		case 27:
			pClone = CRock_Pillar2::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 28:
			pClone = CRock_Pillar3::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 29:
			pClone = CTemple_Pillar1::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 30:
			pClone = CTemple_Pillar2::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 31:
			pClone = CIce_Pillar1::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 32:
			pClone = CDungeon_Grass::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL); // 05.Enterance
			break;
		case 33:
			pClone = CDungeon_Ice::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 34:
			pClone = CDungeon_Temple::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 35:
			pClone = CTower1::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL); // 06.Tower
			break;
		case 36:
			pClone = CTower2::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 37:
			pClone = CTower3::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 38:
			pClone = CChest_Cosmetic::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL); // 07.Chest
			break;
		case 39:
			pClone = CChest_Gold::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		case 40:
			pClone = CChest_Regular::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pClone, E_FAIL);
			FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TerrainWorld", pClone), E_FAIL);
			break;
		}
	}
		break;
	case IMG_OBJ_TYPE::MONSTER:
	{
		switch (g_iSelObj)
		{
		case 0:
		{
		}
		break;
		default:
			break;
		}
	}
		break;
	case IMG_OBJ_TYPE::NPC:
	{

	}
		break;
	case IMG_OBJ_TYPE::ITEM:
	{

	}
		break;
	case IMG_OBJ_TYPE::LINE:
	{

	}
		break;
	case IMG_OBJ_TYPE::TYPEEND:
	{

	}
		break;
	default:
		break;
	}

#pragma endregion
	
		
	NULL_CHECK_RETURN(pClone, E_FAIL);

	// 포지션 세팅
	_vec3 vClonePos = { _vPickPos.x, pClone->Get_Transform()->Get_Info(INFO_POS).y, _vPickPos.z };

	pClone->Get_Transform()->Set_Pos(vClonePos); 

	// 추가
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pClone->Get_Name(), pClone), E_FAIL);

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