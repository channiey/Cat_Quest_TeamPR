#include "Inventory.h"
#include "Export_Function.h"

#include "Item_Weapon.h"
#include "WarriorWeapon.h"
#include "MageWeapon.h"
#include "NinjaWeapon.h"
#include "Player.h"

CInventory::CInventory(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev, OBJ_ID::UI_INVENTORY)
	, m_bIsOn(false), m_bAlphaSet(false), m_iHaveKey(0), m_iTranslucent(0)
{
	m_pPlayer = nullptr;
}

CInventory::CInventory(const CInventory& rhs)
	:CUI(rhs)
	, m_pMannequinAniCom(rhs.m_pMannequinAniCom)
{
}

CInventory::~CInventory()
{
	Free();
}

HRESULT CInventory::Ready_Object()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	// 임시 아이템 추가
	CGameObject* pGameObject = CWarriorWeapon::Create(m_pGraphicDev);
	CEventMgr::GetInstance()->Add_Obj(L"잭 해머", pGameObject);
	m_vecItem.push_back(pGameObject);
	
	pGameObject = CNinjaWeapon::Create(m_pGraphicDev);
	CEventMgr::GetInstance()->Add_Obj(L"차", pGameObject);
	m_vecItem.push_back(pGameObject);
	
	pGameObject = CMageWeapon::Create(m_pGraphicDev);
	CEventMgr::GetInstance()->Add_Obj(L"고목 나무 스태프", pGameObject);
	m_vecItem.push_back(pGameObject);


	m_pMannequinAniCom = CAnimation::Create(m_pGraphicDev, m_pMannequinTexCom, STATE_TYPE::FRONT_IDLE, 0.2f, true);

	m_eUIType = UI_TYPE::VIEW;
	m_eUILayer = UI_LAYER::LV1;
	m_eInvenType = INVENTYPE::INVEN_ITEM;
	m_sEquipCheck.m_bShowUI = false;

	Ready_WorldMatrix();
	Ready_PublicUI();
	Ready_ItemPlayerUI();
	Ready_ItemUI();
	Ready_ItemPlayerFont();
	Ready_ItemFont();
	Ready_SkillUI();

	return S_OK;
}

