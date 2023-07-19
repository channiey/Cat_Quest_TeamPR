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
		{ L"고슴도치나 잡으면서 놀아라.(고슴도치 2마리를 잡아오자.)"}
		}));

	// 사자왕
	m_mapTalkData.insert(make_pair(11, vector<wstring>{
		{ L"고슴도치 2마리를 잡는 것을 보았다."},
		{ L"너는 쓸만하다." },
		{ L"대장장이에게 가봐라." },
		{ L"가기 전에 이걸 받아라.(단검 획득)"}
	}));

	// 사자왕
	m_mapTalkData.insert(make_pair(12, vector<wstring>{
		{ L"잘 돌아왔다."},
		{ L"너는 듀토리얼을 완료했다." },
		{ L"자랑스럽다." }
	}));

	// 메이지
	m_mapTalkData.insert(make_pair(20, vector<wstring>{
		{ L"대장장이가 보내서 왔구나."},
		{ L"이것으로 듀토리얼은 모두 끝났어!" },
		{ L"이걸 받고 사자왕께 돌아가도록 해.(사자왕에게 돌아가자.)" },
		{ L"(지팡이 획득.)"}
	}));

	// 대장장이
	m_mapTalkData.insert(make_pair(30, vector<wstring>{
		{ L"사자왕께서 보내서 왔군." },
		{ L"그럼 다시 마법사에게 가봐." },
		{ L"그리고 이것도 가지고 가.(검 획득)"}
	}));


	//

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
