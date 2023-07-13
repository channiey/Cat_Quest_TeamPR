#pragma once
#include "UI.h"

class CFieldSkillUI : public CUI  // 뷰포트 사용 | 피킹이 가능한 형태의 UI 입니다
{

protected:

	explicit CFieldSkillUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CFieldSkillUI(const CFieldSkillUI& rhs);
	virtual ~CFieldSkillUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;
	void					Picking_UI();
	void					Mouse_Input();

private:
	RECT					m_rcUI[4];
	
	
	_bool					m_bPick;

	_bool					m_bIsOn;


public:
	static CFieldSkillUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;

};

