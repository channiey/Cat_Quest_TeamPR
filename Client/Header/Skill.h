#pragma once

#include "Base.h"
#include "Engine_Define.h"
#include "GameObject.h"

class CSkillEffect;

class CSkill :
    public CBase
{
protected:
	explicit CSkill(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	virtual ~CSkill();

public:
	virtual HRESULT			Ready_Skill();
	virtual void			Update_Skill();
	virtual void			LateUpdate_Skill();

public:
	virtual HRESULT			Cast() { return S_OK; }; // ��ų ���� (����ȭ)
	const _bool				Is_End() const { return m_bPlay; }; // ��ų ������ ��������

private:
	HRESULT					Add_SkillEffect();

protected:
	LPDIRECT3DDEVICE9		m_pGraphicDev;

	CGameObject*			m_pOwnerObject;
	map<PRIORITY_SKILL_LAYER, vector<CSkillEffect*>> m_mapEffect; // ��ų ����Ʈ �����̳�
	_bool					m_bPlay;
	
protected:
	virtual void			Free();
};

