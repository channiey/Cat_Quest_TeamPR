#pragma once

#include "Engine_Define.h"
#include "GameObject.h"


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
	const _bool				Is_End() const { return m_bPlay; }; // 스킬 시전이 끝났는지

protected:
	LPDIRECT3DDEVICE9		m_pGraphicDev;

	CGameObject*			m_pOwnerObject;
	_bool					m_bPlay;

	CSkillEffect*			m_pSKillEffect; // 빔이나 불 같은 스킬
	CEffect_Range_Quater*	m_pRangeEffect; // 스킬 아래 깔리는 장판
	
protected:
	virtual void			Free();
};