void CInventory::Ready_WorldMatrix()
{	
	// Inven World Init
	for (_uint i = 0; i < INVENTORYID_END; ++i)
	{
		D3DXMatrixIdentity(&m_matInventoryWolrd[i]);
	}
	// Line  World Init
	for (_uint i = 0; i < INVEN_LINE - 16; ++i)
	{
		D3DXMatrixIdentity(&m_sLineAry[(INVEN_LINE + i) - 19].m_matLine);
	}

	// ItemSpace World Init
	for (_uint i = 0; i < INVEN_BUTTON12 - 2; ++i)
	{
		D3DXMatrixIdentity(&m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace);
	}

	// SkillSpace World Init
	for (_uint i = 0; i < INVEN_BUTTON12 - 2; ++i)
	{
		D3DXMatrixIdentity(&m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace);
	}

	// Space Equip World Init
	for (_uint i = 0; i < INVEN_BUTTON12 - 2; ++i)
	{
		D3DXMatrixIdentity(&m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matEquip);
	}
	// Player UI Init
	for (_uint i = 0; i < PLAYER_UI_END; ++i)
	{
		D3DXMatrixIdentity(&m_sPlayerUIAry[i].m_matPlUI);
	}
	// Item UI Init
	for (_uint i = 0; i < ITEMUI_END; ++i)
	{
		D3DXMatrixIdentity(&m_sItemStatUIAry[i].m_matItemStatUI);
	}

	// Skill UI Init
	for (_uint i = 0; i < MAX_SKILL_SLOT; ++i)
	{
		D3DXMatrixIdentity(&m_sSkillRingAry[i].m_matEmptySkillUI);
		D3DXMatrixIdentity(&m_sSkillRingAry[i].m_matSkillRingUI);
		D3DXMatrixIdentity(&m_sSkillRingAry[i].m_matSkillNumUI);
	}

	// Mouse World Init
	D3DXMatrixIdentity(&m_matCursorWorld);
	// Equip Check Init
	D3DXMatrixIdentity(&m_sEquipCheck.m_mateCheck);
	// Mannequin Init
	D3DXMatrixIdentity(&m_matMannequinWorld);
	// Fancy Init
	D3DXMatrixIdentity(&m_matFancyLWorld);
	D3DXMatrixIdentity(&m_matFancyRWorld); 
	// Shadow Init
	D3DXMatrixIdentity(&m_matShadowWorld); 
	// BigRing Init
	D3DXMatrixIdentity(&m_sBigSkillRing);

}
void CInventory::Ready_PublicUI()
{
	// Bkg setting
	m_fPosX = WINCX >> 1;
	m_fPosY = WINCY >> 1;
	m_fSizeX = WINCX;
	m_fSizeY = WINCY;
	m_matInventoryWolrd[INVEN_BKG]._11 = m_fSizeX;
	m_matInventoryWolrd[INVEN_BKG]._22 = m_fSizeY;
	m_matInventoryWolrd[INVEN_BKG]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_BKG]._42 = m_fPosY;


	// Button Cancel Button
	m_fPosX = 80.f;
	m_fPosY = 80.f;
	m_fSizeX = 80.f;
	m_fSizeY = 85.f;
	m_fMultipleSizeX = 0.5f;
	m_fMultipleSizeY = 0.5f;
	m_matInventoryWolrd[INVEN_CANCELBUTTON]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_CANCELBUTTON]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_CANCELBUTTON]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_CANCELBUTTON]._22 = m_fSizeY * m_fMultipleSizeY;


	// Tab Button  - Armor
	m_fPosX = 770.f;
	m_fPosY = 100.f;
	m_fSizeX = 176.f;
	m_fSizeY = 128.f;
	m_fMultipleSizeX = 0.38f;
	m_fMultipleSizeY = 0.28f;
	m_matInventoryWolrd[INVEN_ATABBUTTON]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_ATABBUTTON]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_ATABBUTTON]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_ATABBUTTON]._22 = m_fSizeY * m_fMultipleSizeY;


	// Tab Button Image - Armor Texture
	m_fPosX = 770.f;
	m_fPosY = 105.f;
	m_fSizeX = 88.f;
	m_fSizeY = 99.f;
	m_fMultipleSizeX = 0.25f;
	m_fMultipleSizeY = 0.25f;
	m_matInventoryWolrd[INVEN_ARMORTEX]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_ARMORTEX]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_ARMORTEX]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_ARMORTEX]._22 = m_fSizeY * m_fMultipleSizeY;

	// Tab Button - Skill   
	m_fPosX = 925.f;
	m_fPosY = 100.f;
	m_fSizeX = 176.f;
	m_fSizeY = 128.f;
	m_fMultipleSizeX = 0.38f;
	m_fMultipleSizeY = 0.28f;
	m_matInventoryWolrd[INVEN_STABBUTTON]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_STABBUTTON]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_STABBUTTON]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_STABBUTTON]._22 = m_fSizeY * m_fMultipleSizeY;

	// Tab Button Image - Skill Texture
	m_fPosX = 925.f;
	m_fPosY = 105.f;
	m_fSizeX = 92.f;
	m_fSizeY = 96.f;
	m_fMultipleSizeX = 0.25f;
	m_fMultipleSizeY = 0.25f;
	m_matInventoryWolrd[INVEN_SKILLTEX]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_SKILLTEX]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_SKILLTEX]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_SKILLTEX]._22 = m_fSizeY * m_fMultipleSizeY;

	// Tab Line 
	m_fPosX = 925.f;
	m_fPosY = 135.84f;
	m_fSizeX = 4.f;
	m_fSizeY = 4.f;
	m_fMultipleSizeX = 80.f;
	m_fMultipleSizeY = 0.25f;
	m_matInventoryWolrd[INVEN_TABLINE]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_TABLINE]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_TABLINE]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_TABLINE]._22 = m_fSizeY * m_fMultipleSizeY;

	// Mannequin
	m_fPosX = 300.f;
	m_fPosY = 350.f;
	m_fSizeX = 0.5f;
	m_fSizeY = 0.5f;
	m_fMultipleSizeX = 250.f;
	m_fMultipleSizeY = 250.f;
	m_matMannequinWorld._41 = m_fPosX;
	m_matMannequinWorld._42 = WINCY - m_fPosY;
	m_matMannequinWorld._11 = m_fSizeX * m_fMultipleSizeX;
	m_matMannequinWorld._22 = m_fSizeY * m_fMultipleSizeY;

	// Shadow
	m_fSizeX = 0.4f;
	m_fSizeY = 0.4f;
	m_fMultipleSizeX = 102.f;
	m_fMultipleSizeY = 47.f;
	m_matShadowWorld._41 = 300.f;
	m_matShadowWorld._42 = 310.f;
	m_matShadowWorld._11 = m_fSizeX * m_fMultipleSizeX;
	m_matShadowWorld._22 = m_fSizeY * m_fMultipleSizeY;

}
void CInventory::Ready_ItemPlayerUI()
{
	// Hp Bar
	m_fSizeX = 0.8f;
	m_fSizeY = 0.6f;
	m_fMultipleSizeX = 100.f;
	m_fMultipleSizeY = 100.f;
	m_sPlayerUIAry[PLAYER_HPBAR].m_matPlUI._41 = m_matMannequinWorld._41;
	m_sPlayerUIAry[PLAYER_HPBAR].m_matPlUI._42 = m_matMannequinWorld._42 - m_matMannequinWorld._22;
	m_sPlayerUIAry[PLAYER_HPBAR].m_matPlUI._11 = m_fSizeX * m_fMultipleSizeX;
	m_sPlayerUIAry[PLAYER_HPBAR].m_matPlUI._22 = m_fSizeY * m_fMultipleSizeY;

	// Mp Bar
	m_fSizeX = 0.8f;
	m_fSizeY = 0.6f;
	m_fMultipleSizeX = 100.f;
	m_fMultipleSizeY = 100.f;
	m_sPlayerUIAry[PLAYER_MPBAR].m_matPlUI._41 = m_sPlayerUIAry[PLAYER_HPBAR].m_matPlUI._41 + 2.5f;
	m_sPlayerUIAry[PLAYER_MPBAR].m_matPlUI._42 = m_sPlayerUIAry[PLAYER_HPBAR].m_matPlUI._42 - (m_sPlayerUIAry[PLAYER_HPBAR].m_matPlUI._22 * 0.5f) - 5.f;
	m_sPlayerUIAry[PLAYER_MPBAR].m_matPlUI._11 = m_fSizeX * m_fMultipleSizeX;
	m_sPlayerUIAry[PLAYER_MPBAR].m_matPlUI._22 = m_fSizeY * m_fMultipleSizeY;

	// Player Gold
	m_fSizeX = 0.3f;
	m_fSizeY = 0.3f;
	m_fMultipleSizeX = 70.f;
	m_fMultipleSizeY = 65.f;
	m_sPlayerUIAry[PLAYER_GOLD].m_matPlUI._41 = m_sPlayerUIAry[PLAYER_HPBAR].m_matPlUI._41 - (m_sPlayerUIAry[PLAYER_HPBAR].m_matPlUI._22 * 2.f);
	m_sPlayerUIAry[PLAYER_GOLD].m_matPlUI._42 = m_sPlayerUIAry[PLAYER_HPBAR].m_matPlUI._42;
	m_sPlayerUIAry[PLAYER_GOLD].m_matPlUI._11 = m_fSizeX * m_fMultipleSizeX;
	m_sPlayerUIAry[PLAYER_GOLD].m_matPlUI._22 = m_fSizeY * m_fMultipleSizeY;

	// Player Armor
	m_fSizeX = 0.3f;
	m_fSizeY = 0.3f;
	m_fMultipleSizeX = 70.f;
	m_fMultipleSizeY = 65.f;
	m_sPlayerUIAry[PLAYER_ARMOR].m_matPlUI._41 = m_sPlayerUIAry[PLAYER_HPBAR].m_matPlUI._41 + (m_sPlayerUIAry[PLAYER_HPBAR].m_matPlUI._22 * 2.f);
	m_sPlayerUIAry[PLAYER_ARMOR].m_matPlUI._42 = m_sPlayerUIAry[PLAYER_HPBAR].m_matPlUI._42;
	m_sPlayerUIAry[PLAYER_ARMOR].m_matPlUI._11 = m_fSizeX * m_fMultipleSizeX;
	m_sPlayerUIAry[PLAYER_ARMOR].m_matPlUI._22 = m_fSizeY * m_fMultipleSizeY;

	// Player Heart
	m_fPosX = 100.f;
	m_fPosY = 100.f;
	m_fSizeX = 0.4f;
	m_fSizeY = 0.4f;
	m_fMultipleSizeX = 43.f;
	m_fMultipleSizeY = 43.f;
	m_sPlayerUIAry[PLAYER_HEART].m_matPlUI._41 = m_fPosX;
	m_sPlayerUIAry[PLAYER_HEART].m_matPlUI._42 = m_fPosY;
	m_sPlayerUIAry[PLAYER_HEART].m_matPlUI._11 = m_fSizeX * m_fMultipleSizeX;
	m_sPlayerUIAry[PLAYER_HEART].m_matPlUI._22 = m_fSizeY * m_fMultipleSizeY;

	// Player Damage
	m_fSizeX = 0.4f;
	m_fSizeY = 0.4f;
	m_fMultipleSizeX = 43.f;
	m_fMultipleSizeY = 43.f;
	m_sPlayerUIAry[PLAYER_DAMAGE].m_matPlUI._41 = m_sPlayerUIAry[PLAYER_HEART].m_matPlUI._41 + 150.f;
	m_sPlayerUIAry[PLAYER_DAMAGE].m_matPlUI._42 = m_sPlayerUIAry[PLAYER_HEART].m_matPlUI._42;
	m_sPlayerUIAry[PLAYER_DAMAGE].m_matPlUI._11 = m_fSizeX * m_fMultipleSizeX;
	m_sPlayerUIAry[PLAYER_DAMAGE].m_matPlUI._22 = m_fSizeY * m_fMultipleSizeY;

	// Player Magic
	m_fSizeX = 0.4f;
	m_fSizeY = 0.4f;
	m_fMultipleSizeX = 43.f;
	m_fMultipleSizeY = 43.f;
	m_sPlayerUIAry[PLAYER_MAGIC].m_matPlUI._41 = m_sPlayerUIAry[PLAYER_DAMAGE].m_matPlUI._41 + 150.f;
	m_sPlayerUIAry[PLAYER_MAGIC].m_matPlUI._42 = m_sPlayerUIAry[PLAYER_DAMAGE].m_matPlUI._42;
	m_sPlayerUIAry[PLAYER_MAGIC].m_matPlUI._11 = m_fSizeX * m_fMultipleSizeX;
	m_sPlayerUIAry[PLAYER_MAGIC].m_matPlUI._22 = m_fSizeY * m_fMultipleSizeY;

	// Fancy
	m_fSizeX = 0.4f;
	m_fSizeY = 0.4f;
	m_fMultipleSizeX = 71.f;
	m_fMultipleSizeY = 37.f;
	m_matFancyLWorld._41 = 150.f;
	m_matFancyLWorld._42 = 150.f;
	m_matFancyLWorld._11 = m_fSizeX * m_fMultipleSizeX;
	m_matFancyLWorld._22 = m_fSizeY * m_fMultipleSizeY;

	m_fSizeX = 0.4f;
	m_fSizeY = 0.4f;
	m_fMultipleSizeX = 71.f;
	m_fMultipleSizeY = 37.f;
	m_matFancyRWorld._41 = 450.f;
	m_matFancyRWorld._42 = 150.f;
	m_matFancyRWorld._11 = -m_fSizeX * m_fMultipleSizeX;
	m_matFancyRWorld._22 = m_fSizeY * m_fMultipleSizeY;

	m_FancyRc = { 240, WINCY - 170, 240, WINCY - 170 };
}
void CInventory::Ready_ItemUI()
{	
	// ItemSpace
	int iIndex = 0;
	for (_int i = 0; i < 3; ++i)
	{
		for (_int j = 0; j < 4; ++j)
		{
			// space
			m_fPosX = 720.f + (135.f * j);
			m_fPosY = 220.f + (123.f * i);
			m_fSizeX = 175.f;
			m_fSizeY = 175.f;
			m_fMultipleSizeX = 0.3f;
			m_fMultipleSizeY = 0.3f;
			m_sItemSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matSpace._41 = m_fPosX;
			m_sItemSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matSpace._42 = WINCY - m_fPosY;
			m_sItemSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matSpace._11 = m_fSizeX * m_fMultipleSizeX;
			m_sItemSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matSpace._22 = m_fSizeY * m_fMultipleSizeY;

			// equip
			m_fPosX = 680.f + (135.f * j);
			m_fPosY = 180.f + (123.f * i);
			m_fSizeX = 82.f;
			m_fSizeY = 82.f;
			m_fMultipleSizeX = 0.3f;
			m_fMultipleSizeY = 0.3f;
			m_sItemSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matEquip._41 = m_fPosX;
			m_sItemSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matEquip._42 = WINCY - m_fPosY;
			m_sItemSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matEquip._11 = m_fSizeX * m_fMultipleSizeX;
			m_sItemSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matEquip._22 = m_fSizeY * m_fMultipleSizeY;

			iIndex += 1;
		}
	}

	// Item - Line
	for (_int i = 0; i < INVEN_LINE - 16; ++i)
	{
		m_fPosX = 950.f;
		switch (i)
		{
		case 0:
			m_fPosY = 542.5f;
			break;
		case 1:
			m_fPosY = 642.5f;
			break;
		case 2:
			m_fPosY = 692.5f;
			break;
		default:
			break;
		}
		m_fSizeX = 4.f;
		m_fSizeY = 2.f;
		m_fMultipleSizeX = 70.f;
		m_fMultipleSizeY = 0.25f;
		m_sLineAry[(INVEN_LINE + i) - 19].m_matLine._41 = m_fPosX;
		m_sLineAry[(INVEN_LINE + i) - 19].m_matLine._42 = WINCY - m_fPosY;
		m_sLineAry[(INVEN_LINE + i) - 19].m_matLine._11 = m_fSizeX * m_fMultipleSizeX;
		m_sLineAry[(INVEN_LINE + i) - 19].m_matLine._22 = m_fSizeY * m_fMultipleSizeY;
	}

	// Equip Check OK, NO 
	m_fPosX = 1100.f;
	m_fPosY = 592.5;
	m_fSizeX = 100.f;
	m_fSizeY = 50.f;
	//m_fMultipleSizeX = 0.5f;
	//m_fMultipleSizeY = 0.5f;
	m_sEquipCheck.m_mateCheck._41 = m_fPosX;
	m_sEquipCheck.m_mateCheck._42 = WINCY - m_fPosY;
	m_sEquipCheck.m_mateCheck._11 = m_fSizeX;
	m_sEquipCheck.m_mateCheck._22 = m_fSizeY;

	// Item Heart
	m_fSizeX = 0.4f;
	m_fSizeY = 0.4f;
	m_fMultipleSizeX = 43.f;
	m_fMultipleSizeY = 43.f;
	m_sItemStatUIAry[ITEM_HEART].m_matItemStatUI._41 = 690.f;
	m_sItemStatUIAry[ITEM_HEART].m_matItemStatUI._42 = WINCY - 670.f;
	m_sItemStatUIAry[ITEM_HEART].m_matItemStatUI._11 = m_fSizeX * m_fMultipleSizeX;
	m_sItemStatUIAry[ITEM_HEART].m_matItemStatUI._22 = m_fSizeY * m_fMultipleSizeY;

	// Item Damage
	m_fSizeX = 0.4f;
	m_fSizeY = 0.4f;
	m_fMultipleSizeX = 43.f;
	m_fMultipleSizeY = 43.f;
	m_sItemStatUIAry[ITEM_DAMAGE].m_matItemStatUI._41 = 790.f;
	m_sItemStatUIAry[ITEM_DAMAGE].m_matItemStatUI._42 = WINCY - 670.f;
	m_sItemStatUIAry[ITEM_DAMAGE].m_matItemStatUI._11 = m_fSizeX * m_fMultipleSizeX;
	m_sItemStatUIAry[ITEM_DAMAGE].m_matItemStatUI._22 = m_fSizeY * m_fMultipleSizeY;

	// Item Magic
	m_fSizeX = 0.4f;
	m_fSizeY = 0.4f;
	m_fMultipleSizeX = 43.f;
	m_fMultipleSizeY = 43.f;
	m_sItemStatUIAry[ITEM_MAGIC].m_matItemStatUI._41 = 890.f;
	m_sItemStatUIAry[ITEM_MAGIC].m_matItemStatUI._42 = WINCY - 670.f;
	m_sItemStatUIAry[ITEM_MAGIC].m_matItemStatUI._11 = m_fSizeX * m_fMultipleSizeX;
	m_sItemStatUIAry[ITEM_MAGIC].m_matItemStatUI._22 = m_fSizeY * m_fMultipleSizeY;
}
void CInventory::Ready_ItemPlayerFont()
{
	// 골드
	m_sPlayerStatFont[PLAYER_GOLD].m_plStatRc = {
		(LONG)(m_sPlayerUIAry[PLAYER_GOLD].m_matPlUI._41 - 75.f),
		(LONG)(m_sPlayerUIAry[PLAYER_GOLD].m_matPlUI._42 + 210.f),
		(LONG)(m_sPlayerUIAry[PLAYER_GOLD].m_matPlUI._41 - 50.f),
		(LONG)(m_sPlayerUIAry[PLAYER_GOLD].m_matPlUI._42 + 210.f)
	};
	// 아머
	m_sPlayerStatFont[PLAYER_ARMOR].m_plStatRc = {
		(LONG)(m_sPlayerUIAry[PLAYER_ARMOR].m_matPlUI._41 + 40.f),
		(LONG)(m_sPlayerUIAry[PLAYER_ARMOR].m_matPlUI._42 + 210.f),
		(LONG)(m_sPlayerUIAry[PLAYER_ARMOR].m_matPlUI._41 + 65.f),
		(LONG)(m_sPlayerUIAry[PLAYER_ARMOR].m_matPlUI._42 + 210.f)
	};
	// 최대 체력
	m_sPlayerStatFont[PLAYER_HEART].m_plStatRc = {
		(LONG)(m_sPlayerUIAry[PLAYER_HEART].m_matPlUI._41 + 80.f),
		WINCY - 125,
		(LONG)(m_sPlayerUIAry[PLAYER_HEART].m_matPlUI._41 + 80.f),
		WINCY - 125
	};
	// 공격력
	m_sPlayerStatFont[PLAYER_DAMAGE].m_plStatRc = {
		(LONG)(m_sPlayerUIAry[PLAYER_DAMAGE].m_matPlUI._41 + 80.f),
		WINCY - 125,
		(LONG)(m_sPlayerUIAry[PLAYER_DAMAGE].m_matPlUI._41 + 80.f),
		WINCY - 125
	};
	// 마력
	m_sPlayerStatFont[PLAYER_MAGIC].m_plStatRc = {
		(LONG)(m_sPlayerUIAry[PLAYER_MAGIC].m_matPlUI._41 + 80.f),
		WINCY - 125,
		(LONG)(m_sPlayerUIAry[PLAYER_MAGIC].m_matPlUI._41 + 80.f),
		WINCY - 125
	};
}
void CInventory::Ready_ItemFont()
{
	// 최대 체력
	m_sItemStatFont[ITEM_HEART].m_pItemStatRc = {
		(LONG)(m_sItemStatUIAry[ITEM_HEART].m_matItemStatUI._41 + 30.f),
		WINCY - 70,
		(LONG)(m_sItemStatUIAry[ITEM_HEART].m_matItemStatUI._41 + 30.f),
		WINCY - 70
	};
	// 공격력
	m_sItemStatFont[ITEM_DAMAGE].m_pItemStatRc = {
		(LONG)(m_sItemStatUIAry[ITEM_DAMAGE].m_matItemStatUI._41 + 30.f),
		WINCY - 70,
		(LONG)(m_sItemStatUIAry[ITEM_DAMAGE].m_matItemStatUI._41 + 30.f),
		WINCY - 70
	};
	// 마력
	m_sItemStatFont[ITEM_MAGIC].m_pItemStatRc = {
		(LONG)(m_sItemStatUIAry[ITEM_MAGIC].m_matItemStatUI._41 + 30.f),
		WINCY - 70,
		(LONG)(m_sItemStatUIAry[ITEM_MAGIC].m_matItemStatUI._41 + 30.f),
		WINCY - 70
	};

	// 아이템 이름, 레벨
	m_ItemNameRc = { 690, WINCY - 170, 690, WINCY - 170 };
	m_ItemLvRc = { 690, WINCY - 120, 690, WINCY - 120 };

	// 합산 폰트
	m_ResultHpRc = {
		(LONG)(m_sPlayerUIAry[PLAYER_HEART].m_matPlUI._41 + 80.f),
		WINCY - 90,
		(LONG)(m_sPlayerUIAry[PLAYER_HEART].m_matPlUI._41 + 80.f),
		WINCY - 90
	};
	m_ResultDmgRc = {
		(LONG)(m_sPlayerUIAry[PLAYER_DAMAGE].m_matPlUI._41 + 80.f),
		WINCY - 90,
		(LONG)(m_sPlayerUIAry[PLAYER_DAMAGE].m_matPlUI._41 + 80.f),
		WINCY - 90
	};
	m_ResultMagicRc = {
		(LONG)(m_sPlayerUIAry[PLAYER_MAGIC].m_matPlUI._41 + 80.f),
		WINCY - 90,
		(LONG)(m_sPlayerUIAry[PLAYER_MAGIC].m_matPlUI._41 + 80.f),
		WINCY - 90
	};


}
void CInventory::Ready_SkillUI()
{
	// SkillSpace
	int iIndex = 0;
	for (_int i = 0; i < 3; ++i)
	{
		for (_int j = 0; j < 4; ++j)
		{
			// space
			m_fPosX = 720.f + (135.f * j);
			m_fPosY = 220.f + (123.f * i);
			m_fSizeX = 175.f;
			m_fSizeY = 175.f;
			m_fMultipleSizeX = 0.3f;
			m_fMultipleSizeY = 0.3f;
			m_sSkillSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matSpace._41 = m_fPosX;
			m_sSkillSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matSpace._42 = WINCY - m_fPosY;
			m_sSkillSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matSpace._11 = m_fSizeX * m_fMultipleSizeX;
			m_sSkillSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matSpace._22 = m_fSizeY * m_fMultipleSizeY;

			iIndex += 1;
		}
	}

	// BigRingUI
	m_fPosX = 300.f;
	m_fPosY = 350.f;
	m_fSizeX = 200.f;
	m_fSizeY = 200.f;
	m_sBigSkillRing._41 = m_fPosX;
	m_sBigSkillRing._42 = WINCY - m_fPosY;
	m_sBigSkillRing._11 = m_fSizeX;
	m_sBigSkillRing._22 = m_fSizeY;

	// Skill UI
	for (_int i = 0; i < MAX_SKILL_SLOT; ++i)
	{
		switch (i)
		{
		case 0:
			m_fPosX = m_sBigSkillRing._41;
			m_fPosY = m_sBigSkillRing._42 + 175.f;
			break;
		case 1:
			m_fPosX = m_sBigSkillRing._41 + 175.f;
			m_fPosY = m_sBigSkillRing._42;
			break;
		case 2:
			m_fPosX = m_sBigSkillRing._41;
			m_fPosY = m_sBigSkillRing._42 - 175.f;
			break;
		case 3:
			m_fPosX = m_sBigSkillRing._41 - 175.f	;
			m_fPosY = m_sBigSkillRing._42;
			break;
		default:
			break;
		}
		// Ring
		m_sSkillRingAry[i].m_matSkillRingUI._41 = m_fPosX;
		m_sSkillRingAry[i].m_matSkillRingUI._42 = m_fPosY;
		m_sSkillRingAry[i].m_matSkillRingUI._11 = 80.f;
		m_sSkillRingAry[i].m_matSkillRingUI._22 = 80.f;

		// Empty
		m_sSkillRingAry[i].m_matEmptySkillUI._41 = m_fPosX;
		m_sSkillRingAry[i].m_matEmptySkillUI._42 = m_fPosY;
		m_sSkillRingAry[i].m_matEmptySkillUI._11 = 65.f;
		m_sSkillRingAry[i].m_matEmptySkillUI._22 = 65.f;

		// Number
		m_sSkillRingAry[i].m_matSkillNumUI._41 = m_fPosX;
		m_sSkillRingAry[i].m_matSkillNumUI._42 = m_fPosY - 70.f;
		m_sSkillRingAry[i].m_matSkillNumUI._11 = 20.f;
		m_sSkillRingAry[i].m_matSkillNumUI._22 = 20.f;


	}


}

