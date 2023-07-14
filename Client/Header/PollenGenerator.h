#pragma once
#include "GameObject.h"

BEGIN(Engine)


END

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

public:
	static CPollenGenerator* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	_matrix m_matView, m_matWorld;
	_vec3	m_vecCreatePos;
	_int    m_fCreatTime;
private:
	virtual void		Free() override;

};

