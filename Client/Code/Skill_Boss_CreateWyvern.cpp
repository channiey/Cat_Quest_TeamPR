#include "Skill_Boss_CreatWyvern.h"
#include "EventMgr.h"
#include "Effect_Range_Quater.h"
#include"Export_Function.h"

#include "RangeObj.h"

CSkill_Boss_CreateWyvern::CSkill_Boss_CreateWyvern(LPDIRECT3DDEVICE9 pGraphicDev)
	:CSkill(pGraphicDev, OBJ_ID::SKILL_BOSS_CREATE_WYVERN)

{
}

CSkill_Boss_CreateWyvern::CSkill_Boss_CreateWyvern(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	:CSkill(pGraphicDev, _pOwnerObject, OBJ_ID::SKILL_BOSS_CREATE_WYVERN)
{
}

CSkill_Boss_CreateWyvern::CSkill_Boss_CreateWyvern(const CSkill_Boss_CreateWyvern& rhs)
	:CSkill(rhs)
{
}

CSkill_Boss_CreateWyvern::~CSkill_Boss_CreateWyvern()
{
}

HRESULT CSkill_Boss_CreateWyvern::Ready_Object()
{

	__super::Ready_Object();

	m_bActive = false;
	m_fSkillDamage = 0;

	vCreatePosition = vec3.zero;
	vCreateBossPosition = vec3.zero;
	// Naming
	m_szName = L"Skill_Boss_CreateWyvern";



	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);





	return S_OK;
}



_int CSkill_Boss_CreateWyvern::Update_Object(const _float& fTimeDelta)
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
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect5);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect6);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect7);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect8);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect9);
		CEventMgr::GetInstance()->Delete_Obj(m_pBaseRangeEffect10);
		CEventMgr::GetInstance()->Delete_Obj(this);
		return iExit;
	}

	// Pos Setting
	_vec3 vPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS);
	m_pTransformCom->Set_Pos(vPos);






	return iExit;
}

void CSkill_Boss_CreateWyvern::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSkill_Boss_CreateWyvern::Render_Object()
{
	__super::Render_Object();
}

