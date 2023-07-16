#include "stdafx.h"
#include "Quest2.h"

#include "Export_Function.h"

#include "Npc_King.h"
#include "Npc_Mage.h"
#include "Npc_BlackSmith.h"

CQuest2::CQuest2(LPDIRECT3DDEVICE9 pGraphicDev)
	: CQuest(pGraphicDev)
{
	Init();
}

CQuest2::~CQuest2()
{
}

void CQuest2::Init()
{
	m_vecTalk.push_back(L"�������� ã�� �ֽ��ϴ� Ȥ�� ������ �ɸ��� �ܼ��� �˷� �ֽ� �� �ֳ���?");
	m_vecTalk.push_back(L"�ܺ��ο��� ������ ������ �Ժη� �� ���� ����! ������ �츮 ������ ���´ٸ� ������ �غ���.");
	m_vecTalk.push_back(L"� ������ �ʿ��ϽŰ���?");
	m_vecTalk.push_back(L"�ڳװ� ���� ���� �� ������ ������ �غ��߰ھ�, ��� ���� 1�� ���͸� ������ֽðԳ�.");
	m_vecTalk.push_back(L"������ Ŭ�����߾�! ���ڿտ��� ���ư�����.");

	m_iRewardGold = 100;
}

void CQuest2::Enter()
{
	if (!m_bAdd)
	{
		m_vecNpc.push_back(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage"));
		m_vecNpc.push_back(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"));
		m_bAdd = true;
	}

	// cout << "���� ����2 : Enter" << endl;
	if (CInputDev::GetInstance()->Key_Down('Z')) {
		//dynamic_cast<CNpc_Mage*>(m_vecNpc[0])->Set_IsReadyTalk(true);
		//m_iLevel += 1;
		m_eProgress = QUEST_PROGRESS::QUEST_UPDATE;
	}
;}

void CQuest2::Update()
{
	// cout << "���� ����2 : Update" << endl;
	if (CInputDev::GetInstance()->Key_Down('Z')) {
		//dynamic_cast<CNpc_Mage*>(m_vecNpc[0])->Set_IsReadyTalk(true);
		//m_iLevel += 1;
		m_eProgress = QUEST_PROGRESS::QUEST_EXIT;
	}
	//switch (m_iLevel)
	//{
	//case 1:
	//	cout << "���� ����2 : Update1" << endl;
	//	dynamic_cast<CNpc_Mage*>(m_vecNpc[0])->OnCollision_Stay(m_pPlayer);
	//	dynamic_cast<CNpc_BlackSmith*>(m_vecNpc[1])->OnCollision_Stay(m_pPlayer);
	//	break;
	//case 2:
	//	cout << "���� ����2 : Update2" << endl;
	//	dynamic_cast<CNpc_BlackSmith*>(m_vecNpc[1])->OnCollision_Stay(m_pPlayer);
	//	break;
	//case 3:
	//	m_eProgress = QUEST_PROGRESS::QUEST_EXIT;
	//	break;
	//}
}

void CQuest2::Exit()
{
	// cout << "���� ����2 : Exit" << endl;

	dynamic_cast<CNpc*>
		(CManagement::GetInstance()->
			Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen2"))->Set_IsReadyQuest(true);



	m_eProgress = QUEST_PROGRESS::QUEST_CLEAR;
}

void CQuest2::Free()
{
}