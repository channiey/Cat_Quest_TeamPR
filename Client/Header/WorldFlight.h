#pragma once
#include "Item_Object.h"

BEGIN(Engine)

class CCollider;

END

#define SPARKLE_AMOUNT 3

struct tagFlightSparkle
{
	CTransform*				m_pSparkleTransCom;
	CTexture*				m_pSparkleTextureCom;
	LERP_FLOAT_INFO			m_tSizeUpLerp;
	LERP_FLOAT_INFO			m_tSizeDownLerp;
};

class CWorldFlight : public CItem_Object
{
protected:
	explicit CWorldFlight(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CWorldFlight(const CItem& rhs);
	virtual ~CWorldFlight();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	virtual void		OnCollision_Enter(CGameObject* _pColObj);
	virtual void		OnCollision_Exit(CGameObject* _pColObj);

private:
	HRESULT					Add_Component();

	tagFlightSparkle	 m_tSparkle[3];
	_int				 m_iLevel;

public:
	static				CWorldFlight* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;


};

