#include "stdafx.h"
#include "Quest2.h"

#include "Export_Function.h"

#include "Npc_King.h"

CQuest2::CQuest2()
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
	//cout << "���� ����2 : Enter" << endl;
	if (CInputDev::GetInstance()->Key_Down('Z')) {
		m_eLevel = QUEST_LEVEL::QUEST_UPDATE;
	}
;}

void CQuest2::Update()
{
	//cout << "���� ����2 : Update" << endl;
	if (CInputDev::GetInstance()->Key_Down('Z')) {
		m_eLevel = QUEST_LEVEL::QUEST_EXIT;
	}
}

void CQuest2::Exit()
{
	//cout << "���� ����2 : Exit" << endl;
	m_eLevel = QUEST_LEVEL::QUEST_CLEAR;
}

void CQuest2::Free()
{
}