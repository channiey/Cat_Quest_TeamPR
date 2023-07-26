#pragma once


/*

	*	�� ������Ʈ�� �ش� Ŭ������ ��ӹ޾� �����ȴ�.
	
	*	��������� ������������Ʈ ���͸� ���� ������, �ش� ������������Ʈ���� �÷��̾�� �浹�� �ش� Ŭ������ Enter ~ Exit Player �Լ��� ȣ���ϰ� �ȴ�.
	
	*	������ �������z ���ʹ� �浹 �˻���̸�, ������ ���� �� ó���� �ش� Ŭ������ ��ӹ޾� ������ �Ļ�Ŭ�������� �����Ѵ�.

*/

#include "GameObject.h"

class CRangeObj;

class CIsland : public Engine::CGameObject
{
public:
	explicit CIsland(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CIsland(const CIsland& rhs);
	virtual ~CIsland();

public:
	virtual HRESULT		Ready_Object(void) override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object(void) override;
	virtual void		Render_Object(void) override;

public:
	virtual void		OnCollision_Enter(CGameObject* _pColObj);
	virtual void		OnCollision_Stay(CGameObject* _pColObj);
	virtual void		OnCollision_Exit(CGameObject* _pColObj);

private:
	HRESULT				Add_Component(void);

protected:
	virtual HRESULT		Add_RangeObj();

public:
	virtual void		Enter_Player();
	virtual void		Exit_Player();

protected:

	_int				m_iIN;

	vector<CRangeObj*>	m_vecRangeObj;

public:
	static CIsland* Create(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);


protected:
	virtual void		Free() override;

};