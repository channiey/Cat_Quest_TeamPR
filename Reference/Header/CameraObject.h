#pragma once

#include "GameObject.h"
#include "Camera.h"

BEGIN(Engine)

class ENGINE_DLL CCameraObject : public CGameObject
{
protected:
	explicit CCameraObject(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCameraObject(const CCameraObject& rhs);
	virtual ~CCameraObject();

public:
	virtual HRESULT						Ready_Object(void);

public:
	CCamera*							Get_CameraCom() const { return m_pCameraCom; }

protected:
	LPDIRECT3DDEVICE9					m_pGraphicDev;
	CCamera*							m_pCameraCom;
	
public:
	virtual void						Free();
};

END