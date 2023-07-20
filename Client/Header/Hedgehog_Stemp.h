#pragma once
#include "Effect.h"

BEGIN(Engine)
class CTexture;
END

class CHedgehog_Stemp : public CEffect
{
	explicit CHedgehog_Stemp(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos);
	explicit CHedgehog_Stemp(const CHedgehog_Stemp& rhs);
	virtual ~CHedgehog_Stemp();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
private:
	CTexture*   m_pTextureCom;
	CTransform* m_pTransformCom;

	_int		m_iTranslucent;
	_int		m_iAlpha;
	_vec3		m_vPos;

	_float		m_fSize;
	_float		m_fSpeed;

	_matrix		matWorld;

public:
	static CHedgehog_Stemp* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos);

private:
	virtual void				Free() override;
};

