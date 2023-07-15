#include "stdafx.h"
#include "Quest3.h"

#include "Export_Function.h"

#include "Npc_King.h"

CQuest3::CQuest3()
{
	Init();
}

CQuest3::~CQuest3()
{
}

void CQuest3::Init()
{
	m_vecTalk.push_back(L"사자왕에게 들었는데 얼마 전 바다에서 특이한 물건을 주웠다고 해서 왔습니다.");
	m_vecTalk.push_back(L"그게 왜 궁금하신거죠? 다람쥐들이 곡식을 훔쳐먹어서 그거 잡느라 바쁜데.");
	m_vecTalk.push_back(L"우리가 도와드릴게요.");
	m_vecTalk.push_back(L"그럼 다람쥐 10마리만 잡아 주세요.");

	m_vecTalk.push_back(L"나쁜 다람쥐를 모두 잡았습니다.");
	m_vecTalk.push_back(L"아이구야 빠르기도 하셔라 대단하시네요.");
	m_vecTalk.push_back(L"혹시 바다에서 주우셨다는 물건이 뭔지 볼 수 있을까요? 여동생을 찾는데 단서가 될까 해서요…...");
	m_vecTalk.push_back(L"뭐 특별할건 아닌데 난 뭔지도 모르겠고 가져가셔.");
	//                                           스킬 획득 
	m_vecTalk.push_back(L"그나저나 드라코스 때문에 이번 농사도 다 망쳤네.");
	m_vecTalk.push_back(L"드라코스가 누구죠?");
	m_vecTalk.push_back(L"우리 마을을 위협하는 악의 무리들이지 온갖 나쁜 짓들은 다 하니 그들이 납치했을 수도 있겠네요.");

	m_iRewardGold = 100;

	m_eLevel = QUEST_LEVEL::QUEST_ENTER;
}

void CQuest3::Enter()
{
	//cout << "도둑 잡기 : Enter" << endl;
	if (CInputDev::GetInstance()->Key_Down('Z')) {
		m_eLevel = QUEST_LEVEL::QUEST_UPDATE;
	}
}

void CQuest3::Update()
{
	//cout << "도둑 잡기 : Update" << endl;
	if (CInputDev::GetInstance()->Key_Down('Z')) {
		m_eLevel = QUEST_LEVEL::QUEST_EXIT;
	}
}

void CQuest3::Exit()
{
	//cout << "도둑 잡기 : Exit" << endl;
	m_eLevel = QUEST_LEVEL::QUEST_CLEAR;
}

void CQuest3::Free()
{
}