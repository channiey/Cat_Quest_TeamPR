#pragma once

#include "GameObject.h"
#include "Monster.h"

BEGIN(Engine)

//class CCubeCol;
class CCollider;

END

class CCuteMonster : public CMonster
{
protected:
	explicit CCuteMonster(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCuteMonster(const CMonster& rhs);
	virtual ~CCuteMonster();

public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;

public:
	virtual void		OnCollision_Enter(CGameObject* _pColObj);
	virtual void		OnCollision_Stay(CGameObject* _pColObj);
	virtual void		OnCollision_Exit(CGameObject* _pColObj);

private:
	HRESULT				Add_Component();
private:
	void				Move(const _float& fTimeDelta);

protected:
	MOVEINFO			m_tMoveInfo;
	STATINFO			m_tStatInfo;

public:
	static				CCuteMonster* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

