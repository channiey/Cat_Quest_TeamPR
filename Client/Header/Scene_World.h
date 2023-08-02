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

public:
	void				Finish_Game(); 
private:
	HRESULT				Ready_Layer_Camera();
	HRESULT				Ready_Layer_UI(); 
	HRESULT				Ready_Layer_Player(); 
	HRESULT				Ready_Layer_Effect(); 
	HRESULT				Ready_Layer_Other();

	HRESULT				Ready_Load(); 

	HRESULT				Ready_Layer_KSH();
	HRESULT				Ready_Layer_KJM();
	HRESULT				Ready_Layer_LHJ();
	HRESULT				Ready_Layer_YC(); 

	void SetupVertexFog(DWORD Color, DWORD Mode, BOOL UseRange, FLOAT Density);

public:
	static CScene_World*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	_bool				m_bEndingFade;
	_bool				m_bFinish;
	_float				m_fAcc;

private:
	virtual void		Free() override;
};

