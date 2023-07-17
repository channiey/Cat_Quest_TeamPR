#pragma once
#include "Effect.h"

BEGIN(Engine)
class CTexture;
END

class CMonstSpirit : public CEffect
{
	explicit CMonstSpirit(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos);
	explicit CMonstSpirit(const CMonstSpirit& rhs);
	virtual ~CMonstSpirit();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;

	virtual void				Alpha_Update();
private:
	// 텍스쳐
	CTexture* m_pTexSpritCom;
	CTexture* m_pTexWaveCom;
	CTexture* m_pTexBlueOrbCom;
	CTexture* m_pTexYellowOrbCom;

	// 스피릿
	_int		m_iSpiritMaxAlpha;
	_int		m_iSpiritTranslucent;
	_float		m_fSpritSizeY;
	_vec3		m_vSpritPos;
	CTransform* m_pSpritTransCom;
	// 웨이브
	_int		m_iOtherMaxAlpha;
	_int		m_iOtherTranslucent;
	_float		m_fWaveSize;
	_vec3		m_vWavePos;
	CTransform* m_pWaveTransCom;
	// 파란구
	_float		m_fBlueOrbSize;
	_vec3		m_vBlueOrbPos;
	CTransform* m_pBlueOrbTransCom;


	_bool	  m_bExtinction;


	_matrix	  matWorld;

public:
	static CMonstSpirit* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos);

private:
	virtual void				Free() override;
};

