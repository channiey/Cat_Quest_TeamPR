#pragma once
#include "UI.h"

#define		MAX_SKILL_SLOT 4

BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;
class CGameObject;
class CAnimation;

END
// 아이템, 스킬 인벤토리 구분
enum class INVENTYPE { INVEN_ITEM, INVEN_SKILL, INVEN_END };
// OK, NO 버튼
enum EQUIPCHECK{ EQUIP_NONE, EQUIP_OK, EQUIP_NO };
// Player UI
enum PLAYERUI  { PLAYER_GOLD, PLAYER_ARMOR, PLAYER_HEART, PLAYER_DAMAGE, PLAYER_MAGIC, PLAYER_UI_END };
// Item UI
enum ITEMui    { ITEM_HEART, ITEM_DAMAGE, ITEM_MAGIC, ITEMUI_END};

// 아이템 칸
struct tagItemSpace
{
	_matrix     m_matSpace;
	_matrix		m_matEquip;
	CTexture*	m_pSpaceNoneTex;
	CTexture*	m_pSpaceIsTex;
	CTexture*	m_pSpaceSelectTex;
	CTexture*	m_pSpaceEquipTex;
	_bool		m_bIsSpace = false;
	_bool		m_bOnSpace = false;
	_bool		m_bEquip = false;
};
// 스킬 칸
struct tagSkillSpace
{
	_matrix     m_matSpace;
	_matrix		m_matEquip;
	CTexture*	m_pSpaceNoneTex;
	CTexture*	m_pSpaceIsTex;
	CTexture*	m_pSpaceSelectTex;
	_bool		m_bIsSpace = false;
	_bool		m_bOnSpace = false;
	_bool		m_bEquip = false;
};
// 라인
struct tagLine
{
	_matrix     m_matLine;
	CTexture*   m_pLineTex;
};
// 장착여부
struct tagEquipCheck
{
	_matrix     m_mateCheck;
	CTexture*   m_pOkTex;
	CTexture*   m_pNoTex;
	EQUIPCHECK  m_eEquipCheck;
	_bool		m_bShowUI;
};
// 플레이어 UI
struct tagPlayerUI
{
	_matrix     m_matPlUI;
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
	CTexture*   m_pItemStatUITex;
};
// 아이템 스텟 폰트 박스
struct tagItemStatFont
{
	RECT		m_pItemStatRc;
};

// Skill Ring
struct tagSkillRingUI
{
	_matrix     m_matEmptySkillUI;
	_matrix     m_matSkillRingUI;
	_matrix		m_matSkillNumUI;
	CTexture*	m_pSkillRingUITex;
	CTexture*	m_pSkillEmptyUITex;
	CTexture*   m_pSkillNumUITex;

	_bool		m_bIsSkill;
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
#pragma region Ready
	// Ready
	void					Ready_WorldMatrix();
	void					Ready_PublicUI();
	// Item
	void					Ready_ItemPlayerUI();
	void					Ready_ItemUI();
	void					Ready_ItemPlayerFont();
	void					Ready_ItemFont();
	// Skill
	void					Ready_SkillUI();
#pragma endregion

#pragma region Render
	// Render Public
	void					Render_PublicUI();
	// Render Item
	void					Render_ItemInventory();
	void					Render_PlayerStatUI();
	void					Render_ItemUI();
	void					Render_PlayerItemFont();
	// Render Skill
	void					Render_SkillInventory();
	void					Render_SkillUI();
	void					Render_SkillFont();
#pragma endregion

#pragma region Update
	void				    Item_StatView(_int _Index);
	void					Key_Input();
	void					Mouse_Update();

	void					ItemPicking_UI();
	void					SkillPicking_UI();
	void					TabPicking_UI();
#pragma endregion

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

private:
#pragma region System
	_bool					m_bIsOn; // 활성 여부
	_bool					m_bAlphaSet; // 알파 변수
	_int					m_iTranslucent; // 온오프 알파값

	CPlayer*				m_pPlayer;	
	vector<CGameObject*>	m_vecItem; // 아이템 배열
	_int					m_iHaveKey; // 열쇠 

	INVENTYPE				m_eInvenType; // 아이템인지 스킬인지
#pragma endregion

	CTexture*				m_pInventoryTexCom[INVENTORYID_END]; // 기존에 있던 배열
	_matrix                 m_matInventoryWolrd[INVENTORYID_END]; // 기존에 있던 배열

#pragma region UI
	// 아이템 인벤토리 관련
	tagItemSpace			m_sItemSpaceAry[INVEN_BUTTON12 - 2]; // 아이템 칸 배열
	tagEquipCheck			m_sEquipCheck; // 장비 장착 여부 구조체
	tagPlayerUI				m_sPlayerUIAry[PLAYER_UI_END]; // 플레이어 UI 배열
	tagPlayerStatFont		m_sPlayerStatFont[PLAYER_UI_END]; // 플레이어 Stat 폰트 배열
	tagItemStatUI			m_sItemStatUIAry[ITEMUI_END]; // 아이템 스텟 UI 배열
	tagItemStatFont			m_sItemStatFont[ITEMUI_END]; // 아이템 스텟 Font

	// 스킬 인벤토리 관련
	tagSkillSpace			m_sSkillSpaceAry[INVEN_BUTTON12 - 2]; // 스킬 칸 배열
	tagSkillRingUI			m_sSkillRingAry[MAX_SKILL_SLOT];
	_matrix					m_sBigSkillRing;
	CTexture*				m_pBigSkillRingTex;

	// 공용
	tagLine					m_sLineAry[INVEN_LINE - 16]; // 라인 배열


#pragma endregion

#pragma region 렉트
	// 아이템 스텟 폰트
	RECT		m_ItemNameRc;
	RECT		m_ItemLvRc;
	// 능력 증가치 폰트
	RECT		m_ResultHpRc;
	RECT		m_ResultDmgRc;
	RECT		m_ResultMagicRc;
#pragma endregion

#pragma region 마네킹
	// 마네킹
	CGameObject*	m_pMannequin;
	CTexture*		m_pMannequinTexCom;
	CAnimation*		m_pMannequinAniCom;
	_matrix			m_matMannequinWorld;

	CTexture*		m_pShadowTexCom;
	_matrix			m_matShadowWorld;

#pragma endregion
	
#pragma region  fancy

	// 왼쪽
	CTexture*	 m_pFancyLTexCom;
	_matrix		 m_matFancyLWorld;
	// 오른쪽
	CTexture*	 m_pFancyRTexCom;
	_matrix		 m_matFancyRWorld;
	// 폰트
	RECT		 m_FancyRc;

#pragma endregion
	
#pragma region CursorPt
	CTexture*	 m_pCursorTexCom;
	_matrix		 m_matCursorWorld;
#pragma endregion

#pragma region BAR
	CTexture*	 m_pBarTexCom;
	_matrix		 m_matBar[8];

	_float		m_fHpRatio;

	_float		m_fHpBarPosX;
	_float		m_fHpBarPosY;

	_float		m_fHpBarSizeX;
	_float		m_fHpBarSizeY;
	
	_float		m_fMpRatio;

	_float		m_fMpBarPosX;
	_float		m_fMpBarPosY;

	_float		m_fMpBarSizeX;
	_float		m_fMpBarSizeY;

	_float		m_fCapSizeX;
	_float		m_fCapSizeY;

#pragma endregion



public: 

	static CInventory* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void			Free() override;


};

