#pragma once

#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CAIComponent;
class CRcTex;
END

class CNpc : public Engine::CGameObject
{
protected:
	explicit CNpc(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CNpc(const CNpc& rhs);
	virtual ~CNpc();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	virtual void			OnCollision_Enter(CGameObject* _pColObj);
	virtual void			OnCollision_Stay(CGameObject* _pColObj);
	virtual void			OnCollision_Exit(CGameObject* _pColObj);

private:
	HRESULT					Add_Component();

protected:

	CTexture* m_pTextureCom[_uint(STATE_TYPE::TYPEEND)];


protected:
	virtual void			Free() override;

};

