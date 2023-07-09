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
	virtual HRESULT						Ready_Object(const _vec3& vPoint1, const _vec3& vPoint2);
	virtual _int						Update_Object(const _float& fTimeDelta) override;
	virtual void						LateUpdate_Object() override;
	virtual void						Render_Object() override;
public:
	const LINE_TYPE&					Get_LineType() const { return m_eLineType; }
	void								Set_LineType(const LINE_TYPE& _eLineType) { m_eLineType = _eLineType; }

private:
	HRESULT								Add_Component(const _vec3& vPoint1, const _vec3& vPoint2);


private:
	LINE_TYPE							m_eLineType;

protected:
	LPDIRECT3DDEVICE9					m_pGraphicDev;

public:
	static CLineObject*					Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPoint1, const _vec3& vPoint2);

public:
	virtual void						Free();
	friend class CCollisionMgr;

};

END