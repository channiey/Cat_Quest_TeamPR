#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

class CShadow_Creature : public CEffect
{
	explicit CShadow_Creature(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CShadow_Creature(const CShadow_Creature& rhs);
	virtual ~CShadow_Creature();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;

private:
	CTexture* m_pTextureCom;

public:
	static CShadow_Creature* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

private:
	virtual void				Free() override;
};

