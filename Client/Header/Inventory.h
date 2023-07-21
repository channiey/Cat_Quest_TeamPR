#pragma once
#include "UI.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;
class CGameObject;
class CAnimation;

END
// ������, ��ų �κ��丮 ����
enum class INVENTYPE { INVEN_ITEM, INVEN_SKILL, INVEN_END };
// OK, NO ��ư
enum EQUIPCHECK{ EQUIP_NONE, EQUIP_OK, EQUIP_NO };
// Player UI
enum PLAYERUI  { PLAYER_HPBAR, PLAYER_MPBAR, PLAYER_GOLD, PLAYER_ARMOR, PLAYER_HEART, PLAYER_DAMAGE, PLAYER_MAGIC, PLAYER_UI_END };
// Item UI
enum ITEMui    { ITEM_HEART, ITEM_DAMAGE, ITEM_MAGIC, ITEMUI_END};

// ĭ
struct tagSpace
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
// ����
struct tagLine
{
	_matrix     m_matLine;
	CTexture*   m_pLineTex;
};
// ��������
struct tagEquipCheck
{
	_matrix     m_mateCheck;
	CTexture*   m_pOkTex;
	CTexture*   m_pNoTex;
	EQUIPCHECK  m_eEquipCheck;
	_bool		m_bShowUI;
};
// �÷��̾� UI
struct tagPlayerUI
{
	_matrix     m_matPlUI;
	CTexture*	m_pPlUITex;
};
// �÷��̾� ���� ��Ʈ �ڽ�
struct tagPlayerStatFont
{
	RECT		m_plStatRc;
};
// ������ ���� UI
struct tagItemStatUI
{
	_matrix     m_matItemStatUI;
	CTexture*   m_pItemStatUITex;
};
// ������ ���� ��Ʈ �ڽ�
struct tagItemStatFont
{
	RECT		m_pItemStatRc;
};


class CPlayer;

class CInventory : public CUI   // ����Ʈ ��� | ��ŷ�� ������ ������ UI �Դϴ�
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
	// Ready
	void					Ready_WorldMatrix();
	void					Ready_PublicUI();
	void					Ready_PlayerUI();
	void					Ready_ItemUI();
	void					Ready_PlayerFont();
	void					Ready_ItemFont();

	// Render
	void					Render_PublicUI();
	void					Render_ItemInventory();
	void					Render_PlayerUI();
	void					Render_ItemUI();
	void					Render_PlayerItemFont();

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
	void					ItemPicking_UI();
	void				    Item_StatView(_int _Index);
	void					Key_Input();

private:
	_bool					m_bIsOn; // Ȱ�� ����
	_bool					m_bAlphaSet; // ���� ����
	_int					m_iTranslucent; // �¿��� ���İ�

	CPlayer*				m_pPlayer;	
	vector<CGameObject*>	m_vecItem; // ������ �迭
	_int					m_iHaveKey; // ���� 

	CTexture*				m_pInventoryTexCom[INVENTORYID_END]; // ������ �ִ� �迭
	_matrix                 m_matInventoryWolrd[INVENTORYID_END]; // ������ �ִ� �迭

	INVENTYPE				m_eInvenType; // ���������� ��ų����
	_bool					m_bPick[INVENTORYID_END]; // �����

#pragma region ����ü
	// ����
	tagSpace				m_sSpaceAry[INVEN_BUTTON12 - 2]; // ĭ �迭

	// ������ �κ��丮 ����
	
	tagEquipCheck			m_sEquipCheck; // ��� ���� ���� ����ü
	tagLine					m_sLineAry[INVEN_LINE - 16]; // ���� �迭
	tagPlayerUI				m_sPlayerUIAry[PLAYER_UI_END]; // �÷��̾� UI �迭
	tagPlayerStatFont		m_sPlayerStatFont[PLAYER_UI_END]; // �÷��̾� Stat ��Ʈ �迭
	tagItemStatUI			m_sItemStatUIAry[ITEMUI_END]; // ������ ���� UI �迭
	tagItemStatFont			m_sItemStatFont[ITEMUI_END]; // ������ ���� Font
#pragma endregion

#pragma region ��Ʈ
	// ������ ���� ��Ʈ
	RECT		m_ItemNameRc;
	RECT		m_ItemLvRc;
	// �ɷ� ����ġ ��Ʈ
	RECT		m_ResultHpRc;
	RECT		m_ResultDmgRc;
	RECT		m_ResultMagicRc;
#pragma endregion

#pragma region ����ŷ
	// ����ŷ
	CGameObject*	m_pMannequin;
	CTexture*		m_pMannequinTexCom;
	CAnimation*		m_pMannequinAniCom;
	_matrix			m_matMannequinWorld;

	CTexture*		m_pShadowTexCom;
	_matrix			m_matShadowWorld;

#pragma endregion
	
#pragma region  fancy

	// ����
	CTexture*	 m_pFancyLTexCom;
	_matrix		 m_matFancyLWorld;
	// ������
	CTexture*	 m_pFancyRTexCom;
	_matrix		 m_matFancyRWorld;
	// ��Ʈ
	RECT		 m_FancyRc;

#pragma endregion
	

		
public: 

	static CInventory* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void			Free() override;


};

