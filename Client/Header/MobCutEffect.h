#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;
class CAnimation;

END

class CMobCutEffect : public CEffect
{
	explicit CMobCutEffect(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos);
	explicit CMobCutEffect(const CMobCutEffect& rhs);
	virtual ~CMobCutEffect();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;

private:
	// Texture
	CTexture* m_pTexCutCom;
	CTexture* m_pTexOrbCom;

	// Cut
	_vec3	  m_vPos;
	_float	  m_fCutSize;
	_float	  m_fCutMaxSize;
	_bool	  m_bSizeUp;
	_float	  m_fRandRotZ;
	// Orb
	_float	  m_fOrbSize;

public:
	static CMobCutEffect* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos);

private:
	virtual void				Free() override;
};

