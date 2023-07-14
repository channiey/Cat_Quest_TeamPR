#include "stdafx.h"
#include "Effect_SpellBurst_Blue.h"

#include "Export_Function.h"

CSpellBrust_Blue::CSpellBrust_Blue(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	:CSkillEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_SKILL_CAST_BLUE)
{
}

CSpellBrust_Blue::CSpellBrust_Blue(const CEffect& rhs)
	: CSkillEffect(rhs)
{
}

CSpellBrust_Blue::~CSpellBrust_Blue()
{
}

HRESULT CSpellBrust_Blue::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 2.f, 1.f, 3.f });
	m_pTransformCom->Set_Pos(_vec3{ 140, m_pTransformCom->Get_Scale().y, 0 });

	//m_bActive = false;

	m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_IDLE);

	return S_OK;
}

_int CSpellBrust_Blue::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CSpellBrust_Blue::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSpellBrust_Blue::Render_Object()
{
	__super::Render_Object();
}

HRESULT CSpellBrust_Blue::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Skill_SpellBurst_Blue", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	CAnimation* pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.07f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_IDLE, pAnimation);

	return S_OK;
}

CSpellBrust_Blue* CSpellBrust_Blue::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CSpellBrust_Blue* pInstance = new CSpellBrust_Blue(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Spell Burst Blue Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSpellBrust_Blue::Free()
{
	__super::Free();
}
