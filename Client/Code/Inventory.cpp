#include "Inventory.h"
#include "Export_Function.h"

#include "Item_Weapon.h"
#include "WarriorWeapon.h"
#include "MageWeapon.h"
#include "NinjaWeapon.h"
#include "Player.h"

CInventory::CInventory(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev, OBJ_ID::UI_INVENTORY)
	, m_bIsOn(false), m_iHaveKey(0), m_iTranslucent(0)
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
	Ready_PlayerUI();
	Ready_ItemUI();
	Ready_PlayerFont();
	Ready_ItemFont();

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

	// Space World Init
	for (_uint i = 0; i < INVEN_BUTTON12 - 2; ++i)
	{
		D3DXMatrixIdentity(&m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace);
	}
	// Space Equip World Init
	for (_uint i = 0; i < INVEN_BUTTON12 - 2; ++i)
	{
		D3DXMatrixIdentity(&m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matEquip);
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

	// Equip Check Init
	D3DXMatrixIdentity(&m_sEquipCheck.m_mateCheck);
	// Mannequin Init
	D3DXMatrixIdentity(&m_matMannequinWorld);
	// Fancy
	D3DXMatrixIdentity(&m_matFancyLWorld);
	D3DXMatrixIdentity(&m_matFancyRWorld); 
	// Shadow
	D3DXMatrixIdentity(&m_matShadowWorld); 
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
	m_fPosX = 670.f;
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
	m_fPosX = 670.f;
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
	m_fPosX = 825.f;
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
	m_fPosX = 825.f;
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
	m_fPosX = 825.f;
	m_fPosY = 135.84f;
	m_fSizeX = 4.f;
	m_fSizeY = 4.f;
	m_fMultipleSizeX = 80.f;
	m_fMultipleSizeY = 0.25f;
	m_matInventoryWolrd[INVEN_TABLINE]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_TABLINE]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_TABLINE]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_TABLINE]._22 = m_fSizeY * m_fMultipleSizeY;

	// Button
	int iIndex = 0;
	for (_int i = 0; i < 3; ++i)
	{
		for (_int j = 0; j < 4; ++j)
		{
			// space
			m_fPosX = 620.f + (135.f * j);
			m_fPosY = 220.f + (123.f * i);
			m_fSizeX = 175.f;
			m_fSizeY = 175.f;
			m_fMultipleSizeX = 0.3f;
			m_fMultipleSizeY = 0.3f;
			m_sSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matSpace._41 = m_fPosX;
			m_sSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matSpace._42 = WINCY - m_fPosY;
			m_sSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matSpace._11 = m_fSizeX * m_fMultipleSizeX;
			m_sSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matSpace._22 = m_fSizeY * m_fMultipleSizeY;

			// equip
			m_fPosX = 580.f + (135.f * j);
			m_fPosY = 180.f + (123.f * i);
			m_fSizeX = 82.f;
			m_fSizeY = 82.f;
			m_fMultipleSizeX = 0.3f;
			m_fMultipleSizeY = 0.3f;
			m_sSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matEquip._41 = m_fPosX;
			m_sSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matEquip._42 = WINCY - m_fPosY;
			m_sSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matEquip._11 = m_fSizeX * m_fMultipleSizeX;
			m_sSpaceAry[(INVEN_BUTTON1 + iIndex) - 3].m_matEquip._22 = m_fSizeY * m_fMultipleSizeY;

			iIndex += 1;
		}
	}

	// Mannequin
	m_fPosX = 300.f;
	m_fPosY = 300.f;
	m_fSizeX = 0.5f;
	m_fSizeY = 0.5f;
	m_fMultipleSizeX = 250.f;
	m_fMultipleSizeY = 250.f;
	m_matMannequinWorld._41 = m_fPosX;
	m_matMannequinWorld._42 = WINCY - m_fPosY;
	m_matMannequinWorld._11 = m_fSizeX * m_fMultipleSizeX;
	m_matMannequinWorld._22 = m_fSizeY * m_fMultipleSizeY;
}
void CInventory::Ready_PlayerUI()
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
	m_fPosY = 150.f;
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
	m_matFancyLWorld._42 = 200.f;
	m_matFancyLWorld._11 = m_fSizeX * m_fMultipleSizeX;
	m_matFancyLWorld._22 = m_fSizeY * m_fMultipleSizeY;

	m_fSizeX = 0.4f;
	m_fSizeY = 0.4f;
	m_fMultipleSizeX = 71.f;
	m_fMultipleSizeY = 37.f;
	m_matFancyRWorld._41 = 450.f;
	m_matFancyRWorld._42 = 200.f;
	m_matFancyRWorld._11 = -m_fSizeX * m_fMultipleSizeX;
	m_matFancyRWorld._22 = m_fSizeY * m_fMultipleSizeY;

	m_FancyRc = { 240, WINCY - 220, 240, WINCY - 220 };

	// Shadow
	m_fSizeX = 0.4f;
	m_fSizeY = 0.4f;
	m_fMultipleSizeX = 102.f;
	m_fMultipleSizeY = 47.f;
	m_matShadowWorld._41 = 300.f;
	m_matShadowWorld._42 = 360.f;
	m_matShadowWorld._11 = m_fSizeX * m_fMultipleSizeX;
	m_matShadowWorld._22 = m_fSizeY * m_fMultipleSizeY;

}
void CInventory::Ready_ItemUI()
{	
	// Item - Line
	for (_int i = 0; i < INVEN_LINE - 16; ++i)
	{
		m_fPosX = 850.f;
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
	m_fPosX = 1000.f;
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
	m_sItemStatUIAry[ITEM_HEART].m_matItemStatUI._41 = 590.f;
	m_sItemStatUIAry[ITEM_HEART].m_matItemStatUI._42 = WINCY - 670.f;
	m_sItemStatUIAry[ITEM_HEART].m_matItemStatUI._11 = m_fSizeX * m_fMultipleSizeX;
	m_sItemStatUIAry[ITEM_HEART].m_matItemStatUI._22 = m_fSizeY * m_fMultipleSizeY;

	// Item Damage
	m_fSizeX = 0.4f;
	m_fSizeY = 0.4f;
	m_fMultipleSizeX = 43.f;
	m_fMultipleSizeY = 43.f;
	m_sItemStatUIAry[ITEM_DAMAGE].m_matItemStatUI._41 = 690.f;
	m_sItemStatUIAry[ITEM_DAMAGE].m_matItemStatUI._42 = WINCY - 670.f;
	m_sItemStatUIAry[ITEM_DAMAGE].m_matItemStatUI._11 = m_fSizeX * m_fMultipleSizeX;
	m_sItemStatUIAry[ITEM_DAMAGE].m_matItemStatUI._22 = m_fSizeY * m_fMultipleSizeY;

	// Item Magic
	m_fSizeX = 0.4f;
	m_fSizeY = 0.4f;
	m_fMultipleSizeX = 43.f;
	m_fMultipleSizeY = 43.f;
	m_sItemStatUIAry[ITEM_MAGIC].m_matItemStatUI._41 = 790.f;
	m_sItemStatUIAry[ITEM_MAGIC].m_matItemStatUI._42 = WINCY - 670.f;
	m_sItemStatUIAry[ITEM_MAGIC].m_matItemStatUI._11 = m_fSizeX * m_fMultipleSizeX;
	m_sItemStatUIAry[ITEM_MAGIC].m_matItemStatUI._22 = m_fSizeY * m_fMultipleSizeY;
}
void CInventory::Ready_PlayerFont()
{
	// 골드
	m_sPlayerStatFont[PLAYER_GOLD].m_plStatRc = {
		(LONG)(m_sPlayerUIAry[PLAYER_GOLD].m_matPlUI._41 - 75.f),
		(LONG)(m_sPlayerUIAry[PLAYER_GOLD].m_matPlUI._42 + 110.f),
		(LONG)(m_sPlayerUIAry[PLAYER_GOLD].m_matPlUI._41 - 50.f),
		(LONG)(m_sPlayerUIAry[PLAYER_GOLD].m_matPlUI._42 + 130.f)
	};
	// 아머
	m_sPlayerStatFont[PLAYER_ARMOR].m_plStatRc = {
		(LONG)(m_sPlayerUIAry[PLAYER_ARMOR].m_matPlUI._41 + 40.f),
		(LONG)(m_sPlayerUIAry[PLAYER_ARMOR].m_matPlUI._42 + 110.f),
		(LONG)(m_sPlayerUIAry[PLAYER_ARMOR].m_matPlUI._41 + 65.f),
		(LONG)(m_sPlayerUIAry[PLAYER_ARMOR].m_matPlUI._42 + 130.f)
	};
	// 최대 체력
	m_sPlayerStatFont[PLAYER_HEART].m_plStatRc = {
		(LONG)(m_sPlayerUIAry[PLAYER_HEART].m_matPlUI._41 + 80.f),
		WINCY - 175,
		(LONG)(m_sPlayerUIAry[PLAYER_HEART].m_matPlUI._41 + 80.f),
		WINCY - 175
	};
	// 공격력
	m_sPlayerStatFont[PLAYER_DAMAGE].m_plStatRc = {
		(LONG)(m_sPlayerUIAry[PLAYER_DAMAGE].m_matPlUI._41 + 80.f),
		WINCY - 175,
		(LONG)(m_sPlayerUIAry[PLAYER_DAMAGE].m_matPlUI._41 + 80.f),
		WINCY - 175
	};
	// 마력
	m_sPlayerStatFont[PLAYER_MAGIC].m_plStatRc = {
		(LONG)(m_sPlayerUIAry[PLAYER_MAGIC].m_matPlUI._41 + 80.f),
		WINCY - 175,
		(LONG)(m_sPlayerUIAry[PLAYER_MAGIC].m_matPlUI._41 + 80.f),
		WINCY - 175
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
	m_ItemNameRc = { 590, WINCY - 170, 590, WINCY - 170 };
	m_ItemLvRc = { 590, WINCY - 120, 590, WINCY - 120 };

	// 합산 폰트
	m_ResultHpRc = {
		(LONG)(m_sPlayerUIAry[PLAYER_HEART].m_matPlUI._41 + 80.f),
		WINCY - 145,
		(LONG)(m_sPlayerUIAry[PLAYER_HEART].m_matPlUI._41 + 80.f),
		WINCY - 145
	};
	m_ResultDmgRc = {
		(LONG)(m_sPlayerUIAry[PLAYER_DAMAGE].m_matPlUI._41 + 80.f),
		WINCY - 145,
		(LONG)(m_sPlayerUIAry[PLAYER_DAMAGE].m_matPlUI._41 + 80.f),
		WINCY - 145
	};
	m_ResultMagicRc = {
		(LONG)(m_sPlayerUIAry[PLAYER_MAGIC].m_matPlUI._41 + 80.f),
		WINCY - 145,
		(LONG)(m_sPlayerUIAry[PLAYER_MAGIC].m_matPlUI._41 + 80.f),
		WINCY - 145
	};


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
		if (m_iTranslucent < 240) m_iTranslucent += 10.f;

		Render_PublicUI();

		if (m_eInvenType == INVENTYPE::INVEN_ITEM)
		{
			Render_ItemInventory();
		}

	}


	__super::Render_Object();

}

void CInventory::Render_PublicUI()
{
	// BackGround
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iTranslucent, 255, 255, 255));
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_BKG]);

	m_pInventoryTexCom[INVEN_BKG]->Render_Texture();
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	// Tab Button - Armor
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_ATABBUTTON]);
	m_pInventoryTexCom[INVEN_ATABBUTTON]->Render_Texture();
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


	// Tab Button - Skill
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_STABBUTTON]);
	m_pInventoryTexCom[INVEN_STABBUTTON]->Render_Texture();
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


	// Tab Button Image - Armor Texture
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_ARMORTEX]);
	m_pInventoryTexCom[INVEN_ARMORTEX]->Render_Texture();
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


	// Tab Button Image - Skill Texture
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_SKILLTEX]);
	m_pInventoryTexCom[INVEN_SKILLTEX]->Render_Texture();
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	// Cancel Button
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_CANCELBUTTON]);
	m_pInventoryTexCom[INVEN_CANCELBUTTON]->Render_Texture();
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	// Tab Line 
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_TABLINE]);
	m_pInventoryTexCom[INVEN_TABLINE]->Render_Texture();
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


	// Button 
	for (_int i = 0; i < INVEN_BUTTON12 - 2; ++i)
	{
		// 아이템 있음
		if (m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bIsSpace == true && m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bOnSpace == false)
		{
			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace);
			m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceIsTex->Render_Texture();
			m_pBufferCom->Render_Buffer();
			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		}
		// 아이템 선택
		else if (m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bIsSpace == true && m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bOnSpace == true)
		{
			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace);
			m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceSelectTex->Render_Texture();
			m_pBufferCom->Render_Buffer();
			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		}
		// 아이템 없음
		else
		{
			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace);
			m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceNoneTex->Render_Texture();
			m_pBufferCom->Render_Buffer();
			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		}
		// 무기 선택 미니 아이콘
		if (m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bEquip)
		{
			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matEquip);
			m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceEquipTex->Render_Texture();
			m_pBufferCom->Render_Buffer();
			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

		}
	}

	// Shadow
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matShadowWorld);
	m_pShadowTexCom->Render_Texture();
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	// Mannequin
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matMannequinWorld);
	m_pMannequinAniCom->Render_Animation();
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
// Item
void CInventory::Render_ItemInventory()
{
	Render_PlayerUI();
	ItemPicking_UI();
	Render_ItemUI();
	Render_PlayerItemFont();
}
void CInventory::Render_PlayerUI()
{
	for (_int i = 0; i < m_vecItem.size(); ++i)
	{
		dynamic_cast<CItem_Weapon*>(m_vecItem[i])->Set_InvenTrans(
			m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._41,
			m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._42
		);
		m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bIsSpace = true;
	}
	// PlayerUI
	for (_int i = 0; i < PLAYER_UI_END; ++i)
	{
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sPlayerUIAry[i].m_matPlUI);
		m_sPlayerUIAry[i].m_pPlUITex->Render_Texture();
		m_pBufferCom->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}

	// Fancy
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matFancyLWorld);
	m_pFancyLTexCom->Render_Texture();
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matFancyRWorld);
	m_pFancyRTexCom->Render_Texture();
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
void CInventory::Render_ItemUI()
{
	if (m_sEquipCheck.m_bShowUI)
	{
		// Line
		for (_int i = 0; i < INVEN_LINE - 16; ++i)
		{
			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sLineAry[(INVEN_LINE + i) - 19].m_matLine);
			m_sLineAry[(INVEN_LINE + i) - 19].m_pLineTex->Render_Texture();
			m_pBufferCom->Render_Buffer();
			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		}

		// OK 
		if (m_sEquipCheck.m_eEquipCheck == EQUIP_OK)
		{
			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sEquipCheck.m_mateCheck);
			m_sEquipCheck.m_pOkTex->Render_Texture();
			m_pBufferCom->Render_Buffer();
			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		}

		// NO
		if (m_sEquipCheck.m_eEquipCheck == EQUIP_NO)
		{
			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sEquipCheck.m_mateCheck);
			m_sEquipCheck.m_pNoTex->Render_Texture();
			m_pBufferCom->Render_Buffer();
			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		}

	}

}
void CInventory::Render_PlayerItemFont()
{
	//								Player Font
	// Gold
	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, to_wstring((int)(m_pPlayer->Get_StatInfo().fGold)).c_str(), -1,
		&m_sPlayerStatFont[PLAYER_GOLD].m_plStatRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
	// Armor
	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, L"0/0", -1,
		&m_sPlayerStatFont[PLAYER_ARMOR].m_plStatRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

	// Heart
	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, to_wstring((int)(m_pPlayer->Get_StatInfo().fMaxHP)).c_str(), -1,
		&m_sPlayerStatFont[PLAYER_HEART].m_plStatRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(153, 102, 0, 0));

	// Damage
	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, to_wstring((int)(m_pPlayer->Get_StatInfo().fAD)).c_str(), -1,
		&m_sPlayerStatFont[PLAYER_DAMAGE].m_plStatRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(153, 102, 0, 0));

	// Magic
	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, to_wstring(10).c_str(), -1,
		&m_sPlayerStatFont[PLAYER_MAGIC].m_plStatRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(153, 102, 0, 0));

	// Fancy
	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, L"Statistics", -1,
		&m_FancyRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(153, 102, 0, 0));
}
void CInventory::ItemPicking_UI()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	D3DVIEWPORT9 ViewPort;

	m_pGraphicDev->GetViewport(&ViewPort);

	pt.y = WINCY - pt.y;

	for (_int i = 0; i < INVEN_BUTTON12 - 2; ++i)
	{
		RECT SpaceRT;
		SpaceRT.left = m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._41 - (m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._11 * 0.5f);
		SpaceRT.right = m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._41 + (m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._11 * 0.5f);
		SpaceRT.top = m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._42 - (m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._22 * 0.5f);
		SpaceRT.bottom = m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._42 + (m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_matSpace._22 * 0.5f);

		// 피킹
		if (PtInRect(&SpaceRT, pt))
		{
			// 황금 박스로 변경
			m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bOnSpace = true;

			// 마우스 클릭 시
			if (CInputDev::GetInstance()->Key_Down(MK_LBUTTON))
			{
				if (!m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bEquip && m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bIsSpace)
				{
					// 이미 선택된 애들은 해제
					for (_int i = 0; i < INVEN_BUTTON12 - 2; ++i)
					{
						m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bEquip = false;
					}
					m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bEquip = true;
				}
				else
					m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bEquip = false;
			}

			Item_StatView(i);

			// EquipCheck 버튼
			if (m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bEquip)
			{
				m_sEquipCheck.m_eEquipCheck = EQUIP_OK;
			}
			else if (!m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bEquip)
			{
				m_sEquipCheck.m_eEquipCheck = EQUIP_NO;
			}
			//////////////////

		}
		// 픽킹 상태가 아닐 때
		else
		{
			m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_bOnSpace = false;
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
			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_sItemStatUIAry[i].m_matItemStatUI);
			m_sItemStatUIAry[i].m_pItemStatUITex->Render_Texture();
			m_pBufferCom->Render_Buffer();
			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		}

		//								Item Font
		// Heart
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, to_wstring((int)(pWeapon->Get_StatInfo().fMaxHP)).c_str(), -1,
			&m_sItemStatFont[ITEM_HEART].m_pItemStatRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(153, 102, 0, 0));

		// Damage
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, to_wstring((int)(pWeapon->Get_StatInfo().fAD)).c_str(), -1,
			&m_sItemStatFont[ITEM_DAMAGE].m_pItemStatRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(153, 102, 0, 0));

		// Magic
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, to_wstring(10).c_str(), -1,
			&m_sItemStatFont[ITEM_MAGIC].m_pItemStatRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(153, 102, 0, 0));

		// Name
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, pWeapon->Get_Name(), -1,
			&m_ItemNameRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(153, 102, 0, 0));

		// LV
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, L"LV 1", -1,
			&m_ItemLvRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(153, 102, 0, 0));

		// 합산 폰트
		// Heart
		_int iResult = (m_pPlayer->Get_StatInfo().fMaxHP
			+ pWeapon->Get_StatInfo().fMaxHP) - m_pPlayer->Get_StatInfo().fMaxHP;
		
		wstring HpResultStr;
		if (iResult > 0)		HpResultStr = L"+" + to_wstring(iResult);
		else if (iResult < 0)	HpResultStr = L"-" + to_wstring(iResult);
		else					HpResultStr = to_wstring(iResult);
		if (!m_sSpaceAry[(INVEN_BUTTON1 + _Index) - 3].m_bEquip)
		{
			CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, HpResultStr.c_str(), -1,
				&m_ResultHpRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 153, 0));
		}


		// Damage
		iResult = (m_pPlayer->Get_StatInfo().fAD
			+ pWeapon->Get_StatInfo().fAD) - m_pPlayer->Get_StatInfo().fAD;

		wstring DmgResultStr;
		if (iResult > 0)		DmgResultStr = L"+" + to_wstring(iResult);
		else if (iResult < 0)	DmgResultStr = L"-" + to_wstring(iResult);
		else					DmgResultStr = to_wstring(iResult);
		if (!m_sSpaceAry[(INVEN_BUTTON1 + _Index) - 3].m_bEquip)
		{
			CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, DmgResultStr.c_str(), -1,
				&m_ResultDmgRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 153, 0));
		}
		// Magic(미구현이라 보류)
		//iResult = (m_pPlayer->Get_StatInfo().fMaxHP
		//	+ pWeapon->Get_StatInfo().fMaxHP) - m_pPlayer->Get_StatInfo().fMaxHP;
		//CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, to_wstring(10).c_str(), -1,
		//	&m_sItemStatFont[ITEM_MAGIC].m_pItemStatRc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(200, 0, 0, 0));

	}
}
// Skill



