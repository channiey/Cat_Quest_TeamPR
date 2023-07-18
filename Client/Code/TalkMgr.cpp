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
		{ L"고슴도치나 잡으면서 놀아라.(고슴도치 2마리를 잡아오자.)"}
		}));

	// 사자왕
	m_mapTalkData.insert(make_pair(11, vector<wstring>{
		{ L"고슴도치 2마리를 잡는 것을 보았다."},
		{ L"너는 쓸만하다." },
		{ L"대장장이에게 가봐라." }
	}));

	// 사자왕
	m_mapTalkData.insert(make_pair(12, vector<wstring>{
		{ L"잘 돌아왔다."},
		{ L"너는 듀토리얼을 완료했다." },
		{ L"자랑스럽다." }
	}));

	// 메이지
	m_mapTalkData.insert(make_pair(20, vector<wstring>{
		{ L"나는 메이지다."},
		{ L"너는 매우 한가해 보인다." },
		{ L"수풀에나 들어가서 놀아라.(사자왕에게 돌아가자.)" }
	}));

	// 대장장이
	m_mapTalkData.insert(make_pair(30, vector<wstring>{
		{ L"나는 대장장이다."},
		{ L"너는 뭔가 없어 보인다." },
		{ L"칼질이나 하면서 놀아라.(마법사한테 가보자.)" }
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
