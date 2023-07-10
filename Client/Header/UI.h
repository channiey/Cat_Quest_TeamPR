#pragma once
#include "GameObject.h"
#include "Engine_Define.h"


BEGIN(Engine)

class CTexture;
class CRcTex;


END

class CUI : public Engine::CGameObject
{

protected:

	explicit CUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CUI(const CUI& rhs);
	virtual ~CUI();


public: 
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

protected:
	virtual HRESULT			Add_Component() PURE;

protected:
	
	CTexture*				m_pTextureCom;
	UI_TYPE					m_eUIType;

	_matrix					m_UImatWorld;

	_float					m_fPosX;
	_float					m_fPosY;

	_float					m_fSizeX;
	_float					m_fSizeY;
	
protected:
	virtual void			Free() override;

	

};
