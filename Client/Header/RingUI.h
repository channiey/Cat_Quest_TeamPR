#pragma once
#include "UI.h"



class CRingUI : public CUI     // ����Ʈ ��� | ȭ�鿡 ������ ǥ�ø� ���� UI  ������Ÿ�� �Դϴ�.
{

protected:

	explicit CRingUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRingUI(const CRingUI& rhs);
	virtual ~CRingUI();

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
	static CRingUI*			Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;
};

