#pragma once

#include "Scene.h"

class CScene_World : public Engine::CScene
{
private:
	explicit CScene_World(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene_World();

public:
	virtual HRESULT		Ready_Scene() override;
	virtual _int		Update_Scene(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Scene() override;
	virtual void		Render_Scene() override;

private:
	HRESULT				Ready_Layer_Environment	();
	HRESULT				Ready_Layer_Camera();
	HRESULT				Ready_Layer_UI();
	HRESULT				Ready_Layer_Player();
	HRESULT				Ready_Layer_Monster();
	HRESULT				Ready_Layer_Item();
	HRESULT				Ready_Layer_Projectile();
	HRESULT				Ready_Layer_Effect();

public:
	static CScene_World*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free() override;
};

