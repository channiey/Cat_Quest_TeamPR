#include "..\..\Header\LineObject.h"

#include "ProtoMgr.h"

CLineObject::CLineObject(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::CAMERA)
	, m_eLineType(LINE_TYPE::TYPEEND)
{

}

CLineObject::CLineObject(const CLineObject& rhs)
	: Engine::CGameObject(rhs)
	, m_eLineType(rhs.m_eLineType)
{
}

CLineObject::~CLineObject()
{
}

HRESULT CLineObject::Ready_Object(void)
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

HRESULT CLineObject::Add_Component(void)
{
	CComponent* pComponent = nullptr;
	pComponent = m_pColliderCom = dynamic_cast<CLineCollider*>(CProtoMgr::GetInstance()->Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_LINE, pComponent);

	return S_OK;
}

CLineObject* CLineObject::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLineObject* pInstance = new CLineObject(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Line Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CLineObject::Free()
{
	CGameObject::Free();
}
