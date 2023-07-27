#include "stdafx.h"
#include "Quest3.h"

#include "Export_Function.h"

#include "Player.h"
#include "TalkMgr.h"
#include "Management.h"
#include "GraphicDev.h"
#include "IndicatorUI.h"

#include "Npc_BlackSmith.h"
#include "Npc_Soldier.h"
#include "Npc_Mage.h"
// ����� ���� ���߿��� ��Ż�� �߰��ؾ� �Ѵ�.
#include "Tower2.h"

#include "MageWeapon.h"
#include "Skill_Player_Ice.h"
#include "Skill_Player_Beam.h"
#include "Key.h"

#include "MiniGameMgr_Jump.h"

CQuest3::CQuest3(wstring _QuestName, LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
{
	m_strQuestName = _QuestName;
	Init(m_pGraphicDev, _pPlayer);
}

CQuest3::~CQuest3()
{
	if (m_pKey)
	{
		Safe_Release(m_pKey);
	}
}

void CQuest3::Init(LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
{
	m_pPlayer = _pPlayer;

	// Ice Skill
	CSkill* pSkill = CSkill_Player_Ice::Create(m_pGraphicDev, m_pPlayer);
	CEventMgr::GetInstance()->Add_Obj(L"�ǲ� �ڲ���", pSkill);
	m_vSkillList.push_back(pSkill);
	pSkill->Set_Maintain(true);

	// Beam Skill
	pSkill = CSkill_Player_Beam::Create(m_pGraphicDev, m_pPlayer);
	CEventMgr::GetInstance()->Add_Obj(L"������ġ", pSkill);
	m_vSkillList.push_back(pSkill);
	pSkill->Set_Maintain(true);


	// Item Mage
	CGameObject* pGameObject = CMageWeapon::Create(m_pGraphicDev);
	CEventMgr::GetInstance()->Add_Obj(L"������ ������", pGameObject);
	m_vItemList.push_back(pGameObject);
	pGameObject->Set_Maintain(true);

	m_tQuestContent.push_back({ L"1.���� ������.", false });

	m_bCreateKey = false;
	m_pKey = nullptr;
}

_bool CQuest3::Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble)
{

	// ����
	// ����Ʈ �ܰ谡 4�ܰ��̰� ���忡 Ű�� ������ �ȵ��� �� + (�ߺ� ���� ����)
	if (m_iLevel == 3 && !m_bCreateKey &&
		CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
	{
		m_pKey = CKey::Create(pGraphicDev);
		CEventMgr::GetInstance()->Add_Obj(L"Item_Key", m_pKey);
		m_bCreateKey = true;
	}
	// �� �̵��� m_bCreateKey false�� ����. ���� �˾Ƽ� ������.
	if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() != SCENE_TYPE::WORLD)
	{
		m_bCreateKey = false;
	}
	///////////////////////////////////////


	switch (m_iLevel)
	{
	case 0: // �������̿� ��ȭ(���� ķ �̺�Ʈ)
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::DUNGEON_SWAMP)
		{
			if (!*_IsAble)
			{
				dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
					dynamic_cast<CTower2*>(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::ENVIRONMENT, L"Tower2")));
				*_IsAble = true;
			}
		}

		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc�� ���� �Ѵٸ�
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith") != nullptr))
			{
				if (!*_IsAble)
				{
					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith")));
					*_IsAble = true;
				}

				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"))->Get_IsCol())
				{
					_vec3 vPlayerPos = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player")->Get_Transform()->Get_Info(INFO_POS);
					_vec3 vTargetPos = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::NPC, L"Npc_Soldier")->Get_Transform()->Get_Info(INFO_POS);

					if (CTalkMgr::GetInstance()->Get_CamTalk(
						pGraphicDev, 300, OBJ_ID::NPC_BLACKSMITH, 3, vPlayerPos, vTargetPos))
					{
						m_iLevel += 1;
						*_IsAble = false;
						break;
					}
				}
			}
		}
		break;
	case 1: // ���ΰ� ��ȭ
		m_bShowQuestView = true;
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc�� ���� �Ѵٸ�
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_Soldier") != nullptr))
			{
				// �ε������� ����
				if (!*_IsAble)
				{
					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_Soldier")));
					*_IsAble = true;
				}
				// ��ȭ �� ���� �ܰ�
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_Soldier"))->Get_IsCol())
				{
					_vec3 vPlayerPos = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player")->Get_Transform()->Get_Info(INFO_POS);
					_vec3 vTargetPos = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage")->Get_Transform()->Get_Info(INFO_POS);

					if (CTalkMgr::GetInstance()->Get_CamTalk(
						pGraphicDev, 310, OBJ_ID::NPC_SOLLIDER, 2, vPlayerPos, vTargetPos))
					{
						m_tQuestContent[0].m_bClear = true;
						m_tQuestContent.push_back({ L"2.������ ����Ͽ�\n������ ������.", false });
						m_iLevel += 1;
						*_IsAble = false;
						CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_TOP_TO_BACK);
						CMiniGameMgr_Jump::GetInstance()->Start_MiniGame(); // �̴ϰ��� ����
						break;
					}
				}
			}
		}
		break;
	case 2: // �����翡�� ���ϱ�
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc�� ���� �Ѵٸ�
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage") != nullptr))
			{
				// �ε������� ����
				if (!*_IsAble)
				{
					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage")));
					*_IsAble = true;
				}
				// ��ȭ �� ���� �ܰ�
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage"))->Get_IsCol())
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 320, OBJ_ID::NPC_MAGE))
					{
						m_tQuestContent[1].m_bClear = true;
						m_tQuestContent.push_back({ L"3.�������� ���� ã���ֱ�.", false });
						m_iLevel += 1;
						*_IsAble = false;
						break;
					}
				}
			}
		}
		break;
	case 3: // ���� ã��
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			if (m_bCreateKey)
			{
				if (dynamic_cast<CKey*>(m_pKey)->Get_IsCol())
				{
					dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Set_HaveKey(true);
					m_iLevel += 1;
					break;
				}
			}
		}	

		break;
	case 4:
		// �����翡�� ���� ������ �ֱ�
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage") != nullptr))
			{
				if (!*_IsAble)
				{
					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage")));
					*_IsAble = true;
				}
		
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage"))->Get_IsCol() &&
					dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Get_HaveKey() >= 1)
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 321, OBJ_ID::NPC_MAGE)) {
						dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Set_HaveKey(false);
						// dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Item(m_vItemList[0]);
						m_iLevel += 1;
						*_IsAble = false;
						break;
					}
				}
		
			}
		}
		break;
	case 5: // �������̿��� ����
		m_tQuestContent[2].m_bClear = true;

		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc�� ���� �Ѵٸ�
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith") != nullptr))
			{
				// �ε������� ����
				if (!*_IsAble)
				{
					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith")));
					*_IsAble = true;
				}
				// ��ȭ �� ���� �ܰ�
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"))->Get_IsCol())
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 301, OBJ_ID::NPC_BLACKSMITH))
					{
						m_iLevel += 1;
						dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Skill(
							m_vSkillList[0]);
						dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Skill(
							m_vSkillList[1]);
						dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Item(
							m_vItemList[0]);

						*_IsAble = false;
						break;
					}
				}
			}
		}

		break;
	case 6:
		m_iLevel = 99;
		*_IsAble = false;
		m_bShowQuestView = false;
		return true;
		break;
	}

	return false;
}
