#pragma once
#include "GameObject.h"

BEGIN(Engine)


END

class CPollen;

class CEffectGenerator : public Engine::CGameObject
{
private:
	explicit CEffectGenerator(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CEffectGenerator(const CEffectGenerator& rhs);
	virtual ~CEffectGenerator();

public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;

public:
	void	Set_Locate(OBJ_ID _eLocation) { m_ePlayerLocate = _eLocation; }


private:
	void	Pollen_Create(const _float& fTimeDelta);
	void	Pollen_Caculate_CreateTime();
	void	Pollen_Caculate_InitPos();

	void	Cloud_Create(const _float& fTimeDelta);
	void	Cloud_Caculate_CreateTime();
	void	Cloud_Caculate_InitPos();


private:
	OBJ_ID		m_ePlayerLocate;

	// 먼지
	_vec3		m_vPollen_CreatePos;
	_float		m_fPollen_AccTime;
	_float		m_fPollen_CreateTime;

	// 구름
	_vec3		m_vCloud_CreatePos;
	_float		m_fCloud_AccTime;
	_float		m_fCloud_CreateTime;


public:
	static CEffectGenerator* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free() override;

};

