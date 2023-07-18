#include "stdafx.h"
#include "TalkMgr.h"

#include "Export_Function.h"

#include "DialogUI.h"
#include "EventMgr.h"

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

	m_mapTalkData.insert(make_pair(TALK_ID::TALK_KING_1, vector<wstring>{
		{ L"나는 사자왕이다."},
		{ L"너는 매우 약해 보인다."},
		{ L"고슴도치나 잡으면서 놀아라."}
		}));

	m_mapTalkData.insert(make_pair(TALK_ID::TALK_MAGE_1, vector<wstring>{
		{ L"나는 메이지다."},
		{ L"너는 매우 한가해 보인다." },
		{ L"수풀에나 들어가서 놀아라." }
	}));

	m_mapTalkData.insert(make_pair(TALK_ID::TALK_BLACKSMITH_1, vector<wstring>{
		{ L"나는 대장장이다."},
		{ L"너는 뭔가 없어 보인다." },
		{ L"칼질이나 하면서 놀아라." }
	}));
}

void CTalkMgr::Get_Talk(LPDIRECT3DDEVICE9 pGraphicDev, TALK_ID _eTalkID, OBJ_ID _eObjID)
{
	auto iter = m_mapTalkData.find(_eTalkID);

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
				return;
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
}

void CTalkMgr::Free()
{
}
