#pragma once

#include "Engine_Define.h"
#include "GameObject.h"

/*

	* �ش� Ŭ������ ��� �޾� �� ��ų�� �����ϵ��� �Ѵ�.
	
	* CSkillEffect
	* CEffect_Range_Quater
	* CCollier
	* CTransform
	



	����



	1. �÷��̾� �Ǵ� ���ʹ� �ڽ��� ����� ��ų�� ��������� ���´�(�� Ŭ���� Ÿ��) -> ���� ��ų ���� �����̳� ���

	2. ��ų�� �� Ŭ������ ��ӹ޾� ���� ��ų Ŭ������ �����Ѵ�.

		- �ϳ��� ��ų�� CSkillEffect / CEffect_Range_Quater / CCollier / CTransform�� ������ ���´�(CEffect_Range_Quater�� ����)

		- ��ų ����, CSkillEffect�� CEffect_Range_Quater�� ��� �Լ��� ȣ���ϵ��� �Ѵ�.

*/

class CSkillEffect;
class CEffect_Range_Quater;

class CSkill :
    public CGameObject
{
protected:
	explicit CSkill(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CSkill(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, const OBJ_ID& _eID);
	explicit CSkill(const CSkill& rhs);
	virtual ~CSkill();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	HRESULT					Add_Component();

public:
	virtual HRESULT			Play();
	virtual HRESULT			End();
	const _bool				Is_End() const { return m_bPlay; }; // ��ų ������ ��������

protected:
	LPDIRECT3DDEVICE9		m_pGraphicDev;

	CGameObject*			m_pOwnerObject;
	_bool					m_bPlay;

	CSkillEffect*			m_pSKillEffect; // ���̳� �� ���� ��ų
	CEffect_Range_Quater*	m_pRangeEffect; // ��ų �Ʒ� �򸮴� ����
	
protected:
	virtual void			Free();
};

