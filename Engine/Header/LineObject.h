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

public:
	const LINE_TYPE&					Get_LineType() const { return m_eLineType; }
	void								Set_LineType(const LINE_TYPE& _eLineType) { m_eLineType = _eLineType; }

private:
	HRESULT								Add_Component(void);


private:
	LINE_TYPE							m_eLineType;

protected:
	LPDIRECT3DDEVICE9					m_pGraphicDev;

public:
	static CLineObject*					Create(LPDIRECT3DDEVICE9 pGraphicDev);

public:
	virtual void						Free();

};

END