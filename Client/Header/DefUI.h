#pragma once
#include "UI.h"



class CDefUI : public CUI     // 뷰포트 사용 | 화면에 고정된 표시를 위한 UI  프로토타입 입니다.
{

protected:

	explicit CDefUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CDefUI(const CDefUI& rhs);
	virtual ~CDefUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;

	void	Follow_Player();

private:
	_uint	m_iTranslucent;
	_float	m_fAcc;
	_bool	m_bIsReach;

public:
	static CDefUI*			Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;
};

