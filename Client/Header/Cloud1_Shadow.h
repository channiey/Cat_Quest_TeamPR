#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

class CCloud1_Shadow : public CEffect
{
	explicit CCloud1_Shadow(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CCloud1_Shadow(const CCloud1_Shadow& rhs);
	virtual ~CCloud1_Shadow();

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
	static CCloud1_Shadow* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

private:
	virtual void				Free() override;
};

