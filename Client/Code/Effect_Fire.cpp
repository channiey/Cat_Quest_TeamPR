#include "stdafx.h"
#include "Effect_Fire.h"

#include "Export_Function.h"

CEffect_Fire::CEffect_Fire(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	:CSkillEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_SKILL_SPELLBURST_FIRE)
{
}

CEffect_Fire::CEffect_Fire(const CEffect& rhs)
	: CSkillEffect(rhs)
{
}

CEffect_Fire::~CEffect_Fire()
{
}

HRESULT CEffect_Fire::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.5f, 3.f, 3.f });
	m_pTransformCom->Set_Pos(_vec3{ 170, m_pTransformCom->Get_Scale().y, 0 });

	//m_bActive = false;

	m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_IDLE);

	return S_OK;
}

_int CEffect_Fire::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CEffect_Fire::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEffect_Fire::Render_Object()
{
	__super::Render_Object();
}

HRESULT CEffect_Fire::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Skill_Fire", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	CAnimation* pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.07f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_IDLE, pAnimation);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CEffect_Fire* CEffect_Fire::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CEffect_Fire* pInstance = new CEffect_Fire(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Fire Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffect_Fire::Free()
{
	__super::Free();
}
