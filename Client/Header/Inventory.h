#pragma once
#include "UI.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;
class CGameObject;

END

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

	vector<CGameObject*>	m_vecItem;

public: 

	static CInventory* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void			Free() override;


};