_int CInventory::Update_Object(const _float& fTimeDelta)
{
	if (!m_pPlayer)
	{
		if (nullptr == m_pPlayer)
			m_pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));
	}

	m_pMannequinAniCom->Update_Animation(fTimeDelta);

	_int iExit = __super::Update_Object(fTimeDelta);

	Key_Input();
	Mouse_Update();

	return iExit;
}

void CInventory::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CInventory::Render_Object()
{
	if (m_bIsOn)
	{
		if (m_iTranslucent < 240 && !m_bAlphaSet) m_iTranslucent += 10.f;

		Render_PublicUI();
		TabPicking_UI();
		if (m_eInvenType == INVENTYPE::INVEN_ITEM)
		{
			Render_ItemInventory();
		}
		else if (m_eInvenType == INVENTYPE::INVEN_SKILL)
		{
			Render_SkillInventory();
		}

		// Cursor 
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matCursorWorld);
		m_pCursorTexCom->Render_Texture();
		m_pBufferCom->Render_Buffer();

	}

	// 위를 무시하고 바로 일로 오기 때문에 랜더들이 알파값이 적용 안되고 바로꺼진다.
	// 집에서 수정하자.
	if (m_bAlphaSet)
	{
		m_iTranslucent -= 10;
		if (m_iTranslucent <= 10)
		{
			m_bIsOn = !m_bIsOn; 
			m_bAlphaSet = false;
		}
	}

	__super::Render_Object();

}

