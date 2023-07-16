#include "stdafx.h"
#include "Quest4.h"

#include "Export_Function.h"

#include "Npc_King.h"

CQuest4::CQuest4(LPDIRECT3DDEVICE9 pGraphicDev)
	: CQuest(pGraphicDev)
{
	Init();
}

CQuest4::~CQuest4()
{
}

void CQuest4::Init()
{
	m_vecTalk.push_back(L"�������� ã�� �ֽ��ϴ� Ȥ�� ������ �ɸ��� �ܼ��� �˷� �ֽ� �� �ֳ���?");
	m_vecTalk.push_back(L"�ܺ��ο��� ������ ������ �Ժη� �� ���� ����! ������ �츮 ������ ���´ٸ� ������ �غ���.");
	m_vecTalk.push_back(L"� ������ �ʿ��ϽŰ���?");
	m_vecTalk.push_back(L"�ڳװ� ���� ���� �� ������ ������ �غ��߰ھ�, ��� ���� 1�� ���͸� ������ֽðԳ�.");
	m_vecTalk.push_back(L"������ Ŭ�����߾�! ���ڿտ��� ���ư�����.");

	m_iRewardGold = 100;

	m_eProgress = QUEST_PROGRESS::QUEST_ENTER;
}

void CQuest4::Enter()
{
	int i = 0;
}

void CQuest4::Update()
{
	int i = 0;
}

void CQuest4::Exit()
{
	int i = 0;
}

void CQuest4::Free()
{
}