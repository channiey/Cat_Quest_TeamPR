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
		{ L"���� ���ڿ��̴�."},
		{ L"�ʴ� �ſ� ���� ���δ�."},
		{ L"����ġ�� �����鼭 ��ƶ�."}
		}));

	m_mapTalkData.insert(make_pair(TALK_ID::TALK_MAGE_1, vector<wstring>{
		{ L"���� ��������."},
		{ L"�ʴ� �ſ� �Ѱ��� ���δ�." },
		{ L"��Ǯ���� ���� ��ƶ�." }
	}));

	m_mapTalkData.insert(make_pair(TALK_ID::TALK_BLACKSMITH_1, vector<wstring>{
		{ L"���� �������̴�."},
		{ L"�ʴ� ���� ���� ���δ�." },
		{ L"Į���̳� �ϸ鼭 ��ƶ�." }
	}));
}

void CTalkMgr::Get_Talk(LPDIRECT3DDEVICE9 pGraphicDev, TALK_ID _eTalkID, OBJ_ID _eObjID)
{
	auto iter = m_mapTalkData.find(_eTalkID);

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
				return;
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
}

void CTalkMgr::Free()
{
}
