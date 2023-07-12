#pragma once
#include "UI.h"
#include "GameObject.h" 

BEGIN(Engine)

class CGameObject;

END

class CPlayer;

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
	void	Set_IndicTarget(CGameObject* pTarget) { m_pTarget = pTarget; }


	void	Get_ViewPos_Target();

private:
	CGameObject*			m_pTarget;
	CPlayer*				m_pPlayer;

	_vec3					m_vIndicDir;

	_bool					m_bIsShirk;
	_bool					m_bIsExpand;


private:
	virtual HRESULT			Add_Component() override;

public:
	static CIndicatorUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void			Free() override;
};

