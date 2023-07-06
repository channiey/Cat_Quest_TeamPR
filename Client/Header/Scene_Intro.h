#pragma once

#include "Scene.h"

class CLoadingThread;

class CScene_Intro : public Engine::CScene
{
private:
	explicit CScene_Intro(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene_Intro();

public:
	virtual HRESULT		Ready_Scene() override;
	virtual _int		Update_Scene(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Scene() override;
	virtual void		Render_Scene() override;

private:
	HRESULT				Ready_Prototype();
	HRESULT				Ready_Layer_Environment();
	HRESULT				Ready_Layer_UI();

private:
	CLoadingThread*		m_pLoading;

public:
	static CScene_Intro*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free() override;

};

