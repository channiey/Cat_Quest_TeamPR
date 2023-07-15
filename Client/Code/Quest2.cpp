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
	m_vecTalk.push_back(L"여동생을 찾고 있습니다 혹시 도움이 될만한 단서를 알려 주실 수 있나요?");
	m_vecTalk.push_back(L"외부인에게 마을의 정보를 함부로 줄 수는 없지! 하지만 우리 마을을 돕는다면 생각은 해보지.");
	m_vecTalk.push_back(L"어떤 도움이 필요하신가요?");
	m_vecTalk.push_back(L"자네가 많이 약한 것 같으니 시험을 해봐야겠어, 사원 던전 1의 몬스터를 토벌해주시게나.");
	m_vecTalk.push_back(L"던전을 클리어했어! 사자왕에게 돌아가보자.");

	m_iRewardGold = 100;
}

void CQuest2::Enter()
{
	//cout << "힘의 증명2 : Enter" << endl;
	if (CInputDev::GetInstance()->Key_Down('Z')) {
		m_eLevel = QUEST_LEVEL::QUEST_UPDATE;
	}
;}

void CQuest2::Update()
{
	//cout << "힘의 증명2 : Update" << endl;
	if (CInputDev::GetInstance()->Key_Down('Z')) {
		m_eLevel = QUEST_LEVEL::QUEST_EXIT;
	}
}

void CQuest2::Exit()
{
	//cout << "힘의 증명2 : Exit" << endl;
	m_eLevel = QUEST_LEVEL::QUEST_CLEAR;
}

void CQuest2::Free()
{
}