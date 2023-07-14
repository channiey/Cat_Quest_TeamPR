#pragma once
#include "UI.h"

class CPlayer;

class CManaUI : public CUI     // ����Ʈ ��� | ȭ�鿡 ������ ǥ�ø� ���� UI  ������Ÿ�� �Դϴ�.
{

protected:

	explicit CManaUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CManaUI(const CManaUI& rhs);
	virtual ~CManaUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;

	void					Follow_Player();

private:
	CTransform*				m_pUITransformCom[4];

	CPlayer*				m_pPlayer;
	_float					m_fMpRatio;

public:
	static CManaUI*			Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;
};

