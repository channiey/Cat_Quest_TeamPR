#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CTexture;
class CAIComponent;

END

class CProjectile : public Engine:: CGameObject
{
protected:
	explicit CProjectile(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CProjectile(const CProjectile& rhs);
	virtual ~CProjectile();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;



private:
	HRESULT					Add_Component();


protected:

	CTexture*			m_pTextureCom;
	CAIComponent*		m_pAICom;


protected:
	virtual void		Free() override;


};

