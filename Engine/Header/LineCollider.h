#pragma once

#include "Collider.h"

BEGIN(Engine)

class ENGINE_DLL CLineCollider : public CCollider
{
private:
	explicit CLineCollider();
	explicit CLineCollider(LPDIRECT3DDEVICE9 CLineCollider);
	explicit CLineCollider(const CLineCollider& rhs, CGameObject* _pOwnerObject);
	virtual ~CLineCollider();

public:
	HRESULT						Ready_Collider();
	virtual void				Render_Collider() override;

private:
	_vec3						m_vecPoint1;
	_vec3						m_vecPoint2;
		
public:
	static CLineCollider*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*			Clone(CGameObject* _pOwnerObject);


private:
	virtual void				Free();

	friend class CCollisionMgr;

};

END