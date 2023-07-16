#include "stdafx.h"
#include "Quest1.h"

#include "Export_Function.h"

#include "Npc.h"
#include "Npc_Mage.h"
#include "Npc_BlackSmith.h"

#include "DialogUI.h"

CQuest1::CQuest1(LPDIRECT3DDEVICE9 pGraphicDev)
	: CQuest(pGraphicDev)
{
	Init();
}

CQuest1::~CQuest1()
{
}

void CQuest1::Init()
{
	m_vecTalk.push_back(L"�������� ã�� �ֽ��ϴ� Ȥ�� ������ �ɸ��� �ܼ��� �˷� �ֽ� �� �ֳ���?");
	m_vecTalk.push_back(L"�ܺ��ο��� ������ ������ �Ժη� �� ���� ����! ������ �츮 ������ ���´ٸ� ������ �غ���.");
	m_vecTalk.push_back(L"� ������ �ʿ��ϽŰ���?");
	m_vecTalk.push_back(L"�ڳװ� ���� ���� �� ������ ������ �غ��߰ھ�, ��� ���� 1�� ���͸� ������ֽðԳ�.");

	m_vecTalk.push_back(L"������ Ŭ�����߾�! ���ڿտ��� ���ư�����.");

	m_iRewardGold = 100;	
}

void CQuest1::Enter()
{
	if (!m_bAdd)
	{
		m_vecNpc.push_back(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage"));
		m_vecNpc.push_back(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"));
		m_bAdd = true;
	}

	// CEventMgr::GetInstance()->Add_Obj(L"DialogUI", CDialogUI::Create(m_pGraphicDev, OBJ_ID::NPC_BLACKSMITH, m_vecTalk[0]));
	// CEventMgr::GetInstance()->Add_Obj(L"DialogUI", CDialogUI::Create(m_pGraphicDev, OBJ_ID::NPC_BLACKSMITH, m_vecTalk[1]));
	// CEventMgr::GetInstance()->Add_Obj(L"DialogUI", CDialogUI::Create(m_pGraphicDev, OBJ_ID::NPC_BLACKSMITH, m_vecTalk[2]));
	// CEventMgr::GetInstance()->Add_Obj(L"DialogUI", CDialogUI::Create(m_pGraphicDev,OBJ_ID::NPC_BLACKSMITH, m_vecTalk[3]));


	// cout << "���� ����1 : Enter" << endl;
	if (CInputDev::GetInstance()->Key_Down('Z')) {
		//dynamic_cast<CNpc_Mage*>(m_vecNpc[0])->Set_IsReadyTalk(true);
		//m_iLevel += 1;
		m_eProgress = QUEST_PROGRESS::QUEST_UPDATE; 
	}
}

void CQuest1::Update()
{
	// cout << "���� ����1 : Update" << endl;
	if (CInputDev::GetInstance()->Key_Down('Z')) {
		//dynamic_cast<CNpc_Mage*>(m_vecNpc[0])->Set_IsReadyTalk(true);
		//m_iLevel += 1;
		m_eProgress = QUEST_PROGRESS::QUEST_EXIT;
	}

	//switch (m_iLevel)
	//{
	//case 1:
	//	cout << "���� ����1 : Update1" << endl;
	//	dynamic_cast<CNpc_Mage*>(m_vecNpc[0])->OnCollision_Stay(m_pPlayer);
	//	break;
	//case 2:
	//	cout << "���� ����1 : Update2" << endl;
	//	dynamic_cast<CNpc_BlackSmith*>(m_vecNpc[1])->Set_IsReadyTalk(true);
	//	dynamic_cast<CNpc_BlackSmith*>(m_vecNpc[1])->OnCollision_Stay(m_pPlayer);
	//	break;
	//case 3:
	//	dynamic_cast<CNpc_BlackSmith*>(m_vecNpc[1])->Set_IsReadyTalk(false);
	//	m_eProgress = QUEST_PROGRESS::QUEST_EXIT;
	//	break;
	//}

}

void CQuest1::Exit()
{
	// cout << "���� ����1 : Exit" << endl;

	dynamic_cast<CNpc*>
		(CManagement::GetInstance()->
			Get_GameObject(OBJ_TYPE::NPC, L"Npc_King"))->Set_NextQuest();
	dynamic_cast<CNpc*>
		(CManagement::GetInstance()->
			Get_GameObject(OBJ_TYPE::NPC, L"Npc_King"))->Set_IsReadyQuest(true);
	dynamic_cast<CNpc*>
		(CManagement::GetInstance()->
			Get_GameObject(OBJ_TYPE::NPC, L"Npc_King"))->Set_IsReadyTalk(true);

	m_eProgress = QUEST_PROGRESS::QUEST_CLEAR;
}

void CQuest1::Free()
{
}