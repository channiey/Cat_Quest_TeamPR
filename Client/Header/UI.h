#pragma once
#include "GameObject.h"
#include "Engine_Define.h"

BEGIN(Engine)

class CTexture;
class CRcTex;
class CTransform;

END

class CUI : public Engine::CGameObject
{

protected:

	explicit CUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CUI(const CUI& rhs);
	virtual ~CUI();

	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;



private:
	HRESULT					Add_Component();


protected:
	CTexture*				m_pTextureCom = nullptr;
	UITYPE					m_eUItype;


public:
	static CUI*				Create(LPDIRECT3DDEVICE9 pGraphicDev);
	

protected:
	virtual void			Free() override;

	

};