void CInventory::Render_PublicUI()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iTranslucent, 255, 255, 255));
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	// BackGround
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_BKG]);
	m_pInventoryTexCom[INVEN_BKG]->Render_Texture();
	m_pBufferCom->Render_Buffer();

	// Tab Button - Armor
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_ATABBUTTON]);
	m_pInventoryTexCom[INVEN_ATABBUTTON]->Render_Texture();
	m_pBufferCom->Render_Buffer();

	// Tab Button - Skill
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_STABBUTTON]);
	m_pInventoryTexCom[INVEN_STABBUTTON]->Render_Texture();
	m_pBufferCom->Render_Buffer();

	// Tab Button Image - Armor Texture
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_ARMORTEX]);
	m_pInventoryTexCom[INVEN_ARMORTEX]->Render_Texture();
	m_pBufferCom->Render_Buffer();

	// Tab Button Image - Skill Texture
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_SKILLTEX]);
	m_pInventoryTexCom[INVEN_SKILLTEX]->Render_Texture();
	m_pBufferCom->Render_Buffer();

	// Cancel Button
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_CANCELBUTTON]);
	m_pInventoryTexCom[INVEN_CANCELBUTTON]->Render_Texture();
	m_pBufferCom->Render_Buffer();

	// Tab Line 
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_TABLINE]);
	m_pInventoryTexCom[INVEN_TABLINE]->Render_Texture();
	m_pBufferCom->Render_Buffer();

	// Shadow
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matShadowWorld);
	m_pShadowTexCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	// Mannequin
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matMannequinWorld);
	m_pMannequinAniCom->Render_Animation();
	m_pBufferCom->Render_Buffer();
}

