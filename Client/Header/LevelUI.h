#pragma once
#include "UI.h"



class CLevelUI : public CUI
{

protected:

	explicit CLevelUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CLevelUI(const CLevelUI& rhs);
	virtual ~CLevelUI();


	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;



protected:

	CTexture* m_pTextureCom = nullptr;


	_matrix matWorld;

	float m_fX;
	float m_fY;

	float m_fSizeX;
	float m_fSizeY;

private:

	HRESULT		Add_Component();


public:

	static CLevelUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;
};

