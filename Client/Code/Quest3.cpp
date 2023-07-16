#include "stdafx.h"
#include "Quest3.h"

#include "Export_Function.h"

#include "Npc.h"

CQuest3::CQuest3(LPDIRECT3DDEVICE9 pGraphicDev)
	: CQuest(pGraphicDev)
{
	Init();
}

CQuest3::~CQuest3()
{
}

void CQuest3::Init()
{
	m_vecTalk.push_back(L"���ڿտ��� ����µ� �� �� �ٴٿ��� Ư���� ������ �ֿ��ٰ� �ؼ� �Խ��ϴ�.");
	m_vecTalk.push_back(L"�װ� �� �ñ��ϽŰ���? �ٶ������ ����� ���ĸԾ �װ� ����� �ٻ۵�.");
	m_vecTalk.push_back(L"�츮�� ���͵帱�Կ�.");
	m_vecTalk.push_back(L"�׷� �ٶ��� 10������ ��� �ּ���.");

	m_vecTalk.push_back(L"���� �ٶ��㸦 ��� ��ҽ��ϴ�.");
	m_vecTalk.push_back(L"���̱��� �����⵵ �ϼŶ� ����Ͻó׿�.");
	m_vecTalk.push_back(L"Ȥ�� �ٴٿ��� �ֿ�̴ٴ� ������ ���� �� �� �������? �������� ã�µ� �ܼ��� �ɱ� �ؼ��䡦...");
	m_vecTalk.push_back(L"�� Ư���Ұ� �ƴѵ� �� ������ �𸣰ڰ� ��������.");
	//                                           ��ų ȹ�� 
	m_vecTalk.push_back(L"�׳����� ����ڽ� ������ �̹� ��絵 �� ���Ƴ�.");
	m_vecTalk.push_back(L"����ڽ��� ������?");
	m_vecTalk.push_back(L"�츮 ������ �����ϴ� ���� ���������� �°� ���� ������ �� �ϴ� �׵��� ��ġ���� ���� �ְڳ׿�.");

	m_iRewardGold = 100;

	m_eProgress = QUEST_PROGRESS::QUEST_ENTER;
}

void CQuest3::Enter()
{
	if (!m_bAdd)
	{
		m_vecNpc.push_back(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage"));
		m_vecNpc.push_back(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"));
		m_bAdd = true;
	}


	// cout << "���� ��� : Enter" << endl;
	if (CInputDev::GetInstance()->Key_Down('Z')) {
		//dynamic_cast<CNpc*>(m_vecNpc[0])->Set_IsReadyTalk(true);
		//m_iLevel += 1;
		m_eProgress = QUEST_PROGRESS::QUEST_UPDATE;
	}
}

void CQuest3::Update()
{
	// cout << "���� ��� : Update" << endl;

	if (CInputDev::GetInstance()->Key_Down('Z')) {
		m_eProgress = QUEST_PROGRESS::QUEST_EXIT;
	}
}

void CQuest3::Exit()
{
	// cout << "���� ��� : Update" << endl;
	if (CInputDev::GetInstance()->Key_Down('Z')) {
		m_eProgress = QUEST_PROGRESS::QUEST_CLEAR;
	}
}

void CQuest3::Free()
{
}