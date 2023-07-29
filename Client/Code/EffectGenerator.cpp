#include "stdafx.h"
#include "EffectGenerator.h"
#include "Pollen.h"
#include "Cloud1.h"
#include "Cloud2.h"
#include "Cloud3.h"
#include "Export_Function.h"

CEffectGenerator::CEffectGenerator(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::GENERATOR, OBJ_ID::GENERATOR_POLLEN)
	
{
}

CEffectGenerator::CEffectGenerator(const CEffectGenerator& rhs)
	: Engine::CGameObject(rhs)
{
}

CEffectGenerator::~CEffectGenerator()
{
}

HRESULT CEffectGenerator::Ready_Object()
{
	m_pPlayer = nullptr;

	m_fPollen_AccTime = 0.f;
	Pollen_Caculate_CreateTime();

	m_fCloud_AccTime = 0.f;
	m_fCloud_CreateTime = 0.f;

	return S_OK;
}

_int CEffectGenerator::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	if (nullptr == m_pPlayer)
	{
		m_pPlayer = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player");
		NULL_CHECK_RETURN(m_pPlayer, E_FAIL);
	}
	else
		m_vPlayerPos = m_pPlayer->Get_Transform()->Get_Info(INFO::INFO_POS);
	
	switch (m_ePlayerLocate)
	{
	case OBJ_ID::ISLAND_RANGE_VILLAGE:
		Pollen_Create(fTimeDelta);
		Cloud_Create(fTimeDelta);
		break;
	case OBJ_ID::ISLAND_RANGE_ICE:
		Cloud_Create(fTimeDelta);
		break;
	case OBJ_ID::ISLAND_RANGE_JUMP:
		Pollen_Create(fTimeDelta);
		Cloud_Create(fTimeDelta);
		break;
	case OBJ_ID::ISLAND_RANGE_KING:
		Pollen_Create(fTimeDelta);
		Cloud_Create(fTimeDelta);
		break;
	case OBJ_ID::ISLAND_RANGE_DEATH:
		break;
	case OBJ_ID::TYPEEND:
		Pollen_Create(fTimeDelta);
		Cloud_Create(fTimeDelta);
		break;
	default:
		Pollen_Create(fTimeDelta);
		break;
	}

	return iExit;
}

void CEffectGenerator::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEffectGenerator::Render_Object()
{
}

void CEffectGenerator::Set_Locate(OBJ_ID _eLocation)
{
	m_ePlayerLocate = _eLocation;

	switch (m_ePlayerLocate)
	{
	case OBJ_ID::ISLAND_RANGE_VILLAGE:
		break;
	case OBJ_ID::ISLAND_RANGE_ICE:
		m_fPollen_AccTime = 0.f;
		for (auto iter : m_vecPollen)
			CEventMgr::GetInstance()->Delete_Obj(iter);
		m_vecPollen.clear();
		break;
	case OBJ_ID::ISLAND_RANGE_JUMP:
		break;
	case OBJ_ID::ISLAND_RANGE_KING:
		break;
	case OBJ_ID::ISLAND_RANGE_DEATH:
		m_fCloud_AccTime = 0.f;
		for (auto iter : m_vecCloud)
			CEventMgr::GetInstance()->Delete_Obj(iter);
		m_vecCloud.clear();
		break;
	case OBJ_ID::TYPEEND:
		break;
	default:
		m_fCloud_AccTime = 0.f;
		for (auto iter : m_vecCloud)
			CEventMgr::GetInstance()->Delete_Obj(iter);
		m_vecCloud.clear();
		break;
	}
}

void CEffectGenerator::Pollen_Create(const _float& fTimeDelta)
{
	m_fPollen_AccTime += fTimeDelta;
	if (m_fPollen_AccTime >= m_fPollen_CreateTime)
	{
		Pollen_Caculate_InitPos();

		CGameObject* pPollen = CPollen::Create(m_pGraphicDev, m_vPollen_CreatePos);
		NULL_CHECK(pPollen);
		m_vecPollen.push_back(pPollen);
		CEventMgr::GetInstance()->Add_Obj(L"Effect_Pollen", pPollen);

		m_fPollen_AccTime -= m_fPollen_CreateTime;
		Pollen_Caculate_CreateTime();
	}
}

