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

	// ���丮�� ����Ʈ
	// ���ڿ�
	m_mapTalkData.insert(make_pair(10, vector<wstring>{
		{ L"���� ���ڿ��̴�."},
		{ L"�ʴ� �ſ� ���� ���δ�."},
		{ L"���丮���� �ñ��� ���δ�."},
		{ L"����ġ�� �����鼭 ��ƶ�.(����ġ 2������ ��ƿ���.)"}
		}));

	// ���ڿ�
	m_mapTalkData.insert(make_pair(11, vector<wstring>{
		{ L"����ġ 2������ ��� ���� ���Ҵ�."},
		{ L"�ʴ� �����ϴ�." },
		{ L"�������̿��� ������." },
		{ L"���� ���� �̰� �޾ƶ�.(�ܰ� ȹ��)"}
	}));

	// ���ڿ�
	m_mapTalkData.insert(make_pair(12, vector<wstring>{
		{ L"�� ���ƿԴ�."},
		{ L"�ʴ� ���丮���� �Ϸ��ߴ�." },
		{ L"�ڶ�������." }
	}));

	// ������
	m_mapTalkData.insert(make_pair(20, vector<wstring>{
		{ L"�������̰� ������ �Ա���."},
		{ L"�̰����� ���丮���� ��� ������!" },
		{ L"�̰� �ް� ���ڿղ� ���ư����� ��.(���ڿտ��� ���ư���.)" },
		{ L"(������ ȹ��.)"}
	}));

	// ��������
	m_mapTalkData.insert(make_pair(30, vector<wstring>{
		{ L"���ڿղ��� ������ �Ա�." },
		{ L"�׷� �ٽ� �����翡�� ����." },
		{ L"�׸��� �̰͵� ������ ��.(�� ȹ��)"}
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
			// ������ ������ �� ����ߴٸ�
			if (m_iTalkIndex >= iter->second.size())
			{
				CEventMgr::GetInstance()->Delete_Obj
				(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"));
				m_iTalkIndex = 0;
				return true;
			}

			if (m_iTalkIndex < iter->second.size())
			{
				// �̹� ������ ������
				if (CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"))
				{
					CEventMgr::GetInstance()->Delete_Obj
					(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"));
				}
				// ����
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
