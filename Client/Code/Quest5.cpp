#include "stdafx.h"
#include "Quest5.h"

#include "Export_Function.h"

#include "Npc_King.h"

CQuest5::CQuest5()
{
	Init();
}

CQuest5::~CQuest5()
{
}

void CQuest5::Init()
{
	m_vecTalk.push_back(L"�������� ã�� �ֽ��ϴ� Ȥ�� ������ �ɸ��� �ܼ��� �˷� �ֽ� �� �ֳ���?");
	m_vecTalk.push_back(L"�ܺ��ο��� ������ ������ �Ժη� �� ���� ����! ������ �츮 ������ ���´ٸ� ������ �غ���.");
	m_vecTalk.push_back(L"� ������ �ʿ��ϽŰ���?");
	m_vecTalk.push_back(L"�ڳװ� ���� ���� �� ������ ������ �غ��߰ھ�, ��� ���� 1�� ���͸� ������ֽðԳ�.");
	m_vecTalk.push_back(L"������ Ŭ�����߾�! ���ڿտ��� ���ư�����.");

	m_iRewardGold = 100;

	m_eLevel = QUEST_LEVEL::QUEST_ENTER;
}

void CQuest5::Enter()
{
	int i = 0;
}

void CQuest5::Update()
{
	int i = 0;
}

void CQuest5::Exit()
{
	int i = 0;
}

void CQuest5::Free()
{
}