#pragma once

#include "Collider.h"

BEGIN(Engine)

class ENGINE_DLL CRectCollider : public CCollider
{
private:
	explicit CRectCollider();
	explicit CRectCollider(LPDIRECT3DDEVICE9 CRectCollider);
	explicit CRectCollider(const CRectCollider& rhs, CGameObject* _pOwnerObject);
	virtual ~CRectCollider();

public:
	HRESULT						Ready_Collider();
	virtual void				Render_Collider() override;

	void						Set_OverLap(const _vec3& _vOverlap) { memcpy(&m_vOverlap, &_vOverlap, sizeof(_vec3)); }

private:
	_vec3						m_vSize;
	_vec3						m_vOverlap; // 렉트끼리 겹친 부분에 대한 넓이를 가진다.

public:
	static CRectCollider*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*			Clone(CGameObject* _pOwnerObject);

private:
	virtual void				Free();

	friend class CCollisionMgr;

};

END