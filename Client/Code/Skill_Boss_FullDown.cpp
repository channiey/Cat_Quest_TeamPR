#include "Skill_Boss_FullDown.h"
#include "EventMgr.h"
#include "Effect_Range_Quater.h"
#include"Export_Function.h"

#include "RangeObj.h"

CSkill_Boss_FullDown::CSkill_Boss_FullDown(LPDIRECT3DDEVICE9 pGraphicDev)
	:CSkill(pGraphicDev, OBJ_ID::SKILL_MONSTER_BASIC)

{
}

CSkill_Boss_FullDown::CSkill_Boss_FullDown(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	:CSkill(pGraphicDev, _pOwnerObject, OBJ_ID::SKILL_MONSTER_BASIC)
{
}

CSkill_Boss_FullDown::CSkill_Boss_FullDown(const CSkill_Boss_FullDown& rhs)
	:CSkill(rhs)
{
}

CSkill_Boss_FullDown::~CSkill_Boss_FullDown()
{
}

HRESULT CSkill_Boss_FullDown::Ready_Object()
{

	__super::Ready_Object();

	m_bActive = false;
	m_fSkillDamage = 40;

	m_pBaseRangeEffect = nullptr;

	// Naming
	m_szName = L"Skill_Monster_FullDown";


	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}



_int CSkill_Boss_FullDown::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);


	// Dead condition
	if (!m_pOwnerObject->Is_Active())
	{
		CEventMgr::GetInstance()->Delete_Obj(m_pRangeEffect);
		//CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect);
		//CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect);
		CEventMgr::GetInstance()->Delete_Obj(this);
		return iExit;
	}

	// Pos Setting
	_vec3 vPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS);
	m_pTransformCom->Set_Pos(vPos);






	return iExit;
}

void CSkill_Boss_FullDown::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSkill_Boss_FullDown::Render_Object()
{
	__super::Render_Object();
}

HRESULT CSkill_Boss_FullDown::Add_Component()
{
	//// Skill Effect
	//CSkillEffect* pFireEffect = CEffect_Fire::Create(m_pGraphicDev, this);
	//NULL_CHECK_RETURN(pFireEffect, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_FireSkill_Effect", pFireEffect), E_FAIL);
	//m_pSKillEffect = pFireEffect;

	//// Effect Range Quater
	//CEffect_Range_Quater* pRangeEffect = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_YELLOW);
	//NULL_CHECK_RETURN(pRangeEffect, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_FireSkill_Range", pRangeEffect), E_FAIL);
	//m_pRangeEffect = pRangeEffect;

	// Effect Range Quater - Base
	m_pBaseRangeEffect = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_FullDown_Base", m_pBaseRangeEffect), E_FAIL);


	return S_OK;
}

HRESULT CSkill_Boss_FullDown::Play()
{

	_vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO::INFO_POS);
	OBJ_ID eObjID = m_pOwnerObject->Get_ID();

	m_pBaseRangeEffect->Play_Effect(_vec3{ vOwnerPos.x, 0.01f, vOwnerPos.z + 4 });
	m_pBaseRangeEffect->Alphaing(4.f, 255.f, 80.f);
	m_pBaseRangeEffect->Scaling(2.f, 0.3f, 3.f);
	

	m_bActive = true;

	return S_OK;
}



HRESULT CSkill_Boss_FullDown::LatePlay()
{
	return S_OK;
}

HRESULT CSkill_Boss_FullDown::End()
{
	m_pBaseRangeEffect->Set_Active(FALSE);


	return S_OK;
}

CSkill_Boss_FullDown* CSkill_Boss_FullDown::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CSkill_Boss_FullDown* pInstance = new CSkill_Boss_FullDown(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("CSkill_Boss_FullDown Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSkill_Boss_FullDown::Free()
{
}
