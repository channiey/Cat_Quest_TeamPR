#pragma once
#include "UI.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;
class CGameObject;

END
// OK, NO ��ư
enum EQUIPCHECK{ EQUIP_NONE, EQUIP_OK, EQUIP_NO };

// ĭ
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
// ����
struct tagLine
{
	_matrix     m_matLine;
	CTransform* m_pLineTrans;
	CTexture*   m_pLineTex;
};
// ��������
struct tagEquipCheck
{
	_matrix     m_mateCheck;
	CTransform* m_peCheckTrans;
	CTexture*   m_pOkTex;
	CTexture*   m_pNoTex;
	EQUIPCHECK  m_eEquipCheck = EQUIP_NONE;
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
	void					Set_Player(CGameObject* _pPlayer) { m_pPlayer = _pPlayer; }

	// Set
	void					Add_Item(CGameObject* _pItem) { m_vecItem.push_back(_pItem); }
	// Get
protected:
	virtual HRESULT			Add_Component();
	void					Picking_UI();
	void					Key_Input();




private:
	CGameObject*			m_pPlayer;	

	CTexture*				m_pInventoryTexCom[INVENTORYID_END];
	CTransform*				m_pInventortyTransCom[INVENTORYID_END];

	_bool					m_bIsOn;
	_bool					m_bShirnk;

	_bool					m_bPick[INVENTORYID_END];
	RECT					m_rcPick[INVENTORYID_END];

	_matrix                 m_matInventoryWolrd[INVENTORYID_END];

	// ��� ���� ���� ����ü
	tagEquipCheck			m_sEquipCheck;
	// ĭ �迭
	tagSpace				m_sSpaceAry[INVEN_BUTTON12 - 2];
	// ���� �迭
	tagLine					m_sLineAry[INVEN_LINE - 16];
	// ������ �迭
	vector<CGameObject*>	m_vecItem;

public: 

	static CInventory* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void			Free() override;


};

