#include "Skill_Boss_BloodyThunder.h"
#include "Export_Function.h"
#include "Effect_Boss_Thunder.h"
#include "EventMgr.h"
#include "Effect_Range_Quater.h"

CSkill_Boss_BloodyThunder::CSkill_Boss_BloodyThunder(LPDIRECT3DDEVICE9 pGraphicDev)
	:CSkill(pGraphicDev, OBJ_ID::SKILL_BOSS_BLOODYTHUNDER)
{
}

CSkill_Boss_BloodyThunder::CSkill_Boss_BloodyThunder(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	:CSkill(pGraphicDev, _pOwnerObject, OBJ_ID::SKILL_BOSS_BLOODYTHUNDER)
{
}

CSkill_Boss_BloodyThunder::CSkill_Boss_BloodyThunder(const CSkill_Boss_BloodyThunder& rhs)
	:CSkill(rhs)
{
}

CSkill_Boss_BloodyThunder::~CSkill_Boss_BloodyThunder()
{
}

HRESULT CSkill_Boss_BloodyThunder::Ready_Object()
{

	__super::Ready_Object();

	m_bActive = false;
	m_fSkillDamage = 40;

	m_bBaseEffectEnd = false;
	m_bSkillEffectEnd = false;


	// Naming
	m_szName = L"Skill_Boss_BloodyThunder";


	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
}

_int CSkill_Boss_BloodyThunder::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);


	// Dead condition
	if (!m_pOwnerObject->Is_Active())
	{
		End();

		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect1);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect2);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect3);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect4);
		//CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect5);
		

		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect1);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect2);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect3);
		CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect4);
		//CEventMgr::GetInstance()->Delete_Obj(m_pSKillEffect5);
		
		CEventMgr::GetInstance()->Delete_Obj(this);
		return iExit;
	}

	// Pos Setting
	//_vec3 vPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS);
	//m_pTransformCom->Set_Pos(vPos);




	return iExit;
}

void CSkill_Boss_BloodyThunder::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSkill_Boss_BloodyThunder::Render_Object()
{
	__super::Render_Object();
}

HRESULT CSkill_Boss_BloodyThunder::Add_Component()
{

	// Skill Effect
	CSkillEffect* pThunderEffect1 = CEffect_Boss_Thunder::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pThunderEffect1, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Bossr_BloodyThunder_Effect1", pThunderEffect1), E_FAIL);
	m_pSKillEffect1 = pThunderEffect1;
	
	CSkillEffect* pThunderEffect2 = CEffect_Boss_Thunder::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pThunderEffect2, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Bossr_BloodyThunder_Effect2", pThunderEffect2), E_FAIL);
	m_pSKillEffect2 = pThunderEffect2;

	CSkillEffect* pThunderEffect3 = CEffect_Boss_Thunder::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pThunderEffect3, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Bossr_BloodyThunder_Effect3", pThunderEffect3), E_FAIL);
	m_pSKillEffect3 = pThunderEffect3;

	CSkillEffect* pThunderEffect4 = CEffect_Boss_Thunder::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pThunderEffect4, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Bossr_BloodyThunder_Effect4", pThunderEffect4), E_FAIL);
	m_pSKillEffect4 = pThunderEffect4;

	/*CSkillEffect* pThunderEffect5 = CEffect_Boss_Thunder::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pThunderEffect5, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Bossr_BloodyThunder_Effect5", pThunderEffect5), E_FAIL);
	m_pSKillEffect5 = pThunderEffect5;*/


	// Effect Range Quater - Base
	m_pBaseRangeEffect1 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect1, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_BloodyThunder_Base1", m_pBaseRangeEffect1), E_FAIL);

	m_pBaseRangeEffect2 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect2, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_BloodyThunder_Base2", m_pBaseRangeEffect2), E_FAIL);

	m_pBaseRangeEffect3 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect3, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_BloodyThunder_Base3", m_pBaseRangeEffect3), E_FAIL);

	m_pBaseRangeEffect4 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect4, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_BloodyThunder_Base4", m_pBaseRangeEffect4), E_FAIL);


	//m_pBaseRangeEffect5 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	//NULL_CHECK_RETURN(m_pBaseRangeEffect5, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_BloodyThunder_Base5", m_pBaseRangeEffect5), E_FAIL);


	return S_OK;
}

