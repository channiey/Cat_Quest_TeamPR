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
	m_vecTalk.push_back(L"여동생을 찾고 있습니다 혹시 도움이 될만한 단서를 알려 주실 수 있나요?");
	m_vecTalk.push_back(L"외부인에게 마을의 정보를 함부로 줄 수는 없지! 하지만 우리 마을을 돕는다면 생각은 해보지.");
	m_vecTalk.push_back(L"어떤 도움이 필요하신가요?");
	m_vecTalk.push_back(L"자네가 많이 약한 것 같으니 시험을 해봐야겠어, 사원 던전 1의 몬스터를 토벌해주시게나.");
	m_vecTalk.push_back(L"던전을 클리어했어! 사자왕에게 돌아가보자.");

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

	// cout << "힘의 증명2 : Enter" << endl;
	if (CInputDev::GetInstance()->Key_Down('Z')) {
		//dynamic_cast<CNpc_Mage*>(m_vecNpc[0])->Set_IsReadyTalk(true);
		//m_iLevel += 1;
		m_eProgress = QUEST_PROGRESS::QUEST_UPDATE;
	}
;}

void CQuest2::Update()
{
	// cout << "힘의 증명2 : Update" << endl;
	if (CInputDev::GetInstance()->Key_Down('Z')) {
		//dynamic_cast<CNpc_Mage*>(m_vecNpc[0])->Set_IsReadyTalk(true);
		//m_iLevel += 1;
		m_eProgress = QUEST_PROGRESS::QUEST_EXIT;
	}
	//switch (m_iLevel)
	//{
	//case 1:
	//	cout << "힘의 증명2 : Update1" << endl;
	//	dynamic_cast<CNpc_Mage*>(m_vecNpc[0])->OnCollision_Stay(m_pPlayer);
	//	dynamic_cast<CNpc_BlackSmith*>(m_vecNpc[1])->OnCollision_Stay(m_pPlayer);
	//	break;
	//case 2:
	//	cout << "힘의 증명2 : Update2" << endl;
	//	dynamic_cast<CNpc_BlackSmith*>(m_vecNpc[1])->OnCollision_Stay(m_pPlayer);
	//	break;
	//case 3:
	//	m_eProgress = QUEST_PROGRESS::QUEST_EXIT;
	//	break;
	//}
}

void CQuest2::Exit()
{
	// cout << "힘의 증명2 : Exit" << endl;

	dynamic_cast<CNpc*>
		(CManagement::GetInstance()->
			Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen2"))->Set_IsReadyQuest(true);



	m_eProgress = QUEST_PROGRESS::QUEST_CLEAR;
}

void CQuest2::Free()
{
}