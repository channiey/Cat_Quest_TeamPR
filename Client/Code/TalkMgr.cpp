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
		{ L"���� ������ ���͵��� ��� �����ϰ� ��������� Ȯ�� �޾ƶ�.(���� ������ ��� ���͸� ��������.)"},
		}));
	// ���ڿ�
	m_mapTalkData.insert(make_pair(11, vector<wstring>{
		{ L"���� ���ܳ��� ���谡 Ʋ������."},
		{ L"�ʴ� ���丮���� �Ϸ��ߴ�." },
		{ L"���� �ʴ� ���� �����ϴ� ������ �����̴�." },
		{ L"�ڶ�������.(������ ȹ��)"}
	}));

	// ����(citizen2)
	m_mapTalkData.insert(make_pair(20, vector<wstring>{
		{ L"��� ���͸� �����ϼ̱���."},
		{ L"�Ǹ��մϴ�." },
		{ L"������ �帮�ڽ��ϴ�.(����Ʈ 1 �Ϸ�, ���� ȹ��.)" }
	}));

	m_mapTalkData.insert(make_pair(21, vector<wstring>{
		{ L"���� ����Ʈ�Դϴ�."},
		{ L"�ٽ� ������ �����ż� ��򰡿� ������ �ִ� ���踦 ã���ø� �˴ϴ�."},
		{ L"���踦 ã�� ���� ���ڿղ� ���ø� �˴ϴ�."}
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
