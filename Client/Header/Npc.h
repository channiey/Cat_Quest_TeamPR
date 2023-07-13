#pragma once

#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CAnimation;
class CRcTex;
END

class CNpc : public Engine::CGameObject
{
protected:
	explicit CNpc(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CNpc(const CNpc& rhs);
	virtual ~CNpc();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	// 모두 같은 기능이라 부모에서 통일
	void					Play_ColLogic(const _float& fTimeDelta); // 충돌 로직

	CTexture*				Get_Texture() { return m_pTextureCom; }

private:
	HRESULT					Add_Component();

protected:
	CTexture*	m_pTextureCom = nullptr; 
	CAnimation* m_pAnimation;

protected:
	virtual void			Free() override;

};

