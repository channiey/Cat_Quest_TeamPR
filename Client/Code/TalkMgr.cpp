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

	// Quest1 : ���������� ��Ź
	// ��������
	m_mapTalkData.insert(make_pair(100, vector<wstring>{
		{ L"�ȳ�! �ϰ� �巡���� óġ�ϱ� ���� �Դٴ� ����̱���!"},
		{ L"�츮 ������ �� �Ծ�!"},
		{ L"�巡�ﵵ �߿������� ���� ����ġ�� ������ �츮���� ���ظ� ���� �־�."},
		{ L"�� �Ʒ��ʿ� �ִ� ����ġ�� �� ������� 5������ óġ���ָ� ���ھ�!"},
		{ L"(����ġ�� 5������ ��� ����."}
		}));
	// ��������
	m_mapTalkData.insert(make_pair(101, vector<wstring>{
		{ L"����ġ 5������ ��ұ���!"},
		{ L"�̰ɷ� �༮�鵵 ����ó�� Ȱ��ġ�� �� �Ұž�." },
		{ L"����! �̰� �츮���� ���� �ִ� ��ų���ε� ������ �� ���Ἥ ���̾�." },
		{ L"�ϰ� �������ָ� �巡���� óġ�ϴ� �� ������ �ǰ���!"},
		{ L"(��ų�� �����.)"}
	}));

	// Quest2 : ���� ����
	// ��������
	m_mapTalkData.insert(make_pair(200, vector<wstring>{
		{ L"������ ������ ���� ���͵��� ��� ��������!"}
	}));

	// ��Ƽ��(1)
	m_mapTalkData.insert(make_pair(201, vector<wstring>{
		{L"���͸� ��� �����ϼ̳׿�!"},
		{L"�̰����� ��������� � ������� ��ǰ�ϱ��? �̷��� ������ �ִ��󱸿�."},
		{L"�������� �� ������ �� �� ������ ����������!"},
		{L"���� �ڽ�Ƭ, ����Ʈ�� ȹ��!"}
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
