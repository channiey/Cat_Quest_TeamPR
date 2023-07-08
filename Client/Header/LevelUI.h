#pragma once
#include "UI.h"



class CLevelUI : public CUI     // 뷰포트 사용 | 화면에 고정된 표시를 위한 UI  프로토타입 입니다.
{

protected:

	explicit CLevelUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CLevelUI(const CLevelUI& rhs);
	virtual ~CLevelUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;



protected:

	CTexture* m_pTextureCom = nullptr;


	_matrix matWorld;

	_float m_fX;
	_float m_fY;

	_float m_fSizeX;
	_float m_fSizeY;

private:

	HRESULT		Add_Component();


public:

	static CLevelUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;
};

