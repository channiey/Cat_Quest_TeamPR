#include "Hedgehog.h"
#include "Export_Function.h"
#include "EventMgr.h"

CHedgehog::CHedgehog(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonster(pGraphicDev)
{
}

CHedgehog::CHedgehog(const CMonster& rhs)
	: CMonster(rhs)
{
}

CHedgehog::~CHedgehog()
{
}

HRESULT CHedgehog::Ready_Object()
{
	__super::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 2.f, 2.f, 2.f });
	//m_pTransformCom->Set_Pos(_vec3{ 300.f, m_pTransformCom->Get_Scale().y, 300.f });

	m_pTransformCom->Set_Pos(_vec3{ _float(VTXCNTX - 30.f + rand() % 40),
									m_pTransformCom->Get_Scale().y,
									_float(rand() % 70) });

	return S_OK;
}

_int CHedgehog::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CMonster::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);


	return iExit;
}

void CHedgehog::LateUpdate_Object()
{
	__super::LateUpdate_Object();

}

void CHedgehog::Render_Object()
{
	__super::Render_Object();

}

void CHedgehog::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CHedgehog::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CHedgehog::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CHedgehog::Add_Component()
{
	CComponent*		pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Hedgehog", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	return S_OK;
}

void CHedgehog::Move(const _float& fTimeDelta)
{


}

CHedgehog* CHedgehog::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHedgehog* pInstance = new CHedgehog(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Hedgehog Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHedgehog::Free()
{
	__super::Free();
}
