#include "..\..\Header\Collider.h"

#include "GameObject.h"

_uint CCollider::g_iNextID = 0;

CCollider::CCollider()	
{
}

CCollider::CCollider(LPDIRECT3DDEVICE9 pGraphicDev, const COMPONENT_TYPE& _eType)
	: CComponent(pGraphicDev, _eType)
	, m_iCol(0.f)
	, m_eColType(COL_TYPE::TYPEEND)
{
	ZeroMemory(&m_vOffset, sizeof(_vec3));
}

CCollider::CCollider(const CCollider & rhs, CGameObject* _pOwnerObject)
	: CComponent(rhs, _pOwnerObject)
	, m_iID(g_iNextID++)
	, m_iCol(0.f)
	, m_eColType(rhs.m_eColType)
	, m_vOffset(rhs.m_vOffset)
{

	Ready_Collider();
}

CCollider::~CCollider()
{
}

HRESULT CCollider::Ready_Collider()
{
	return S_OK;
}

void CCollider::OnCollision_Enter(CGameObject * _pColObj)
{
	++m_iCol;
	m_pOwnerObject->OnCollision_Enter(_pColObj);
	
}

void CCollider::OnCollision_Stay(CGameObject * _pColObj)
{
	m_pOwnerObject->OnCollision_Stay(_pColObj);
}

void CCollider::OnCollision_Exit(CGameObject * _pColObj)
{
	--m_iCol;
	m_pOwnerObject->OnCollision_Exit(_pColObj);
}

CCollider * CCollider::Create(LPDIRECT3DDEVICE9 pGraphicDev, const COMPONENT_TYPE& _eType)
{
	CCollider*		pInstance = new CCollider(pGraphicDev, _eType);

	if (FAILED(pInstance->Ready_Collider()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Collider Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent * CCollider::Clone(CGameObject* _pOwnerObject)
{
	return new CCollider(*this, _pOwnerObject);
}

void CCollider::Free()
{
	//Safe_Release(m_pMesh);

	CComponent::Free();
}
