#include "stdafx.h"
#include "../Header/Dungeon.h"

#include "Export_Function.h"
#include "EventMgr.h"

CDungeon::CDungeon(LPDIRECT3DDEVICE9 pGraphicDev)
	:	CArgObject(pGraphicDev)
{
}

CDungeon::CDungeon(const CArgObject& rhs)
	:	CArgObject(rhs)
{
}

CDungeon::~CDungeon()
{
}

HRESULT CDungeon::Ready_Object()
{
	CArgObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 4.f, 4.f, 4.f });
	m_pTransformCom->Set_Pos(_vec3{ 40.f, m_pTransformCom->Get_Scale().y, 50.f });

	return S_OK;
}

_int CDungeon::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CArgObject::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CDungeon::LateUpdate_Object()
{
	CArgObject::LateUpdate_Object();
}

void CDungeon::Render_Object()
{
	CArgObject::Render_Object();
}

void CDungeon::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CDungeon::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CDungeon::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CDungeon::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Dungeon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CDungeon* CDungeon::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDungeon* pInstnace = new CDungeon(pGraphicDev);

	if (FAILED(pInstnace->Ready_Object()))
	{
		Safe_Release(pInstnace);
		MSG_BOX("Mountain Create Failed");
		return nullptr;
	}
	return pInstnace;
}

void CDungeon::Free()
{
	CArgObject::Free();
}
