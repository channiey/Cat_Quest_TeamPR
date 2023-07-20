#include "stdafx.h"
#include "TalkMgr.h"

#include "Export_Function.h"

#include "DialogUI.h"
#include "EventMgr.h"
#include "QuestMgr.h"

#include "Npc_King.h"
#include "Npc_Mage.h"
#include "Npc_BlackSmith.h"
#include "Npc_Soldier.h"
#include "Npc_Citizen1.h"
#include "Npc_Citizen2.h"

IMPLEMENT_SINGLETON(CTalkMgr)

CTalkMgr::CTalkMgr()
{
}

CTalkMgr::~CTalkMgr()
{
}

void CTalkMgr::Init()
{
	m_iTalkIndex = 0;

	// 듀토리얼 퀘스트
	// 사자왕
	m_mapTalkData.insert(make_pair(10, vector<wstring>{
		{ L"나는 사자왕이다."},
		{ L"너는 매우 약해 보인다."},
		{ L"듀토리얼이 시급해 보인다."},
		{ L"습지 던전의 몬스터들을 모두 소탕하고 시험관에게 확인 받아라.(습지 던전의 모든 몬스터를 소탕하자.)"},
		}));
	// 사자왕
	m_mapTalkData.insert(make_pair(11, vector<wstring>{
		{ L"내가 숨겨놓은 열쇠가 틀림없군."},
		{ L"너는 듀토리얼을 완료했다." },
		{ L"이제 너는 내가 인정하는 강인한 길고양이다." },
		{ L"자랑스럽다.(스태프 획득)"}
	}));

	// 교관(citizen2)
	m_mapTalkData.insert(make_pair(20, vector<wstring>{
		{ L"모든 몬스터를 소탕하셨군요."},
		{ L"훌륭합니다." },
		{ L"보상을 드리겠습니다.(퀘스트 1 완료, 무기 획득.)" }
	}));

	m_mapTalkData.insert(make_pair(21, vector<wstring>{
		{ L"다음 퀘스트입니다."},
		{ L"다시 밖으로 나가셔서 어딘가에 숨겨져 있는 열쇠를 찾으시면 됩니다."},
		{ L"열쇠를 찾고 나면 사자왕께 가시면 됩니다."}
	}));
	//

	m_bInit = true;
}

_bool CTalkMgr::Get_Talk(LPDIRECT3DDEVICE9 pGraphicDev, _int _iTalkID, OBJ_ID _eObjID)
{
	auto iter = m_mapTalkData.find(_iTalkID);

	if (&iter)
	{
		if (CInputDev::GetInstance()->Key_Down('E'))
		{
			// 마지막 대사까지 다 출력했다면
			if (m_iTalkIndex >= iter->second.size())
			{
				CEventMgr::GetInstance()->Delete_Obj
				(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"));
				m_iTalkIndex = 0;
				return true;
			}

			if (m_iTalkIndex < iter->second.size())
			{
				// 이미 있으면 지워라
				if (CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"))
				{
					CEventMgr::GetInstance()->Delete_Obj
					(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"));
				}
				// 생성
				CEventMgr::GetInstance()->Add_Obj(L"DialogUI", CDialogUI::Create(pGraphicDev,
					_eObjID, iter->second[m_iTalkIndex]));
				++m_iTalkIndex;
			}
		}
	}
	return false;
}

void CTalkMgr::Free()
{
}
