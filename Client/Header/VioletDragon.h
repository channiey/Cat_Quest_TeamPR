#pragma once
#include "GameObject.h"
#include "Monster.h"

BEGIN(Engine)

class CCubeCol;
class CCollider;

END

class CVioletDragon : public CMonster
{
protected:

	explicit CVioletDragon(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CVioletDragon(const CMonster& rhs);
	virtual ~CVioletDragon();


public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;


public:
	virtual void		OnCollision_Enter(CGameObject* _pColObj) override;
	virtual void		OnCollision_Stay(CGameObject* _pColObj) override;
	virtual void		OnCollision_Exit(CGameObject* _pColObj) override;

private:
	HRESULT				Add_Component();


public:
	static				CVioletDragon* Create(LPDIRECT3DDEVICE9 pGraphicDev);



private:

	CSkill*					m_pFullDown;
	_bool					m_bFullDown;
	_float					m_FullDownTime;

	CSkill*					m_pBloodyThunder;
	_bool					m_bBloodyTunder;
	_float					m_BloodyTime;

	CSkill*					m_pCreateWyvern;
	_bool					m_bCreatWyvernPlay;
	_bool					m_bCreatWyvernLate;
	_float					m_CreateTime;

protected:
	virtual void		Free() override;




};

