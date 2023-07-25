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

	// Quest1 : 대장장이의 부탁
	// 대장장이
	m_mapTalkData.insert(make_pair(100, vector<wstring>{
		{ L"안녕! 니가 드래곤을 처치하기 위해 왔다는 고양이구나!"},
		{ L"우리 마을에 잘 왔어!"},
		{ L"드래곤도 중요하지만 요즘 고슴도치들 때문에 우리들이 피해를 보고 있어."},
		{ L"저 아래쪽에 있는 고슴도치들 중 본보기로 5마리만 처치해주면 좋겠어!"},
		{ L"(고슴도치를 5마리만 잡고 오자."}
		}));
	// 대장장이
	m_mapTalkData.insert(make_pair(101, vector<wstring>{
		{ L"고슴도치 5마리를 잡았구나!"},
		{ L"이걸로 녀석들도 이전처럼 활개치진 못 할거야." },
		{ L"고마워! 이건 우리집에 대대로 있던 스킬북인데 어차피 난 못써서 말이야." },
		{ L"니가 가져가주면 드래곤을 처치하는 데 도움이 되겠지!"},
		{ L"(스킬을 얻었다.)"}
	}));

	// Quest2 : 던전 정리
	// 대장장이
	m_mapTalkData.insert(make_pair(200, vector<wstring>{
		{ L"다음은 던전에 들어가서 몬스터들을 모두 소탕해줘!"}
	}));

	// 시티즌(1)
	m_mapTalkData.insert(make_pair(201, vector<wstring>{
		{L"몬스터를 모두 소탕하셨네요!"},
		{L"이곳에서 사라져버린 어떤 고양이의 유품일까요? 이런게 떨어져 있더라구요."},
		{L"용사님한테 더 도움이 될 거 같으니 가져가세요!"},
		{L"닌자 코스튬, 라이트냥 획득!"}
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
