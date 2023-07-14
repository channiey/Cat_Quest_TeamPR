#include "stdafx.h"
#include "Effect_SpellBurst_Purple.h"

#include "Export_Function.h"

CSpellBrust_Purple::CSpellBrust_Purple(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	:CSkillEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_SKILL_CAST_BLUE)
{
}

CSpellBrust_Purple::CSpellBrust_Purple(const CEffect& rhs)
	: CSkillEffect(rhs)
{
}

CSpellBrust_Purple::~CSpellBrust_Purple()
{
}

HRESULT CSpellBrust_Purple::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 2.f, 1.f, 3.f });
	m_pTransformCom->Set_Pos(_vec3{ 150, m_pTransformCom->Get_Scale().y, 0 });

	//m_bActive = false;

	m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_IDLE);

	return S_OK;
}

_int CSpellBrust_Purple::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CSpellBrust_Purple::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSpellBrust_Purple::Render_Object()
{
	__super::Render_Object();
}

HRESULT CSpellBrust_Purple::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Skill_SpellBurst_Purple", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	CAnimation* pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.07f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_IDLE, pAnimation);

	return S_OK;
}

CSpellBrust_Purple* CSpellBrust_Purple::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CSpellBrust_Purple* pInstance = new CSpellBrust_Purple(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Spell Burst Purple Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSpellBrust_Purple::Free()
{
	__super::Free();
}
