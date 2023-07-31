#include "stdafx.h"
#include "EffectGenerator.h"
#include "Pollen.h"
#include "Cloud1.h"
#include "Cloud2.h"
#include "Cloud3.h"
#include "Export_Function.h"
#include "Player.h"

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
	m_iChoice = 0;

	m_fSnow_AccTime = 0.f;
	Snow_Caculate_CreateTime();

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
		//Snow_Create(fTimeDelta);
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
		Rain_Create(fTimeDelta);
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
		m_fSnow_AccTime = 0.f;
		m_fRain_AccTime = 0.f;
		break;
	case OBJ_ID::ISLAND_RANGE_ICE:
		m_fPollen_AccTime = 0.f;
		m_fRain_AccTime = 0.f;
		break;
	case OBJ_ID::ISLAND_RANGE_JUMP:
		m_fSnow_AccTime = 0.f;
		m_fRain_AccTime = 0.f;
		break;
	case OBJ_ID::ISLAND_RANGE_KING:
		m_fSnow_AccTime = 0.f;
		m_fRain_AccTime = 0.f;
		break;
	case OBJ_ID::ISLAND_RANGE_DEATH:
		m_fCloud_AccTime = 0.f;
		m_fPollen_AccTime = 0.f;
		m_fSnow_AccTime = 0.f;
		break;
	case OBJ_ID::TYPEEND:
		m_fSnow_AccTime = 0.f;
		m_fRain_AccTime = 0.f;
		break;
	default:
		m_fSnow_AccTime = 0.f;
		m_fRain_AccTime = 0.f;
		m_fCloud_AccTime = 0.f;
		break;
	}
}

#pragma region Pollen
void CEffectGenerator::Pollen_Create(const _float& fTimeDelta)
{
	m_fPollen_AccTime += fTimeDelta;
	if (m_fPollen_AccTime >= m_fPollen_CreateTime)
	{
		Pollen_Caculate_InitPos();

		CGameObject* pPollen = CPollen::Create(m_pGraphicDev, m_vPollen_CreatePos);
		NULL_CHECK(pPollen);
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


#pragma endregion

#pragma region Cloud
void CEffectGenerator::Cloud_Create(const _float& fTimeDelta)
{
	const _int iCreateNum = 2;

	m_fCloud_AccTime += fTimeDelta;
	if (m_fCloud_AccTime >= m_fCloud_CreateTime)
	{
		for (_int i = 0; i < iCreateNum; ++i)
		{
			Cloud_Caculate_InitPos();

			std::mt19937 gen(m_Random());

			std::uniform_int_distribution<int> xDist1(0, 2);
			_int randomChoice = xDist1(gen);

			switch (randomChoice)
			{
			case 0:
			{
				CGameObject* pCloud = CCloud1::Create(m_pGraphicDev, m_vCloud_CreatePos);
				NULL_CHECK(pCloud);
				CEventMgr::GetInstance()->Add_Obj(L"Effect_Cloud1", pCloud);
			}
			break;
			case 1:
			{
				CGameObject* pCloud = CCloud2::Create(m_pGraphicDev, m_vCloud_CreatePos);
				NULL_CHECK(pCloud);
				CEventMgr::GetInstance()->Add_Obj(L"Effect_Cloud2", pCloud);
			}
			break;
			case 2:
			{
				CGameObject* pCloud = CCloud3::Create(m_pGraphicDev, m_vCloud_CreatePos);
				NULL_CHECK(pCloud);
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
	NULL_CHECK(m_pPlayer)

		std::mt19937 gen(m_Random());

	if (static_cast<CPlayer*>(m_pPlayer)->Get_StateM()->Get_CurState() == STATE_TYPE::FRONT_WALK ||
		static_cast<CPlayer*>(m_pPlayer)->Get_StateM()->Get_CurState() == STATE_TYPE::BACK_WALK)
	{
		std::uniform_real_distribution<float> xDist1(2.f, 3.5f);
		m_fCloud_CreateTime = xDist1(gen);
	}
	else
	{
		std::uniform_real_distribution<float> xDist1(8.f, 12.f);
		m_fCloud_CreateTime = xDist1(gen);
	}


}

void CEffectGenerator::Cloud_Caculate_InitPos()
{
	m_vCloud_CreatePos = m_vPlayerPos;

	std::mt19937 gen(m_Random());

	std::uniform_real_distribution<float> xDist1(-50.f, -5.f);
	std::uniform_real_distribution<float> xDist2(5.f, 50.f);
	std::uniform_real_distribution<float> xDist3(-30.f, -1.f);
	std::uniform_real_distribution<float> xDist4(1.f, 30.f);
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

	++m_iChoice;
	if (m_iChoice > 3)
		m_iChoice = 0;

}
#pragma endregion

#pragma region Snow
void CEffectGenerator::Snow_Create(const _float& fTimeDelta)
{
	m_fSnow_AccTime += fTimeDelta;
	if (m_fSnow_AccTime >= m_fSnow_CreateTime)
	{
		Snow_Caculate_InitPos();

		CGameObject* pSnow = CPollen::Create(m_pGraphicDev, m_vSnow_CreatePos);
		NULL_CHECK(pSnow);
		CEventMgr::GetInstance()->Add_Obj(L"Effect_Snow", pSnow);

		m_fPollen_AccTime -= m_fPollen_CreateTime;
		Snow_Caculate_CreateTime();
	}
}

void CEffectGenerator::Snow_Caculate_CreateTime()
{
	_float fMin = 1.f;
	_float fMax = 2.f;
	_float fGenerTime = fMin + (float)(rand()) / ((float)(RAND_MAX / (fMax - fMin)));
	m_fSnow_CreateTime = floor(fGenerTime * 10) / 10;
}

void CEffectGenerator::Snow_Caculate_InitPos()
{
	_vec3 vInitPos = m_pPlayer->Get_Transform()->Get_Info(INFO::INFO_POS);


	_float fMin = -30.f;
	_float fMax = 30.f;
	_float vInitX = fMin + (float)(rand()) / ((float)(RAND_MAX / (fMax - fMin)));
	vInitPos.x += floor(vInitX * 10) / 10;

	fMin = 10.f;
	fMax = 20.f;
	_float vInitY = fMin + (float)(rand()) / ((float)(RAND_MAX / (fMax - fMin)));
	vInitPos.y += floor(vInitY * 10) / 10;


	fMin = 20.f;
	fMax = 40.f;
	_float vInitZ = fMin + (float)(rand()) / ((float)(RAND_MAX / (fMax - fMin)));
	vInitPos.z += floor(vInitZ * 10) / 10;
	m_vSnow_CreatePos = vInitPos;
}
#pragma endregion

#pragma region Rain


#pragma endregion


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



