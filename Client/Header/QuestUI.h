#pragma once
#include "UI.h"

class CQuestUI : public CUI     
{

protected:

	explicit CQuestUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CQuestUI(const CQuestUI& rhs);
	virtual ~CQuestUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:

	virtual HRESULT			Add_Component() override;

private:
	_uint					m_iZoomState;

public:

	static CQuestUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;
};

