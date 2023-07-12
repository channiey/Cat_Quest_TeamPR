#pragma once
#include "UI.h"
#include "GameObject.h" 

BEGIN(Engine)

class CGameObject;

END

class CIndicatorUI : public CUI     // ����Ʈ ��� | ȭ�鿡 ������ ǥ�ø� ���� UI  ������Ÿ�� �Դϴ�.
{

protected:
	explicit CIndicatorUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CIndicatorUI(const CIndicatorUI& rhs);
	virtual ~CIndicatorUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:

private:
	virtual HRESULT			Add_Component() override;

private:
	CGameObject*			m_pTarget;

public:
	static CIndicatorUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;
};

