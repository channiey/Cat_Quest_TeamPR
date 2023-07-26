#pragma once
#include "BossProjectile.h"

BEGIN(Engine)

class CTexture;
class CCollider;

END
class CComBack_Bullet :  public CBossProjectile
{
protected:
	explicit CComBack_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner );
	explicit CComBack_Bullet(const CProjectile& rhs);
	virtual ~CComBack_Bullet();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


	void					Comeback(const _float& fTimeDelta);

private:
	HRESULT					Add_Component();

public:

	static					CComBack_Bullet* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner);


private:
	_vec3			m_vOriginPos;
	_bool			m_bComeBack;
	_bool			m_bStop;

protected:
	virtual void		Free() override;




};