// Item
void CInventory::Render_ItemInventory()
{
	Render_PlayerStatUI();
	ItemPicking_UI();
	Render_ItemUI();
	Render_PlayerItemFont();
}
void CInventory::Render_PlayerStatUI()
{
	// Item 불러오기
	for (_int i = 0; i < m_vecItem.size(); ++i)
	{
		dynamic_cast<CItem_Weapon*>(m_vecItem[i])->Set_InvenTrans(
			m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._41,
			m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._42
		);
		m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bIsSpace = true;
	}
	// PlayerUI
	for (_int i = 0; i < PLAYER_UI_END; ++i)
	{
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sPlayerUIAry[i].m_matPlUI);
		m_sPlayerUIAry[i].m_pPlUITex->Render_Texture();
		m_pBufferCom->Render_Buffer();
	}

	// Fancy
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matFancyLWorld);
	m_pFancyLTexCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matFancyRWorld);
	m_pFancyRTexCom->Render_Texture();
	m_pBufferCom->Render_Buffer();
}
void CInventory::Render_ItemUI()
{
	// ItemSpace 
	for (_int i = 0; i < INVEN_BUTTON12 - 2; ++i)
	{
		// 아이템 있음
		if (m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bIsSpace == true && m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bOnSpace == false)
		{
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace);
			m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceIsTex->Render_Texture();
			m_pBufferCom->Render_Buffer();
		}
		// 아이템 선택
		else if (m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bIsSpace == true && m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bOnSpace == true)
		{
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace);
			m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceSelectTex->Render_Texture();
			m_pBufferCom->Render_Buffer();
		}
		// 아이템 없음
		else
		{
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace);
			m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceNoneTex->Render_Texture();
			m_pBufferCom->Render_Buffer();
		}
		// 무기 선택 미니 아이콘
		if (m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bEquip)
		{
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matEquip);
			m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceEquipTex->Render_Texture();
			m_pBufferCom->Render_Buffer();

		}
	}

	if (m_sEquipCheck.m_bShowUI)
	{
		// Line
		for (_int i = 0; i < INVEN_LINE - 16; ++i)
		{
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sLineAry[(INVEN_LINE + i) - 19].m_matLine);
			m_sLineAry[(INVEN_LINE + i) - 19].m_pLineTex->Render_Texture();
			m_pBufferCom->Render_Buffer();
		}

		// OK 
		if (m_sEquipCheck.m_eEquipCheck == EQUIP_OK)
		{
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sEquipCheck.m_mateCheck);
			m_sEquipCheck.m_pOkTex->Render_Texture();
			m_pBufferCom->Render_Buffer();
		}

		// NO
		if (m_sEquipCheck.m_eEquipCheck == EQUIP_NO)
		{
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sEquipCheck.m_mateCheck);
			m_sEquipCheck.m_pNoTex->Render_Texture();
			m_pBufferCom->Render_Buffer();
		}

	}

}
void CInventory::Render_PlayerItemFont()
{
	//								Player Font
	// Gold
	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, to_wstring((int)(m_pPlayer->Get_StatInfo().fGold)).c_str(), -1,
		&m_sPlayerStatFont[PLAYER_GOLD].m_plStatRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 255, 255, 255));
	// Armor
	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, L"0/0", -1,
		&m_sPlayerStatFont[PLAYER_ARMOR].m_plStatRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 255, 255, 255));

	// Heart
	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, to_wstring((int)(m_pPlayer->Get_StatInfo().fMaxHP)).c_str(), -1,
		&m_sPlayerStatFont[PLAYER_HEART].m_plStatRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 153, 102, 0));

	// Damage
	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, to_wstring((int)(m_pPlayer->Get_StatInfo().fAD)).c_str(), -1,
		&m_sPlayerStatFont[PLAYER_DAMAGE].m_plStatRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 153, 102, 0));

	// Magic
	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, to_wstring(10).c_str(), -1,
		&m_sPlayerStatFont[PLAYER_MAGIC].m_plStatRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 153, 102, 0));

	// Fancy
	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, L"Statistics", -1,
		&m_FancyRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 153, 102, 0));
}

