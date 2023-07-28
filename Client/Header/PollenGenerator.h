#pragma once
#include "GameObject.h"

BEGIN(Engine)


END

class CPollen;

class CPollenGenerator : public Engine::CGameObject
{
private:
	explicit CPollenGenerator(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPollenGenerator(const CPollenGenerator& rhs);
	virtual ~CPollenGenerator();

public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;

private:
	void	Caculate_CreateTime();
	void	Caculate_InitPos();

private:
	_vec3	 m_vecCreatePos;

	_float	  m_fAccTime;
	_float	  m_fCreateTime;


public:
	static CPollenGenerator* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free() override;

};

