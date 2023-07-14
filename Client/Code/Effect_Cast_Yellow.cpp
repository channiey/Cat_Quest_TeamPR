#include "stdafx.h"
#include "Effect_Cast_Yellow.h"

#include "Export_Function.h"

CCast_Yellow::CCast_Yellow(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	:CSkillEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_SKILL_CAST_BLUE)
{
}

CCast_Yellow::CCast_Yellow(const CEffect& rhs)
	: CSkillEffect(rhs)
{
}

CCast_Yellow::~CCast_Yellow()
{
}

HRESULT CCast_Yellow::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 3.f, 12.f, 3.f });
	m_pTransformCom->Set_Pos(_vec3{ 130, m_pTransformCom->Get_Scale().y, 0 });

	//m_bActive = false;

	m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_IDLE);

	return S_OK;
}

_int CCast_Yellow::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CCast_Yellow::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CCast_Yellow::Render_Object()
{
	__super::Render_Object();
}

HRESULT CCast_Yellow::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Skill_Cast_Yellow", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	CAnimation* pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.07f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_IDLE, pAnimation);

	return S_OK;
}

CCast_Yellow* CCast_Yellow::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CCast_Yellow* pInstance = new CCast_Yellow(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Cast Yellow Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CCast_Yellow::Free()
{
	__super::Free();
}
