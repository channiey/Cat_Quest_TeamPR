#pragma once
#include "UI.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;
class CGameObject;
class CAnimation;

END
// OK, NO 버튼
enum EQUIPCHECK{ EQUIP_NONE, EQUIP_OK, EQUIP_NO };
// Player UI
enum PLAYERUI  { PLAYER_HPBAR, PLAYER_MPBAR, PLAYER_GOLD, PLAYER_ARMOR, PLAYER_HEART, PLAYER_DAMAGE, PLAYER_MAGIC, PLAYER_UI_END };
// Item UI
enum ITEMui    { ITEM_HEART, ITEM_DAMAGE, ITEM_MAGIC, ITEMUI_END};

// 칸
struct tagSpace
{
	_matrix     m_matSpace;
	_matrix		m_matEquip;
	CTransform* m_pSpaceTrans;
	CTexture*	m_pSpaceNoneTex;
	CTexture*	m_pSpaceIsTex;
	CTexture*	m_pSpaceSelectTex;
	CTexture*	m_pSpaceEquipTex;
	_bool		m_bIsSpace = false;
	_bool		m_bOnSpace = false;
	_bool		m_bEquip = false;
};
// 라인
struct tagLine
{
	_matrix     m_matLine;
	CTransform* m_pLineTrans;
	CTexture*   m_pLineTex;
};
// 장착여부
struct tagEquipCheck
{
	_matrix     m_mateCheck;
	CTransform* m_peCheckTrans;
	CTexture*   m_pOkTex;
	CTexture*   m_pNoTex;
	EQUIPCHECK  m_eEquipCheck;
};
// 플레이어 UI
struct tagPlayerUI
{
	_matrix     m_matPlUI;
	CTransform* m_pPlUITrans;
	CTexture*	m_pPlUITex;
};
// 플레이어 스텟 폰트 박스
struct tagPlayerStatFont
{
	RECT		m_plStatRc;
};
// 아이템 스텟 UI
struct tagItemStatUI
{
	_matrix     m_matItemStatUI;
	CTransform* m_pItemStatUITrans;
	CTexture*   m_pItemStatUITex;
};
// 아이템 스텟 폰트 박스
struct tagItemStatFont
{
	RECT		m_pItemStatRc;
};


class CPlayer;

class CInventory : public CUI   // 뷰포트 사용 | 피킹이 가능한 형태의 UI 입니다
{
protected:

	explicit CInventory(LPDIRECT3DDEVICE9 pGraphicDevr);
	explicit CInventory(const CInventory& rhs);
	virtual ~CInventory();


public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	// Item
	void					Add_Item(CGameObject* _pItem) { m_vecItem.push_back(_pItem); }

	// Key
	void					Set_HaveKey(_bool _isAdd)
	{
		if (_isAdd) m_iHaveKey += 1;
		else if (!_isAdd && m_iHaveKey > 0) m_iHaveKey -= 1;
	}
	_int					Get_HaveKey() { return m_iHaveKey; }

protected:
	virtual HRESULT			Add_Component();
	void					Picking_UI();
	void				    Item_StatView(_int _Index);
	void					Key_Input();

private:
	CPlayer*				m_pPlayer;	

	CTexture*				m_pInventoryTexCom[INVENTORYID_END];
	CTransform*				m_pInventortyTransCom[INVENTORYID_END];

	_bool					m_bIsOn;
	_bool					m_bShirnk;

	_bool					m_bPick[INVENTORYID_END];
	// RECT					m_rcStatFont[];

	_matrix                 m_matInventoryWolrd[INVENTORYID_END];

	// 장비 장착 여부 구조체
	tagEquipCheck			m_sEquipCheck;
	// 칸 배열
	tagSpace				m_sSpaceAry[INVEN_BUTTON12 - 2];
	// 라인 배열
	tagLine					m_sLineAry[INVEN_LINE - 16];
	// 아이템 배열
	vector<CGameObject*>	m_vecItem;
	// 열쇠 
	_int					m_iHaveKey;
	// 마네킹
	CGameObject* m_pMannequin;
	CTexture*	 m_pMannequinTexCom;
	CTransform*	 m_pMannequinTransCom;
	CAnimation*  m_pMannequinAniCom;
	_matrix		 m_matMannequinWorld;
	// 플레이어 UI 배열
	tagPlayerUI  m_sPlayerUIAry[PLAYER_UI_END];
	// 플레이어 Stat 폰트 배열
	tagPlayerStatFont m_sPlayerStatFont[PLAYER_UI_END];
	// 아이템 스텟 UI 배열
	tagItemStatUI m_sItemStatUIAry[ITEMUI_END];
	// 아이템 스텟 Font
	tagItemStatFont m_sItemStatFont[ITEMUI_END];
	// 아이템 스텟 폰트
	RECT		m_ItemNameRc;
	RECT		m_ItemLvRc;
	// 증가치 폰트
	RECT		m_ResultHpRc;
	RECT		m_ResultDmgRc;
	RECT		m_ResultMagicRc;


		
public: 

	static CInventory* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void			Free() override;


};