HRESULT CSkill_Boss_CreateWyvern::Add_Component()
{
	// Effect Range Quater - Base  1
	m_pBaseRangeEffect1 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect1, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Create_Base1", m_pBaseRangeEffect1), E_FAIL);
	m_pBaseRangeEffect1->Get_Transform()->Set_Scale(_vec3(0.4f, 0.4f, 0.4f));

	// Effect Range Quater - Base  2
	m_pBaseRangeEffect2 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect2, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Create_Base2", m_pBaseRangeEffect2), E_FAIL);
	

	// Effect Range Quater - Base  3
	m_pBaseRangeEffect3 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect3, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Create_Base3", m_pBaseRangeEffect3), E_FAIL);


	// Effect Range Quater - Base  4
	m_pBaseRangeEffect4 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect4, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Create_Base4", m_pBaseRangeEffect4), E_FAIL);
	

	// Effect Range Quater - Base 5
	m_pBaseRangeEffect5 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect5, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Create_Base5", m_pBaseRangeEffect5), E_FAIL);


	// Effect Range Quater - Base 6
	m_pBaseRangeEffect6 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect6, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Create_Base6", m_pBaseRangeEffect6), E_FAIL);


	// Effect Range Quater - Base 7
	m_pBaseRangeEffect7 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect7, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Create_Base7", m_pBaseRangeEffect7), E_FAIL);


	// Effect Range Quater - Base 8
	m_pBaseRangeEffect8 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect8, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Create_Base8", m_pBaseRangeEffect8), E_FAIL);


	// Effect Range Quater - Base  9
	m_pBaseRangeEffect9 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect9, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Create_Base9", m_pBaseRangeEffect9), E_FAIL);


	// Effect Range Quater - Base 10
	m_pBaseRangeEffect10 = CEffect_Range_Quater::Create(m_pGraphicDev, this, EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED);
	NULL_CHECK_RETURN(m_pBaseRangeEffect10, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Create_Base10", m_pBaseRangeEffect10), E_FAIL);







	return S_OK;
}

HRESULT CSkill_Boss_CreateWyvern::Play()
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


	vCreatePosition = vPlayerPos;
	vCreateBossPosition = vOwnerPos;

	_float fCastTime	= 0.5f;
	_float fStartAlpha	= 0.f;
	_float fEndAlpha	= 255.f;
	_float fStartScale	= 0.5f;
	_float fEndScale	= 0.5f;

	// Very Near 1
	m_pBaseRangeEffect1->Play_Effect(_vec3{ vPlayerPos.x +5.f , 0.01f ,vPlayerPos.z });
	m_pBaseRangeEffect1->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect1->Get_Transform()->Set_Scale(_vec3{ 0.1f, 0.1f, 0.1f });
	m_pBaseRangeEffect1->Scaling(fCastTime, fStartScale, fEndScale);


	// Very Near 2
	m_pBaseRangeEffect2->Play_Effect(_vec3{ vPlayerPos.x - 5.f , 0.01f ,vPlayerPos.z });
	m_pBaseRangeEffect2->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect2->Get_Transform()->Set_Scale(_vec3{ 0.1f, 0.1f, 0.1f });
	m_pBaseRangeEffect2->Scaling(fCastTime, fStartScale, fEndScale);


	// Near 1
	m_pBaseRangeEffect3->Play_Effect(_vec3{ vPlayerPos.x - 10.f , 0.01f ,vPlayerPos.z + 10.f });
	m_pBaseRangeEffect3->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect3->Scaling(fCastTime, fStartScale, fEndScale);


	// Near 2
	m_pBaseRangeEffect4->Play_Effect(_vec3{ vPlayerPos.x + 10.f , 0.01f ,vPlayerPos.z + 10.f });
	m_pBaseRangeEffect4->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect4->Scaling(fCastTime, fStartScale, fEndScale);


	// Near 3
	m_pBaseRangeEffect5->Play_Effect(_vec3{ vPlayerPos.x - 10.f , 0.01f ,vPlayerPos.z - 10.f });
	m_pBaseRangeEffect5->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect5->Scaling(fCastTime, fStartScale, fEndScale);

	// Near 4
	m_pBaseRangeEffect6->Play_Effect(_vec3{ vPlayerPos.x + 10.f , 0.01f ,vPlayerPos.z - 10.f });
	m_pBaseRangeEffect6->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect6->Scaling(fCastTime, fStartScale, fEndScale);


	// Boss Near 1
	m_pBaseRangeEffect7->Play_Effect(_vec3{ vOwnerPos.x - 5.f , 0.01f ,vOwnerPos.z - 5.f });
	m_pBaseRangeEffect7->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect7->Scaling(fCastTime, fStartScale, fEndScale);

	// Boss Near 2
	m_pBaseRangeEffect8->Play_Effect(_vec3{ vOwnerPos.x - 5.f , 0.01f ,vOwnerPos.z + 5.f });
	m_pBaseRangeEffect8->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect8->Scaling(fCastTime, fStartScale, fEndScale);


	// Boss Near 3
	m_pBaseRangeEffect9->Play_Effect(_vec3{ vOwnerPos.x + 5.f , 0.01f ,vOwnerPos.z - 5.f });
	m_pBaseRangeEffect9->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect9->Scaling(fCastTime, fStartScale, fEndScale);


	// Boss Near 4
	m_pBaseRangeEffect10->Play_Effect(_vec3{ vOwnerPos.x + 5.f , 0.01f ,vOwnerPos.z + 5.f });
	m_pBaseRangeEffect10->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect10->Scaling(fCastTime, fStartScale, fEndScale);

	return S_OK;
}



