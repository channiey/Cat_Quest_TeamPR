#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

class CCloud1 : public CEffect
{
	// 구름이 생성되는 위치를 위해서라도 주인이 필요할 듯
	explicit CCloud1(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCloud1(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CCloud1(const CCloud1& rhs);
	virtual ~CCloud1();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;

	const _float				Get_Distance_From_Camera();
	void						Set_RandomSize();
	const _float				Set_RandomHeight();

private:
	CTexture*  m_pTextureCom;

public:
	static CCloud1* Create(LPDIRECT3DDEVICE9 pGraphicDev); // 구름이 생성되는 위치를 위해서라도 주인이 필요할 듯

private:
	virtual void				Free() override;
};

