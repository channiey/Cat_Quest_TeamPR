#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

class CCloud2 : public CEffect
{
	// ������ �����Ǵ� ��ġ�� ���ؼ��� ������ �ʿ��� ��
	explicit CCloud2(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCloud2(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CCloud2(const CCloud2& rhs);
	virtual ~CCloud2();

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
	static CCloud2* Create(LPDIRECT3DDEVICE9 pGraphicDev); // ������ �����Ǵ� ��ġ�� ���ؼ��� ������ �ʿ��� ��

private:
	virtual void				Free() override;
};