void CInventory::Render_SkillInventory()
{
	SkillPicking_UI();
	Render_SkillUI();
	Render_SkillFont();
}

void CInventory::Render_SkillUI()
{
	// SkillSpace 
	for (_int i = 0; i < INVEN_BUTTON12 - 2; ++i)
	{
		// 스킬 있음
		if (m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bIsSpace == true && m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bOnSpace == false)
		{
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace);
			m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceIsTex->Render_Texture();
			m_pBufferCom->Render_Buffer();
		}
		// 스킬 선택
		else if (m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bIsSpace == true && m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bOnSpace == true)
		{
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace);
			m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceSelectTex->Render_Texture();
			m_pBufferCom->Render_Buffer();
		}
		// 스킬 없음
		else
		{
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace);
			m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceNoneTex->Render_Texture();
			m_pBufferCom->Render_Buffer();
		}
	}

	// BigRingUI
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sBigSkillRing);
	m_pBigSkillRingTex->Render_Texture();
	m_pBufferCom->Render_Buffer();

	// Skill UI
	for (_int i = 0; i < MAX_SKILL_SLOT; ++i)
	{
		// Ring UI
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sSkillRingAry[i].m_matSkillRingUI);
		m_sSkillRingAry[i].m_pSkillRingUITex->Render_Texture();
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sSkillRingAry[i].m_matEmptySkillUI);
		m_sSkillRingAry[i].m_pSkillEmptyUITex->Render_Texture();
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sSkillRingAry[i].m_matSkillNumUI);
		m_sSkillRingAry[i].m_pSkillNumUITex->Render_Texture();
		m_pBufferCom->Render_Buffer();

	}


}

void CInventory::Render_SkillFont()
{
}

