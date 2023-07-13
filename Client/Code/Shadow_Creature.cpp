#include "stdafx.h"
#include "Shadow_Creature.h"

#include "Export_Function.h"

CShadow_Creature::CShadow_Creature(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CEffect(pGraphicDev, _pOwnerObject), m_pTextureCom(nullptr)
{
	m_pOwnerobject = _pOwnerObject;
}

CShadow_Creature::CShadow_Creature(const CShadow_Creature& rhs)
	: CEffect(rhs)
	, m_pTextureCom(rhs.m_pTextureCom)
{
}

CShadow_Creature::~CShadow_Creature()
{
}

HRESULT CShadow_Creature::Ready_Object()
{
	__super::Ready_Object();

	// CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).x,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).z });
	m_pTransformCom->Set_Scale(_vec3{ 1.f, 1.f, 1.f });

	m_bActive = true;

	return S_OK;
}

_int CShadow_Creature::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	m_pTransformCom->Set_Pos(
		dynamic_cast<CTransform*>(m_pOwnerobject->
			Get_Component(COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC))->Get_Info(INFO_POS));

	return iExit;
}

void CShadow_Creature::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CShadow_Creature::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(220, 255, 255, 255));
	// 장판 텍스처 출력
	// 빌보드 해제
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	_matrix matWorld = m_pOwnerobject->Get_Transform()->Get_WorldMat();
	_matrix matBill;
	_vec3 vPos;

	memcpy(&vPos, &matWorld.m[3], sizeof(_vec3));
	vPos += m_vOffSet;
	vPos.y = 0.02f;
	vPos.z -= 7;

	matWorld *= *D3DXMatrixInverse(&matBill, NULL, &CCameraMgr::GetInstance()->Get_Billboard_X());
	memcpy(&matWorld.m[3], &vPos, sizeof(_vec3));

	matWorld._33 = 2;

	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
	// CEffect::Render_Object();
}

HRESULT CShadow_Creature::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Shadow_Creature", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

void CShadow_Creature::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CShadow_Creature* CShadow_Creature::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CShadow_Creature* pInstance = new CShadow_Creature(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Shadow_Creature Effect Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CShadow_Creature::Free()
{
	__super::Free();
}
