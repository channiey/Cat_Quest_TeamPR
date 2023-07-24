#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

struct tagSparkle
{
	CTransform*				m_pSparkleTransCom;
	CTexture*				m_pSparkleTextureCom;
	LERP_FLOAT_INFO			m_tSizeLerp;
};

class CItemGetEffect : public CEffect
{
	explicit CItemGetEffect(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _pPos);
	explicit CItemGetEffect(const CItemGetEffect& rhs);
	virtual ~CItemGetEffect();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;

private:
	tagSparkle	 m_sSparkle[3];
	_vec3		 m_vPos;
	_vec3		 m_vScale;
	_float		 m_fMaxSize;
public:
	static CItemGetEffect* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _pPos);

private:
	virtual void				Free() override;
};

