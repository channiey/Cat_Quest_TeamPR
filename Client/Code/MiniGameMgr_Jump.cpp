#include "MiniGameMgr_Jump.h"
#include "stdafx.h"
#include "Export_Function.h"

// Island
#include "Island_Ice.h"
#include "Island_Death.h"
#include "Island_Jump.h"
#include "Island_Village.h"
#include "Island_King.h"

#include "CameraMgr.h"
#include "Player.h"

IMPLEMENT_SINGLETON(CMiniGameMgr_Jump)

CMiniGameMgr_Jump::CMiniGameMgr_Jump()
	: m_bInit(FALSE)
	, m_bActive(FALSE)
{
}

CMiniGameMgr_Jump::~CMiniGameMgr_Jump()
{
}

HRESULT CMiniGameMgr_Jump::Init(LPDIRECT3DDEVICE9 _pGraphicDev)
{
    m_pGraphicDev = _pGraphicDev;
	m_bInit = TRUE;
    return S_OK;
}

void CMiniGameMgr_Jump::Update(const _float& _fDelta)
{
	if (!m_bActive) return;

	Check_MiniGame();
}

HRESULT CMiniGameMgr_Jump::Start_MiniGame()
{
	m_bActive = TRUE;

	cout << "-------------------------미니게임 스타트\n";
	return S_OK;
}

HRESULT CMiniGameMgr_Jump::End_MiniGame()
{
	m_bActive = FALSE;
	cout << "-------------------------미니게임 엔드\n";
	return S_OK;
}

void CMiniGameMgr_Jump::Check_MiniGame()
{
	/*
		* 플레이어 사망 조건
		
			* 백뷰이고
			* 점프 상태가 아니고
			* 현재 점프섬과 충돌하고 있지 않다면
	*/

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));

	NULL_CHECK(pPlayer);

	if (CCameraMgr::GetInstance()->Is_BackView() && !pPlayer->Is_Jump() && !m_arrIsland[(UINT)ISLAND_TYPE::JUMP]->Is_In_Player())
		cout << "플레이어 사망\n";
	else
		cout << "플레이어 굿굿\n";
}

HRESULT CMiniGameMgr_Jump::Create_Islands()
{
	CIsland* pGameObject = nullptr;

	pGameObject = CIsland_Village::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);
	m_arrIsland[(UINT)ISLAND_TYPE::VILLAGE] = pGameObject;

	pGameObject = CIsland_Ice::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);
	m_arrIsland[(UINT)ISLAND_TYPE::ICE] = pGameObject;

	pGameObject = CIsland_Death::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);
	m_arrIsland[(UINT)ISLAND_TYPE::DEATH] = pGameObject;

	pGameObject = CIsland_Jump::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);
	m_arrIsland[(UINT)ISLAND_TYPE::JUMP] = pGameObject;

	pGameObject = CIsland_King::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);
	m_arrIsland[(UINT)ISLAND_TYPE::KING] = pGameObject;

	return S_OK;
}


void CMiniGameMgr_Jump::Free()
{
}
