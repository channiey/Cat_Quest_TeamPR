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
	m_vecTalk.push_back(L"여동생을 찾고 있습니다 혹시 도움이 될만한 단서를 알려 주실 수 있나요?");
	m_vecTalk.push_back(L"외부인에게 마을의 정보를 함부로 줄 수는 없지! 하지만 우리 마을을 돕는다면 생각은 해보지.");
	m_vecTalk.push_back(L"어떤 도움이 필요하신가요?");
	m_vecTalk.push_back(L"자네가 많이 약한 것 같으니 시험을 해봐야겠어, 사원 던전 1의 몬스터를 토벌해주시게나.");
	m_vecTalk.push_back(L"던전을 클리어했어! 사자왕에게 돌아가보자.");

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