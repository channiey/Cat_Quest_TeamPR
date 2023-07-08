#pragma once
#include "UI.h"

class CTabUI : public CUI  // ����Ʈ ��� | ��ŷ�� ������ ������ UI �Դϴ�
{

protected:

	explicit CTabUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTabUI(const CTabUI& rhs);
	virtual ~CTabUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:

	void			Picking_UI();


protected:

	CTexture* m_pTextureCom = nullptr;

	bool		m_bPick;

	RECT       m_rcUI;

	_matrix		matWorld;

	_float	m_fX;
	_float	m_fY;

	_float	m_fSizeX;
	_float	m_fSizeY;

private:

	HRESULT		Add_Component();


public:

	static CTabUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;



};

