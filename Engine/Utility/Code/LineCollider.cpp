#include "..\..\Header\LineCollider.h"

#include "Transform.h"

CLineCollider::CLineCollider()
{

}

CLineCollider::CLineCollider(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCollider(pGraphicDev, COMPONENT_TYPE::COL_LINE)
{
	ZeroMemory(&m_vecPoint1, sizeof(_vec3));
	ZeroMemory(&m_vecPoint2, sizeof(_vec3));
}

CLineCollider::CLineCollider(const CLineCollider& rhs, CGameObject* _pOwnerObject)
	: CCollider(rhs, _pOwnerObject)
	, m_vecPoint1(rhs.m_vecPoint1)
	, m_vecPoint2(rhs.m_vecPoint2)
{
	Ready_Collider();
}

CLineCollider::~CLineCollider()
{
}

HRESULT CLineCollider::Ready_Collider()
{
	return S_OK;
}

CLineCollider* CLineCollider::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLineCollider* pInstance = new CLineCollider(pGraphicDev);

	if (FAILED(pInstance->Ready_Collider()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Line Collider Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent* CLineCollider::Clone(CGameObject* _pOwnerObject)
{
	return new CLineCollider(*this, _pOwnerObject);
}

void CLineCollider::Free()
{
	CCollider::Free();
}

void CLineCollider::Render_Collider()
{
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	if (0 < m_iCol)
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.red));
	else
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.green));

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}