// Picking
void CInventory::ItemPicking_UI()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	D3DVIEWPORT9 ViewPort;

	m_pGraphicDev->GetViewport(&ViewPort);

	pt.y = WINCY - pt.y;

	for (_int i = 0; i < m_vecItem.size(); ++i)
	{
		RECT SpaceRT;
		SpaceRT.left = m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._41 - (m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._11 * 0.5f);
		SpaceRT.right = m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._41 + (m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._11 * 0.5f);
		SpaceRT.top = m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._42 - (m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._22 * 0.5f);
		SpaceRT.bottom = m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._42 + (m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._22 * 0.5f);

		// 피킹
		if (PtInRect(&SpaceRT, pt))
		{
			// 황금 박스로 변경
			m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bOnSpace = true;

			// 마우스 클릭 시
			if (CInputDev::GetInstance()->Key_Down(MK_LBUTTON))
			{
				if (!m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bEquip && m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bIsSpace)
				{
					// 이미 선택된 애들은 해제
					for (_int i = 0; i < m_vecItem.size(); ++i)
					{
						m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bEquip = false;
					}
					m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bEquip = true;
				}
				else
					m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bEquip = false;
			}

			Item_StatView(i);

			// EquipCheck 버튼
			if (m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bEquip)
			{
				m_sEquipCheck.m_eEquipCheck = EQUIP_OK;
			}
			else if (!m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bEquip)
			{
				m_sEquipCheck.m_eEquipCheck = EQUIP_NO;
			}
			//////////////////

		}
		// 픽킹 상태가 아닐 때
		else
		{
			m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bOnSpace = false;
			m_sEquipCheck.m_bShowUI = false;
		}
	}
}
void CInventory::SkillPicking_UI()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	D3DVIEWPORT9 ViewPort;

	m_pGraphicDev->GetViewport(&ViewPort);

	pt.y = WINCY - pt.y;

	// 스킬 배열도 만들어서 스킬 범위 사이즈만큼 예외 처리 하자.
	for (_int i = 0; i < INVEN_BUTTON12 - 2; ++i)
	{
		RECT SpaceRT;
		SpaceRT.left = m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._41 - (m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._11 * 0.5f);
		SpaceRT.right = m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._41 + (m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._11 * 0.5f);
		SpaceRT.top = m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._42 - (m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._22 * 0.5f);
		SpaceRT.bottom = m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._42 + (m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._22 * 0.5f);

		// 피킹
		if (PtInRect(&SpaceRT, pt))
		{
			// 황금 박스로 변경
			m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bOnSpace = true;

			// 마우스 클릭 시
			if (CInputDev::GetInstance()->Key_Down(MK_LBUTTON))
			{

			}
		}
		// 픽킹 상태가 아닐 때
		else
		{
			m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bOnSpace = false;
			m_sEquipCheck.m_bShowUI = false;
		}
	}
}
void CInventory::Item_StatView(_int _Index)
{
	if (_Index <= m_vecItem.size())
	{
		m_sEquipCheck.m_bShowUI = true;
		Render_ItemUI();

		CItem_Weapon* pWeapon = dynamic_cast<CItem_Weapon*>(m_vecItem[_Index]);

		// ItemUI
		for (_int i = 0; i < ITEMUI_END; ++i)
		{
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sItemStatUIAry[i].m_matItemStatUI);
			m_sItemStatUIAry[i].m_pItemStatUITex->Render_Texture();
			m_pBufferCom->Render_Buffer();
		}

		//								Item Font
		// Heart
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, to_wstring((int)(pWeapon->Get_StatInfo().fMaxHP)).c_str(), -1,
			&m_sItemStatFont[ITEM_HEART].m_pItemStatRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 153, 102, 0));

		// Damage
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, to_wstring((int)(pWeapon->Get_StatInfo().fAD)).c_str(), -1,
			&m_sItemStatFont[ITEM_DAMAGE].m_pItemStatRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 153, 102, 0));

		// Magic
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, to_wstring(10).c_str(), -1,
			&m_sItemStatFont[ITEM_MAGIC].m_pItemStatRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 153, 102, 0));

		// Name
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, pWeapon->Get_Name(), -1,
			&m_ItemNameRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 153, 102, 0));

		// LV
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, L"LV 1", -1,
			&m_ItemLvRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 153, 102, 0));

		// 합산 폰트
		// Heart
		_int iResult = (m_pPlayer->Get_StatInfo().fMaxHP
			+ pWeapon->Get_StatInfo().fMaxHP) - m_pPlayer->Get_StatInfo().fMaxHP;

		wstring HpResultStr;
		if (iResult > 0)		HpResultStr = L"+" + to_wstring(iResult);
		else if (iResult < 0)	HpResultStr = L"-" + to_wstring(iResult);
		else					HpResultStr = to_wstring(iResult);
		if (!m_sItemSpaceAry[(INVEN_BUTTON1 + _Index) - 3].m_bEquip)
		{
			CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, HpResultStr.c_str(), -1,
				&m_ResultHpRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 0, 153, 0));
		}


		// Damage
		iResult = (m_pPlayer->Get_StatInfo().fAD
			+ pWeapon->Get_StatInfo().fAD) - m_pPlayer->Get_StatInfo().fAD;

		wstring DmgResultStr;
		if (iResult > 0)		DmgResultStr = L"+" + to_wstring(iResult);
		else if (iResult < 0)	DmgResultStr = L"-" + to_wstring(iResult);
		else					DmgResultStr = to_wstring(iResult);
		if (!m_sItemSpaceAry[(INVEN_BUTTON1 + _Index) - 3].m_bEquip)
		{
			CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, DmgResultStr.c_str(), -1,
				&m_ResultDmgRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(m_iTranslucent, 0, 153, 0));
		}
		// Magic(미구현이라 보류)
		//iResult = (m_pPlayer->Get_StatInfo().fMaxHP
		//	+ pWeapon->Get_StatInfo().fMaxHP) - m_pPlayer->Get_StatInfo().fMaxHP;
		//CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, to_wstring(10).c_str(), -1,
		//	&m_sItemStatFont[ITEM_MAGIC].m_pItemStatRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(200, 0, 0, 0));

	}
}
void CInventory::TabPicking_UI()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	D3DVIEWPORT9 ViewPort;

	m_pGraphicDev->GetViewport(&ViewPort);

	pt.y = WINCY - pt.y;

	for (_int i = 0; i < INVENTORYID_END; ++i)
	{
		RECT TabRT;
		TabRT.left    =	m_matInventoryWolrd[i]._41 - (m_matInventoryWolrd[i]._11 * 0.5f);
		TabRT.right   =	m_matInventoryWolrd[i]._41 + (m_matInventoryWolrd[i]._11 * 0.5f);
		TabRT.top	  =	m_matInventoryWolrd[i]._42 - (m_matInventoryWolrd[i]._22 * 0.5f);
		TabRT.bottom  =	m_matInventoryWolrd[i]._42 + (m_matInventoryWolrd[i]._22 * 0.5f);

		// 피킹
		if (PtInRect(&TabRT, pt))
		{
			if (i == INVEN_ARMORTEX && CInputDev::GetInstance()->Key_Down(MK_LBUTTON))
			{
				if (m_eInvenType != INVENTYPE::INVEN_ITEM)
				{
					m_eInvenType = INVENTYPE::INVEN_ITEM;
				}
			}

			if (i == INVEN_SKILLTEX && CInputDev::GetInstance()->Key_Down(MK_LBUTTON))
			{
				if (m_eInvenType != INVENTYPE::INVEN_SKILL)
				{
					m_eInvenType = INVENTYPE::INVEN_SKILL;
				}
			}
		}

	}
}


