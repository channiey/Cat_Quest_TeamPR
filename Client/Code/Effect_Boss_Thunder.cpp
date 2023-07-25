#include "stdafx.h"
#include "Effect_Boss_Thunder.h"

#include "Export_Function.h"

CEffect_Boss_Thunder::CEffect_Boss_Thunder(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject ,CGameObject* _TargetObject)
	:CSkillEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_BOSS_THUNDER)
{
}

CEffect_Boss_Thunder::CEffect_Boss_Thunder(const CEffect& rhs)
	: CSkillEffect(rhs)
{
}

CEffect_Boss_Thunder::~CEffect_Boss_Thunder()
{
}

HRESULT CEffect_Boss_Thunder::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);




	m_pTransformCom->Set_Scale(_vec3{ 17.f, 17.f, 17.f });
	//m_pTransformCom->Set_Pos();

	m_bActive = false;

	m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_IDLE);

	return S_OK;
}

_int CEffect_Boss_Thunder::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	if (m_bActive && m_pAnimatorCom->Get_CurAniamtion()->Is_End())
		m_bActive = false;

	return iExit;
}

void CEffect_Boss_Thunder::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEffect_Boss_Thunder::Render_Object()
{
	__super::Render_Object();
}

void CEffect_Boss_Thunder::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_pTransformCom->Set_Pos(_vec3{ _vPos.x, m_pTransformCom->Get_Info(INFO::INFO_POS).y, _vPos.z + 5.2f });
	m_bActive = true;
	m_pAnimatorCom->Set_Animation(STATE_TYPE::FRONT_IDLE);
}

HRESULT CEffect_Boss_Thunder::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Boss_Thunder", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	CAnimation* pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.05f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_IDLE, pAnimation);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CEffect_Boss_Thunder* CEffect_Boss_Thunder::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, CGameObject* _TargetObject)
{
	CEffect_Boss_Thunder* pInstance = new CEffect_Boss_Thunder(pGraphicDev, _pOwnerObject , _TargetObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Thunder Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffect_Boss_Thunder::Free()
{
	__super::Free();
}