HRESULT CSkill_Boss_BloodyThunder::Play()
{
	_vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS); // Boss Pos 
	NULL_CHECK_RETURN(vOwnerPos, E_FAIL);

	// Player - Transform Com
	CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
	NULL_CHECK_RETURN(pPlayerTransform, E_FAIL);

	// Player - Pos
	_vec3       vPlayerPos;
	vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);
	NULL_CHECK_RETURN(pPlayerTransform, E_FAIL);

	// 1
	m_pBaseRangeEffect1->Play_Effect(_vec3{ vOwnerPos.x - 20, 0.01f, vOwnerPos.z+ 20 });
	m_pBaseRangeEffect1->Alphaing(2.f, 80.f, 255.f);
	m_pBaseRangeEffect1->Scaling(2.f, 0.3f, 1.f);

	// 2
	m_pBaseRangeEffect2->Play_Effect(_vec3{ vOwnerPos.x + 20 , 0.01f, vOwnerPos.z +20 });
	m_pBaseRangeEffect2->Alphaing(2.f, 80.f, 255.f);
	m_pBaseRangeEffect2->Scaling(2.f, 0.3f, 1.f);

	// 3
	m_pBaseRangeEffect3->Play_Effect(_vec3{ vOwnerPos.x -20 , 0.01f, vOwnerPos.z -20 });
	m_pBaseRangeEffect3->Alphaing(2.f, 80.f, 255.f);
	m_pBaseRangeEffect3->Scaling(2.f, 0.3f, 1.f);

	// 4
	m_pBaseRangeEffect4->Play_Effect(_vec3{ vOwnerPos.x +20 , 0.01f, vOwnerPos.z -20 });
	m_pBaseRangeEffect4->Alphaing(2.f, 80.f, 255.f);
	m_pBaseRangeEffect4->Scaling(2.f, 0.3f, 1.f);


	// 5
	//m_pBaseRangeEffect5->Play_Effect(_vec3{ vPlayerPos.x, 0.01f, vPlayerPos.z });
	//m_pBaseRangeEffect5->Alphaing(2.f, 80.f, 255.f);
	//m_pBaseRangeEffect5->Scaling(2.f, 0.3f, 1.f);


	return S_OK;


}

HRESULT CSkill_Boss_BloodyThunder::LatePlay()
{
	_vec3 vOwnerPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS); // Boss Pos 
	NULL_CHECK_RETURN(vOwnerPos, E_FAIL);

	// Player - Transform Com
	CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
	NULL_CHECK_RETURN(pPlayerTransform, E_FAIL);

	// Player - Pos
	_vec3       vPlayerPos;
	vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);
	NULL_CHECK_RETURN(pPlayerTransform, E_FAIL);




	// 1
	m_pBaseRangeEffect1->Play_Effect(_vec3{ vOwnerPos.x - 20, 0.01f, vOwnerPos.z + 20 });
	m_pBaseRangeEffect1->Alphaing(0.2f, 255.f, 0.f);
	m_pBaseRangeEffect1->Scaling(2.f, 0.3f, 1.f);

	// 2
	m_pBaseRangeEffect2->Play_Effect(_vec3{ vOwnerPos.x + 20 , 0.01f, vOwnerPos.z + 20 });
	m_pBaseRangeEffect2->Alphaing(0.2f, 255.f, 0.f);
	m_pBaseRangeEffect2->Scaling(2.f, 0.3f, 1.f);

	// 3
	m_pBaseRangeEffect3->Play_Effect(_vec3{ vOwnerPos.x - 20 , 0.01f, vOwnerPos.z - 20 });
	m_pBaseRangeEffect3->Alphaing(0.2f, 255.f, 0.f);
	m_pBaseRangeEffect3->Scaling(2.f, 0.3f, 1.f);

	// 4
	m_pBaseRangeEffect4->Play_Effect(_vec3{ vOwnerPos.x + 20 , 0.01f, vOwnerPos.z - 20 });
	m_pBaseRangeEffect4->Alphaing(0.2f, 255.f, 0.f);
	m_pBaseRangeEffect4->Scaling(2.f, 0.3f, 1.f);


	// 5
	//m_pBaseRangeEffect5->Play_Effect(_vec3{ vPlayerPos.x, 0.01f, vPlayerPos.z });
	//m_pBaseRangeEffect5->Alphaing(2.f, 255.f, 0.f);
	//m_pBaseRangeEffect5->Scaling(2.f, 0.3f, 1.f);




	_float fSkillEffectScaleY = m_pSKillEffect1->Get_Transform()->Get_Scale().y;


	m_pSKillEffect1->Play_Effect(_vec3{ vOwnerPos.x - 20 , 0.01f  , vOwnerPos.z + 20 });
	m_pSKillEffect2->Play_Effect(_vec3{ vOwnerPos.x + 20 , 0.01f  , vOwnerPos.z + 20 });
	m_pSKillEffect3->Play_Effect(_vec3{ vOwnerPos.x - 20 , 0.01f  , vOwnerPos.z - 20 });
	m_pSKillEffect4->Play_Effect(_vec3{ vOwnerPos.x + 20 , 0.01f  , vOwnerPos.z - 20 });
	//m_pSKillEffect5->Play_Effect(_vec3{ vPlayerPos.x, 0.01f, vPlayerPos.z });
	


	return S_OK;
}

HRESULT CSkill_Boss_BloodyThunder::End()
{

	 m_pBaseRangeEffect1->Set_Active(false);
	 m_pBaseRangeEffect2->Set_Active(false);
	 m_pBaseRangeEffect3->Set_Active(false);
	 m_pBaseRangeEffect4->Set_Active(false);
	// m_pBaseRangeEffect5->Set_Active(false);

	return S_OK;
}

HRESULT CSkill_Boss_BloodyThunder::LateEnd()
{


	m_pSKillEffect1->Set_Active(false);
	m_pSKillEffect2->Set_Active(false);
	m_pSKillEffect3->Set_Active(false);
	m_pSKillEffect4->Set_Active(false);
	//m_pSKillEffect5->Set_Active(false);

	return E_NOTIMPL;
}

CSkill_Boss_BloodyThunder* CSkill_Boss_BloodyThunder::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CSkill_Boss_BloodyThunder* pInstance = new CSkill_Boss_BloodyThunder(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("CSkill_Boss_BloodyThunder Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSkill_Boss_BloodyThunder::Free()
{
	__super::Free();
}
