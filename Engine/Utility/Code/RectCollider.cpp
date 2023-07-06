#include "..\..\Header\RectCollider.h"

#include "Transform.h"

CRectCollider::CRectCollider()
{
}

CRectCollider::CRectCollider(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCollider(pGraphicDev, COMPONENT_TYPE::COL_RECT)
{
	ZeroMemory(&m_vSize, sizeof(_vec3));
	ZeroMemory(&m_vOverlap, sizeof(_vec3));

}

CRectCollider::CRectCollider(const CRectCollider& rhs, CGameObject* _pOwnerObject)
	: CCollider(rhs, _pOwnerObject)
	, m_vSize(rhs.m_vSize)
	, m_vOverlap(rhs.m_vOverlap)
{
	Ready_Collider();
}

CRectCollider::~CRectCollider()
{
}

HRESULT CRectCollider::Ready_Collider()
{
	return S_OK;
}

CRectCollider* CRectCollider::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRectCollider* pInstance = new CRectCollider(pGraphicDev);

	if (FAILED(pInstance->Ready_Collider()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Rect Collider Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent* CRectCollider::Clone(CGameObject* _pOwnerObject)
{
	return new CRectCollider(*this, _pOwnerObject);
}

void CRectCollider::Free()
{
	CCollider::Free();
}

void CRectCollider::Render_Collider()
{
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	if (0 < m_iCol)
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.red));
	else
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.green));


	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}
