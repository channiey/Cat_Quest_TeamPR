#pragma once
#include "UI.h"

class CManaBarUI : public CUI    // 월드 스페이스 사용 |
{
protected:

	explicit CManaBarUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CManaBarUI(const CManaBarUI& rhs);
	virtual ~CManaBarUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual	HRESULT			Add_Component() override;

	void					Follow_Pos();

public:

	static CManaBarUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void			Free() override;


};

