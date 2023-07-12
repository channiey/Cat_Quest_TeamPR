#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

class CCloud1 : public CEffect
{
	// ������ �����Ǵ� ��ġ�� ���ؼ��� ������ �ʿ��� ��
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

private:
	CTexture*  m_pTextureCom;

public:
	static CCloud1* Create(LPDIRECT3DDEVICE9 pGraphicDev); // ������ �����Ǵ� ��ġ�� ���ؼ��� ������ �ʿ��� ��

private:
	virtual void				Free() override;
};

