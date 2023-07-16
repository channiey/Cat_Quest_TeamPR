#include "stdafx.h"
#include "Quest1.h"

#include "Export_Function.h"

#include "Npc.h"

CQuest1::CQuest1()
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
	cout << "���� ����1 : Enter" << endl;
	if (CInputDev::GetInstance()->Key_Down('Z')) {
		m_eProgress = QUEST_PROGRESS::QUEST_UPDATE;
	}
}

void CQuest1::Update()
{
	cout << "���� ����1 : Update" << endl;
	if (CInputDev::GetInstance()->Key_Down('Z')) {
		m_eProgress = QUEST_PROGRESS::QUEST_EXIT;
	}
}

void CQuest1::Exit()
{
	cout << "���� ����1 : Exit" << endl;
	dynamic_cast<CNpc*>
		(CManagement::GetInstance()->
			Get_GameObject(OBJ_TYPE::NPC, L"Npc_King"))->Set_NextQuest();
	dynamic_cast<CNpc*>
		(CManagement::GetInstance()->
			Get_GameObject(OBJ_TYPE::NPC, L"Npc_King"))->Set_IsReadyQuest(true);
	m_eProgress = QUEST_PROGRESS::QUEST_CLEAR;
}

void CQuest1::Free()
{
}