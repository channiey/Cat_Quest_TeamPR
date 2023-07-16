#pragma once
#include "UI.h"

class CMonster;

class CMonHpUI : public CUI     // 뷰포트 사용 | 화면에 고정된 표시를 위한 UI  프로토타입 입니다.
{

protected:

	explicit CMonHpUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMonHpUI(const CMonHpUI& rhs);
	virtual ~CMonHpUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;

	void					Follow_Owner();
	void					Set_Owner(CGameObject* pMonster) { m_pMonster = pMonster; }

private:
	CTransform*				m_pUITransformCom[4];
	CGameObject*			m_pMonster;
	_float					m_fHpRatio;

public:
	static CMonHpUI*			Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pMonster);


protected:
	virtual void			Free() override;
};