HRESULT CSkill_Boss_CreateWyvern::LatePlay()
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


	_float fCastTime	= 0.3f;
	_float fStartAlpha	= 255.f;
	_float fEndAlpha	= 0.f;
	_float fStartScale	= 0.5f;
	_float fEndScale	= 0.5f;

	// Very Near 1
	m_pBaseRangeEffect1->Play_Effect(_vec3{ vCreatePosition.x + 5.f , 0.01f ,vCreatePosition.z });
	m_pBaseRangeEffect1->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect1->Scaling(fCastTime, fStartScale, fEndScale);


	// Very Near 2
	m_pBaseRangeEffect2->Play_Effect(_vec3{ vCreatePosition.x - 5.f , 0.01f ,vCreatePosition.z });
	m_pBaseRangeEffect2->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect2->Scaling(fCastTime, fStartScale, fEndScale);


	// Near 1
	m_pBaseRangeEffect3->Play_Effect(_vec3{ vCreatePosition.x - 10.f , 0.01f ,vCreatePosition.z + 10.f });
	m_pBaseRangeEffect3->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect3->Scaling(fCastTime, fStartScale, fEndScale);


	// Near 2
	m_pBaseRangeEffect4->Play_Effect(_vec3{ vCreatePosition.x + 10.f , 0.01f ,vCreatePosition.z + 10.f });
	m_pBaseRangeEffect4->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect4->Scaling(fCastTime, fStartScale, fEndScale);


	// Near 3
	m_pBaseRangeEffect5->Play_Effect(_vec3{ vCreatePosition.x - 10.f , 0.01f ,vCreatePosition.z - 10.f });
	m_pBaseRangeEffect5->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect5->Scaling(fCastTime, fStartScale, fEndScale);

	// Near 4
	m_pBaseRangeEffect6->Play_Effect(_vec3{ vCreatePosition.x + 10.f , 0.01f ,vCreatePosition.z - 10.f });
	m_pBaseRangeEffect6->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect6->Scaling(fCastTime, fStartScale, fEndScale);


	// Boss Near 1
	m_pBaseRangeEffect7->Play_Effect(_vec3{ vCreateBossPosition.x - 5.f , 0.01f ,vCreateBossPosition.z - 5.f });
	m_pBaseRangeEffect7->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect7->Scaling(fCastTime, fStartScale, fEndScale);

	// Boss Near 2
	m_pBaseRangeEffect8->Play_Effect(_vec3{ vCreateBossPosition.x - 5.f , 0.01f ,vCreateBossPosition.z + 5.f });
	m_pBaseRangeEffect8->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect8->Scaling(fCastTime, fStartScale, fEndScale);


	// Boss Near 3
	m_pBaseRangeEffect9->Play_Effect(_vec3{ vCreateBossPosition.x + 5.f , 0.01f ,vCreateBossPosition.z - 5.f });
	m_pBaseRangeEffect9->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect9->Scaling(fCastTime, fStartScale, fEndScale);


	// Boss Near 4
	m_pBaseRangeEffect10->Play_Effect(_vec3{ vCreateBossPosition.x + 5.f , 0.01f ,vCreateBossPosition.z + 5.f });
	m_pBaseRangeEffect10->Alphaing(fCastTime, fStartAlpha, fEndAlpha);
	m_pBaseRangeEffect10->Scaling(fCastTime, fStartScale, fEndScale);



	return S_OK;
}

HRESULT CSkill_Boss_CreateWyvern::End()
{
	m_pBaseRangeEffect1->Set_Active(false);
	m_pBaseRangeEffect2->Set_Active(false);
	m_pBaseRangeEffect3->Set_Active(false);
	m_pBaseRangeEffect4->Set_Active(false);
	m_pBaseRangeEffect5->Set_Active(false);
	m_pBaseRangeEffect6->Set_Active(false);
	m_pBaseRangeEffect7->Set_Active(false);
	m_pBaseRangeEffect8->Set_Active(false);
	m_pBaseRangeEffect9->Set_Active(false);
	m_pBaseRangeEffect10->Set_Active(false);


	return S_OK;
}

CSkill_Boss_CreateWyvern* CSkill_Boss_CreateWyvern::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CSkill_Boss_CreateWyvern* pInstance = new CSkill_Boss_CreateWyvern(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("CSkill_Boss_CreateWyvern Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSkill_Boss_CreateWyvern::Free()
{
	__super::Free();
}
