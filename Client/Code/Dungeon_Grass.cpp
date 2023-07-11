#include "stdafx.h"
#include "Dungeon_Grass.h"

#include "Export_Function.h"

CDungeon_Grass::CDungeon_Grass(LPDIRECT3DDEVICE9 pGraphicDev)
	: CDungeon(pGraphicDev)
{
}

CDungeon_Grass::CDungeon_Grass(const CDungeon& rhs)
	: CDungeon(rhs)
{
}

CDungeon_Grass::~CDungeon_Grass()
{
}

HRESULT CDungeon_Grass::Ready_Object()
{
	CDungeon::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 3.f, 3.f, 3.f });
	m_pTransformCom->Set_Pos(_vec3{ (VTXCNTX / 2.f) - 40.f, m_pTransformCom->Get_Scale().y, -10.f });	return S_OK;
}

_int CDungeon_Grass::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CDungeon_Grass::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CDungeon_Grass::Render_Object()
{
	__super::Render_Object();
}

void CDungeon_Grass::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CDungeon_Grass::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CDungeon_Grass::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CDungeon_Grass::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Dungeon_Grass", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CDungeon_Grass* CDungeon_Grass::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDungeon_Grass* pInstance = new CDungeon_Grass(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Dungeon_Grass Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CDungeon_Grass::Free()
{
	__super::Free();
}