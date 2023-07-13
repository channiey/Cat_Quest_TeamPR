#include "stdafx.h"
#include "Cloud3_Shadow.h"

#include "Export_Function.h"

CCloud3_Shadow::CCloud3_Shadow(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_CLOUD_3), m_pTextureCom(nullptr)
{
	m_pOwnerobject = _pOwnerObject;
}

CCloud3_Shadow::CCloud3_Shadow(const CCloud3_Shadow& rhs)
	: CEffect(rhs)
	, m_pTextureCom(rhs.m_pTextureCom)
{
}

CCloud3_Shadow::~CCloud3_Shadow()
{
}

HRESULT CCloud3_Shadow::Ready_Object()
{
	__super::Ready_Object();

	// CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).x,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y - 12.f,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).z });
	m_pTransformCom->Set_Scale(_vec3{ 5.f, 3.f, 5.f });

	m_bActive = true;

	return S_OK;
}

_int CCloud3_Shadow::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	m_pTransformCom->Set_Pos(
		dynamic_cast<CTransform*>(m_pOwnerobject->
			Get_Component(COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC))->Get_Info(INFO_POS));

	return iExit;
}

void CCloud3_Shadow::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CCloud3_Shadow::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(220, 255, 255, 255));
	// ���� �ؽ�ó ���
	// ������ ����
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

	//matWorld._11 = m_vSize.x;
	//matWorld._22 = m_vSize.y;
	matWorld._33 = 2;

	m_pTextureCom->Render_Texture(); // �ؽ�ó ���� -> ���� ���� ���� ��!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
	// CEffect::Render_Object();
}

HRESULT CCloud3_Shadow::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Colud3_Shadow", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

void CCloud3_Shadow::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CCloud3_Shadow* CCloud3_Shadow::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CCloud3_Shadow* pInstance = new CCloud3_Shadow(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("CCloud3_Shadow Effect Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CCloud3_Shadow::Free()
{
	__super::Free();
}