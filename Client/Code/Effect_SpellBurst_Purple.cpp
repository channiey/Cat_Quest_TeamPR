#include "stdafx.h"
#include "Effect_SpellBurst_Purple.h"

#include "Export_Function.h"

CEffect_SpellBrust_Purple::CEffect_SpellBrust_Purple(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	:CSkillEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_SKILL_CAST_BLUE)
{
}

CEffect_SpellBrust_Purple::CEffect_SpellBrust_Purple(const CEffect& rhs)
	: CSkillEffect(rhs)
{
}

CEffect_SpellBrust_Purple::~CEffect_SpellBrust_Purple()
{
}

HRESULT CEffect_SpellBrust_Purple::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 2.f, 1.f, 3.f });
	m_pTransformCom->Set_Pos(_vec3{ 150, m_pTransformCom->Get_Scale().y, 0 });

	//m_bActive = false;

	m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_IDLE);

	return S_OK;
}

_int CEffect_SpellBrust_Purple::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CEffect_SpellBrust_Purple::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEffect_SpellBrust_Purple::Render_Object()
{
	__super::Render_Object();
}

HRESULT CEffect_SpellBrust_Purple::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Skill_SpellBurst_Purple", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	CAnimation* pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.07f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_IDLE, pAnimation);

	return S_OK;
}

CEffect_SpellBrust_Purple* CEffect_SpellBrust_Purple::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CEffect_SpellBrust_Purple* pInstance = new CEffect_SpellBrust_Purple(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Spell Burst Purple Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffect_SpellBrust_Purple::Free()
{
	__super::Free();
}