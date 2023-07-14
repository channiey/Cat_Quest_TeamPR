#include "stdafx.h"
#include "Effect_Range_BigCircle.h"

#include "Export_Function.h"

CEffect_Range_BigCircle::CEffect_Range_BigCircle(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	:CSkillEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_SKILL_RANGE_BIGCIRCLE)
{
}

CEffect_Range_BigCircle::CEffect_Range_BigCircle(const CEffect& rhs)
	: CSkillEffect(rhs)
{
}

CEffect_Range_BigCircle::~CEffect_Range_BigCircle()
{
}

HRESULT CEffect_Range_BigCircle::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 10.f, 0.1f, 7.f }); // 이거 0.1f y도 되네?
	m_pTransformCom->Set_Pos(_vec3{ 110, m_pTransformCom->Get_Scale().y, -10.f });

	m_vSize = m_pTransformCom->Get_Scale();

	//m_bActive = false;

	return S_OK;
}

_int CEffect_Range_BigCircle::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CGameObject::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CEffect_Range_BigCircle::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEffect_Range_BigCircle::Render_Object()
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	_matrix matWorld = Get_Transform()->Get_WorldMat();
	_matrix matBill;
	_vec3 vPos;

	memcpy(&vPos, &matWorld.m[3], sizeof(_vec3));
	vPos += m_vOffSet;
	vPos.y = 0.02f;

	matWorld *= *D3DXMatrixInverse(&matBill, NULL, &CCameraMgr::GetInstance()->Get_Billboard_X());
	memcpy(&matWorld.m[3], &vPos, sizeof(_vec3));

	matWorld._11 = m_vSize.x;
	matWorld._22 = m_vSize.y;
	matWorld._33 = m_vSize.z;

	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);
}

HRESULT CEffect_Range_BigCircle::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Skill_BigCircle_Orange", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CTerrainRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, pComponent);

	return S_OK;
}

CEffect_Range_BigCircle* CEffect_Range_BigCircle::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CEffect_Range_BigCircle* pInstance = new CEffect_Range_BigCircle(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Range BigCircle Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffect_Range_BigCircle::Free()
{
	__super::Free();
}
