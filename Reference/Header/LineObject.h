#pragma once

#include "GameObject.h"

#include "LineCollider.h"

BEGIN(Engine)

class ENGINE_DLL CLineObject : public CGameObject
{
protected:
	explicit CLineObject(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CLineObject(const CLineObject& rhs);
	virtual ~CLineObject();

public:
	virtual HRESULT						Ready_Object(void);

private:
	HRESULT								Add_Component(void);

protected:
	LPDIRECT3DDEVICE9					m_pGraphicDev;
	CLineCollider*						m_pLineColliderCom;


public:
	static CLineObject*					Create(LPDIRECT3DDEVICE9 pGraphicDev);

public:
	virtual void						Free();

	//friend class CCollisionMgr;
};

END