HRESULT CInventory::Add_Component()
{
	CComponent* pComponent = nullptr;

	// RcTex Com
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


#pragma region Texture


	// BackGround
	pComponent = m_pInventoryTexCom[INVEN_BKG] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_BKG", this));
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
	
	// UI - Button
	for (_int i = 0; i < INVEN_BUTTON12 - 2; ++i)
	{
		// 아이템 존재x
		pComponent = m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceNoneTex
			= dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_blank", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
		// 아이템 존재
		pComponent = m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceIsTex
			= dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
		// 아이템 선택
		pComponent = m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceSelectTex
			= dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_Gold", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
		// 무기 선택 미니 아이콘
		pComponent = m_sSpaceAry[(INVEN_BUTTON1 + i) - 3].m_pSpaceEquipTex
			= dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Weapon_Select", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	}

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
	pComponent = m_pInventoryTexCom[INVEN_SORTBUTTON] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_Plain", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// Mannequin
	pComponent = m_pMannequinTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fIdle", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// Shadow
	pComponent = m_pShadowTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Shadow_Creature", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// Fancy
	pComponent = m_pFancyLTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Fancy", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pFancyRTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Fancy", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


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



	// UI - Item Stat START

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

	return S_OK;
}

void CInventory::Key_Input()
{
	if (CInputDev::GetInstance()->Key_Down(VK_TAB))
	{
		m_bIsOn = !m_bIsOn;
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
