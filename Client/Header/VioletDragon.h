#pragma once
#include "GameObject.h"
#include "Monster.h"

class CRangeObj;
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


public:
	
	_bool			Get_HP80() { return m_bHP_80; }
	_bool			Get_HP50() { return m_bHP_50; }
	_bool			Get_HP20() { return m_bHP_20; }

	void			Set_HP80(_bool _bHP80) { m_bHP_80 = _bHP80; }
	void			Set_HP50(_bool _bHP50) { m_bHP_50 = _bHP50; }
	void			Set_HP30(_bool _bHP20) { m_bHP_20 = _bHP20; }


private:

	CSkill*					m_pFullDown;
	_bool					m_bFullDown;
	_float					m_FullDownTime;

	CSkill*					m_pBloodyThunder;
	_bool					m_bBloodyTunder;
	_bool					m_bBloodyLate;
	_float					m_BloodyTime;


	CSkill*					m_pBlueThunder;
	_bool					m_bBlueTunder;
	_bool					m_bBlueLate;
	_float					m_BlueTime;



	CSkill*					m_pCreateWyvern;
	_bool					m_bCreatWyvernPlay;
	_bool					m_bCreatWyvernLate;
	_float					m_CreateTime;

	_bool					m_bHP_80;
	_bool					m_bHP_50;
	_bool					m_bHP_20;


protected:
	virtual void		Free() override;




};

