#include "BossSceneMgr.h"
#include "stdafx.h"
#include "Export_Function.h"

#include "CameraMgr.h"
#include "Player.h"
#include "SoundMgr.h"
#include "Player_Camera.h"
#include "VioletDragon.h"
#include "Npc_Citizen2.h"

IMPLEMENT_SINGLETON(CBossSceneMgr)

CBossSceneMgr::CBossSceneMgr()
	: m_fAcc(0.f)
	, m_fDeadFadeStayTime(1.5f)
	, m_bFadeIn_End(FALSE)
	, m_bFadeOut_End(FALSE)
{
	for (int i = 0; i < (_uint)PAGE::TYPEEND; ++i)
		m_arrPage[i] = FALSE;
}

CBossSceneMgr::~CBossSceneMgr()
{
}

HRESULT CBossSceneMgr::Ready_BossSceneMgr(LPDIRECT3DDEVICE9 _pGraphicDev)
{
	if (m_arrPage[(_uint)PAGE::INIT]) return E_FAIL;

	m_arrPage[(_uint)PAGE::INIT] = TRUE;

	m_pGraphicDev = _pGraphicDev;

	return S_OK;
}

void CBossSceneMgr::Update_BossSceneMgr(const _float& fTimeDelta)
{
	if (!m_arrPage[(_uint)PAGE::START] || m_arrPage[(_uint)PAGE::FINISH]) return;

	if (m_arrPage[(_uint)PAGE::DEAD] && !m_bFadeOut_End && !m_bFadeIn_End)
	{
		if (!CCameraMgr::GetInstance()->Is_Fade())
		{
			m_fAcc += fTimeDelta;
			//cout << m_fAcc << endl;
			if (m_fDeadFadeStayTime <= m_fAcc)
			{
				//cout << "03. START FADE IN\n";

				CCameraMgr::GetInstance()->Start_Fade(FADE_MODE::WHITE_FADE_IN);
				CSoundMgr::GetInstance()->Lerp_Volume_CurBGM(LERP_MODE::EXPONENTIAL, 2.5f, 0.f, SOUND_VOLUME_BGM);
				CSoundMgr::GetInstance()->PlayBGM(L"catquest_overworld_02_theme.wav");

				m_bFadeOut_End = TRUE;
				Set_Npc();
			}
		}
	}

	if (m_arrPage[(_uint)PAGE::DEAD] && m_bFadeOut_End && !m_bFadeIn_End)
	{
		if (!CCameraMgr::GetInstance()->Is_Fade())
		{
			//cout << "04. FINISH\n";
			m_bFadeIn_End = TRUE;
			m_arrPage[(_uint)PAGE::FINISH] = TRUE;
		}
	}

}

HRESULT CBossSceneMgr::Start_BossScene()
{
	if (!m_arrPage[(_uint)PAGE::INIT] || m_arrPage[(_uint)PAGE::START]) return E_FAIL;

	m_arrPage[(_uint)PAGE::START] = TRUE;

	// 보스 활성화
	//cout << "01. ACTIVATE BOSS \n";

	CGameObject* pBoss = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::MONSTER, L"Monster_VioletDragon");
	NULL_CHECK_RETURN(pBoss, E_FAIL);
	pBoss->Set_Active(TRUE);
	CSoundMgr::GetInstance()->ChangeBGM(L"catquest_battle_theme.wav");

	return S_OK;
}

void CBossSceneMgr::Play_Dead_BossScene()
{
	//cout << "02. START FADE OUT\n";
	
	// 카메라 페이드 아웃
	CCameraMgr::GetInstance()->Start_Fade(FADE_MODE::WHITE_FADE_OUT);
	m_arrPage[(_uint)PAGE::DEAD] = TRUE;

	// 브금 사운드 페이드 아웃
	CSoundMgr::GetInstance()->Lerp_Volume_CurBGM(LERP_MODE::EASE_OUT, 3.5f, SOUND_VOLUME_BGM, 0.f);

}

void CBossSceneMgr::Set_Npc()
{
	CGameObject* pPlayer = CManagement::GetInstance()->Get_Player();
	NULL_CHECK(pPlayer);
	_vec3 vPlayerPos = pPlayer->Get_Transform()->Get_Info(INFO_POS);

	CGameObject* pNpc = nullptr;
	_vec3 vNpcPos, vNewPos, vNpcScale;
	
	// 01. Npc_Citizen1
	pNpc = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen1");
	NULL_CHECK(pNpc);
	vNpcPos = pNpc->Get_Transform()->Get_Info(INFO_POS);
	vNewPos = _vec3{ vPlayerPos.x - 7.f, vNpcPos.y, vPlayerPos.z + 6.f };
	pNpc->Get_Transform()->Set_Pos(vNewPos);

	// 02. Npc_Soldier
	pNpc = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::NPC, L"Npc_Soldier");
	NULL_CHECK(pNpc);
	vNpcPos = pNpc->Get_Transform()->Get_Info(INFO_POS);
	vNewPos = _vec3{ vPlayerPos.x + 7.f, vNpcPos.y, vPlayerPos.z + 6.f };
	pNpc->Get_Transform()->Set_Pos(vNewPos);

	vNpcScale = pNpc->Get_Transform()->Get_Scale();
	pNpc->Get_Transform()->Set_Scale(_vec3{ -vNpcScale.x, vNpcScale.y, vNpcScale.z });

	// 03. Npc_Citizen2
	pNpc = CNpc_Citizen2::Create(m_pGraphicDev);
	NULL_CHECK(pNpc);
	CEventMgr::GetInstance()->Add_Obj(pNpc->Get_Name(), pNpc);
	vNpcPos = pNpc->Get_Transform()->Get_Info(INFO_POS);
	vNewPos = _vec3{ vPlayerPos.x + 10.f, vNpcPos.y, vPlayerPos.z + 3.f };
	pNpc->Get_Transform()->Set_Pos(vNewPos);

	vNpcScale = pNpc->Get_Transform()->Get_Scale();
	pNpc->Get_Transform()->Set_Scale(_vec3{ -vNpcScale.x, vNpcScale.y, vNpcScale.z });

	// 03. Npc_BlackSmith
	pNpc = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith");
	NULL_CHECK(pNpc);
	vNpcPos = pNpc->Get_Transform()->Get_Info(INFO_POS);
	vNewPos = _vec3{ vPlayerPos.x -5.f, vNpcPos.y, vPlayerPos.z + 4.f };
	pNpc->Get_Transform()->Set_Pos(vNewPos);
}



void CBossSceneMgr::Free()
{
}