void CEffectGenerator::Pollen_Caculate_CreateTime()
{
	_float fMin = 1.f;
	_float fMax = 2.f;
	_float fGenerTime = fMin + (float)(rand()) / ((float)(RAND_MAX / (fMax - fMin)));
	m_fPollen_CreateTime = floor(fGenerTime * 10) / 10;
}

void CEffectGenerator::Pollen_Caculate_InitPos()
{
	_vec3 vInitPos = m_pPlayer->Get_Transform()->Get_Info(INFO::INFO_POS);

	vInitPos.x -= 40.f;

	_float fMin = -2.f;
	_float fMax = 1.f;
	_float vInitZ = fMin + (float)(rand()) / ((float)(RAND_MAX / (fMax - fMin)));
	vInitPos.z += floor(vInitZ * 10) / 10;
	m_vPollen_CreatePos = vInitPos;
}

void CEffectGenerator::Cloud_Create(const _float& fTimeDelta)
{
	m_fCloud_AccTime += fTimeDelta;
	if (m_fCloud_AccTime >= m_fCloud_CreateTime)
	{
		for (_int i = 0; i < 10; ++i)
		{
			Cloud_Caculate_InitPos();

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> xDist1(0, 2);
			_int randomChoice = xDist1(gen);

			switch (randomChoice)
			{
			case 0:
			{
				CGameObject* pCloud = CCloud1::Create(m_pGraphicDev, m_vCloud_CreatePos);
				NULL_CHECK(pCloud);
				m_vecCloud.push_back(pCloud);
				CEventMgr::GetInstance()->Add_Obj(L"Effect_Cloud1", pCloud);
			}
			break;
			case 1:
			{
				CGameObject* pCloud = CCloud2::Create(m_pGraphicDev, m_vCloud_CreatePos);
				NULL_CHECK(pCloud);
				m_vecCloud.push_back(pCloud);
				CEventMgr::GetInstance()->Add_Obj(L"Effect_Cloud2", pCloud);
			}
			break;
			case 2:
			{
				CGameObject* pCloud = CCloud3::Create(m_pGraphicDev, m_vCloud_CreatePos);
				NULL_CHECK(pCloud);
				m_vecCloud.push_back(pCloud);
				CEventMgr::GetInstance()->Add_Obj(L"Effect_Cloud3", pCloud);
			}
			break;
			default:
				break;
			}
		}
		
		m_fCloud_AccTime -= m_fCloud_CreateTime;
		Cloud_Caculate_CreateTime();
	}
}

void CEffectGenerator::Cloud_Caculate_CreateTime()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> xDist1(12.f, 14.f);
	m_fCloud_CreateTime = xDist1(gen);
}

void CEffectGenerator::Cloud_Caculate_InitPos()
{
	m_vCloud_CreatePos = m_vPlayerPos;

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> xDist1(-90.f, -40.f);
	std::uniform_real_distribution<float> xDist2(40.f, 90.f);
	std::uniform_real_distribution<float> xDist3(-50.f, -5.f);
	std::uniform_real_distribution<float> xDist4(5.f, 50.f);
	//std::bernoulli_distribution coinFlip(0.5);

	_float randomX1 = xDist1(gen);
	_float randomX2 = xDist2(gen);
	_float randomZ1 = xDist3(gen);
	_float randomZ2 = xDist4(gen);

	std::uniform_int_distribution<int> xDist5(0, 3);
	_int randomChoice = xDist5(gen);

	switch (randomChoice)
	{
	case 0:
		m_vCloud_CreatePos.x += randomX1;
		m_vCloud_CreatePos.z += randomZ1;
	break;
	case 1:
		m_vCloud_CreatePos.x += randomX1;
		m_vCloud_CreatePos.z += randomZ2;
	break;
	case 2:
		m_vCloud_CreatePos.x += randomX2;
		m_vCloud_CreatePos.z += randomZ1;
	break;
	case 3:
		m_vCloud_CreatePos.x += randomX2;
		m_vCloud_CreatePos.z += randomZ2;
	break;
	default:
	break;
	}
}

CEffectGenerator* CEffectGenerator::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CEffectGenerator* pInstance = new CEffectGenerator(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("EffectGenerator Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffectGenerator::Free()
{
	__super::Free();
}