HRESULT CInventory::Add_Component()
{
	CComponent* pComponent = nullptr;

	// RcTex Com
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


#pragma region Texture
	
#pragma region PublicUI
	// BackGround
	pComponent = m_pInventoryTexCom[INVEN_BKG] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_BKG", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - Cursor
	pComponent = m_pCursorTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Cursor", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - cancel
	pComponent = m_pInventoryTexCom[INVEN_CANCELBUTTON] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_Cancel", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - Tab Button Armor
	pComponent = m_pInventoryTexCom[INVEN_ATABBUTTON] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Tab", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - Tab Button Armor Tex
	pComponent = m_pInventoryTexCom[INVEN_ARMORTEX] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Tab_Armors_Texture", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// UI - Tab Button Skill
	pComponent = m_pInventoryTexCom[INVEN_STABBUTTON] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Tab", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// UI - Tab Button Skill Tex
	pComponent = m_pInventoryTexCom[INVEN_SKILLTEX] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Tab_Skill_Texture", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - Line
	pComponent = m_pInventoryTexCom[INVEN_LINE] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Line", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - Line
	for (_int i = 0; i < INVEN_LINE - 16; ++i)
	{
		pComponent = m_sLineAry[(INVEN_LINE + i) - 19].m_pLineTex
			= dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Line", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	}

	// UI - Tab Line
	pComponent = m_pInventoryTexCom[INVEN_TABLINE] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_TabLine", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - OK 
	pComponent = m_sEquipCheck.m_pOkTex
		= dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_OK", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	// UI - NO
	pComponent = m_sEquipCheck.m_pNoTex
		= dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_NO", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - Sort button 
	// pComponent = m_pInventoryTexCom[INVEN_SORTBUTTON] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_Plain", this));
	// NULL_CHECK_RETURN(pComponent, E_FAIL);
	// m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// Mannequin
	pComponent = m_pMannequinTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fIdle", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// Shadow
	pComponent = m_pShadowTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Shadow_Creature", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

#pragma endregion

#pragma region ItemUI
	// UI - ItemSpace
	for (_int i = 0; i < INVEN_BUTTON12 - 2; ++i)
	{
		// 아이템 존재x
		pComponent = m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceNoneTex
			= dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_blank", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
		// 아이템 존재
		pComponent = m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceIsTex
			= dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
		// 아이템 선택
		pComponent = m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceSelectTex
			= dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_Gold", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
		// 무기 선택 미니 아이콘
		pComponent = m_sItemSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceEquipTex
			= dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Weapon_Select", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	}

#pragma endregion

#pragma region Item Stat
	// UI - Item Stat START

	// Fancy
	pComponent = m_pFancyLTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Fancy", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pFancyRTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Fancy", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// HEART
	pComponent = m_sItemStatUIAry[ITEM_HEART].m_pItemStatUITex = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Player_Heart", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// DAMAGE
	pComponent = m_sItemStatUIAry[ITEM_DAMAGE].m_pItemStatUITex = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Player_Damage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// MAGIC
	pComponent = m_sItemStatUIAry[ITEM_MAGIC].m_pItemStatUITex = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Player_Magic", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - Item Stat END
#pragma endregion

#pragma region Player Stat
	// UI - Player Stat START

	// GOLD
	pComponent = m_sPlayerUIAry[PLAYER_GOLD].m_pPlUITex = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Player_Gold", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// HPBAR
	pComponent = m_sPlayerUIAry[PLAYER_HPBAR].m_pPlUITex = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Player_HpBar", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// MPBAR
	pComponent = m_sPlayerUIAry[PLAYER_MPBAR].m_pPlUITex = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Player_MpBar", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// ARMOR
	pComponent = m_sPlayerUIAry[PLAYER_ARMOR].m_pPlUITex = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Player_Armor", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// HEART
	pComponent = m_sPlayerUIAry[PLAYER_HEART].m_pPlUITex = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Player_Heart", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// DAMAGE
	pComponent = m_sPlayerUIAry[PLAYER_DAMAGE].m_pPlUITex = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Player_Damage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// MAGIC
	pComponent = m_sPlayerUIAry[PLAYER_MAGIC].m_pPlUITex = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Player_Magic", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - Player Stat END
#pragma endregion

#pragma region SkillUI
	// UI - SkillSpace
	for (_int i = 0; i < INVEN_BUTTON12 - 2; ++i)
	{
		// 스킬 존재x
		pComponent = m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceNoneTex
			= dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_blank", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
		// 스킬 존재
		pComponent = m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceIsTex
			= dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
		// 스킬 선택
		pComponent = m_sSkillSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceSelectTex
			= dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_Gold", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	}

	// BigRingUI
	pComponent = m_pBigSkillRingTex = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Ring", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	for (_int i = 0; i < MAX_SKILL_SLOT; ++i)
	{
		// Ring UI
		pComponent = m_sSkillRingAry[i].m_pSkillRingUITex
			= dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Ring", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	
		// Empty UI
		pComponent = m_sSkillRingAry[i].m_pSkillEmptyUITex
			= dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Skill_Empty", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	
		// Number
		switch (i)
		{
		case 0:
			pComponent = m_sSkillRingAry[i].m_pSkillNumUITex = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Skill_Number1", this));
			break;
		case 1:
			pComponent = m_sSkillRingAry[i].m_pSkillNumUITex = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Skill_Number2", this));
			break;
		case 2:
			pComponent = m_sSkillRingAry[i].m_pSkillNumUITex = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Skill_Number3", this));
			break;
		case 3:
			pComponent = m_sSkillRingAry[i].m_pSkillNumUITex = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Skill_Number4", this));
			break;
		}
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	}

#pragma endregion

#pragma endregion

	return S_OK;
}

void CInventory::Key_Input()
{
	if (CInputDev::GetInstance()->Key_Down(VK_TAB))
	{
		if (!m_bIsOn) {
			m_bIsOn = true;
		}
		else
		{
			m_bAlphaSet = true;
		}
	}

	if (m_bIsOn == true || CInputDev::GetInstance()->Get_DIMouseState(DIM_RB))
	{
		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::PLAYER)->Layer_SetActive(false);
		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::MONSTER)->Layer_SetActive(false);
		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::EFFECT)->Layer_SetActive(false);

	}
	else 
	{
		if (m_iTranslucent > 0) m_iTranslucent -= 10.f;

		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::PLAYER)->Layer_SetActive(true);
		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::EFFECT)->Layer_SetActive(true);
		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::MONSTER)->Layer_SetActive(true);
	}
	

}

void CInventory::Mouse_Update()
{
	POINT CursorUIpt;
	GetCursorPos(&CursorUIpt);
	ScreenToClient(g_hWnd, &CursorUIpt);

	D3DVIEWPORT9 ViewPort;

	m_pGraphicDev->GetViewport(&ViewPort);

	CursorUIpt.y = WINCY - CursorUIpt.y;

	m_matCursorWorld._41 = CursorUIpt.x;
	m_matCursorWorld._42 = CursorUIpt.y - 70.f * 0.3f;
	m_matCursorWorld._11 = 70.f * 0.3f;
	m_matCursorWorld._22 = 87.f * 0.3f;

}


CInventory* CInventory::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CInventory* pInstance = new CInventory(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Inventory Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CInventory::Free()
{
	// for_each(m_vecItem.begin(), m_vecItem.end(), CDeleteObj());
	// m_vecItem.clear();
	__super::Free();
}
