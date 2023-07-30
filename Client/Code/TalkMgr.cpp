#include "stdafx.h"
#include "TalkMgr.h"

#include "Export_Function.h"

#include "DialogUI.h"
#include "EventMgr.h"
#include "QuestMgr.h"
#include "SoundMgr.h"

#include "Npc_King.h"
#include "Npc_Mage.h"
#include "Npc_BlackSmith.h"
#include "Npc_Soldier.h"
#include "Npc_Citizen1.h"
#include "Npc_Citizen2.h"

#include "EnterUI.h"

#include "MiniGameMgr_Jump.h"
#include "Player.h"


#define TALK_SOUND 1.f
#define MEOW_SOUND 1.f


IMPLEMENT_SINGLETON(CTalkMgr)


CTalkMgr::CTalkMgr()
	:m_bTargetCam(false), m_bStaySet(false), m_bReturnCam(false), m_bTalkEnd(false), m_iStayTime(0)
{
}

CTalkMgr::~CTalkMgr()
{
}

void CTalkMgr::Init()
{
	m_iTalkIndex = 0;

#pragma region Quest1 : 대장장이의 부탁
	// Quest1 : 대장장이의 부탁
	// 대장장이
	m_mapTalkData.insert(make_pair(100, vector<wstring>{
		{ L"안녕! \n우리 마을에 잘 왔어!"},
		{ L"니가 그 소문의 드래곤 블러드구나! \n니가 온다는 연락은 이미 받았어." },
		{ L"아쉽게도 드래곤에 대한 정보는 \n아직 모으고 있는 중이야."},
		{ L"그동안 저 아래쪽에 있는 고슴도치들을 \n혼내줬으면 좋겠어!"}
		}));
	// 대장장이
	m_mapTalkData.insert(make_pair(101, vector<wstring>{
		{ L"고슴도치들을 혼내줬구나!"},
		{ L"이걸로 녀석들도 이전처럼 활개치진 못 할거야." },
		{ L"고마워! 이건 우리집에 대대로 있던 스킬북이야." },
		{ L"니가 가져가주면 드래곤을 처치하는 데 \n도움이 되겠지!"}
	}));
#pragma endregion
#pragma region Quest2 : 던전 정리
// Quest2 : 던전 정리
// 대장장이
	m_mapTalkData.insert(make_pair(200, vector<wstring>{
		{ L"이제 조금만 더 조사하면 돼!"},
		{ L"그동안 던전에 들어가서 몬스터들을 \n모두 소탕해주지 않을래?"},
		{ L"모두 소탕하면 이미 안에서 조사중인 \n연구원에게 보고해줘."}
	}));

	// 시티즌(2)
	m_mapTalkData.insert(make_pair(201, vector<wstring>{
		{ L"몬스터를 모두 소탕하셨네요!"},
		{ L"그리고 이것들은 이곳에서 사라져버린\n 어떤 고양이의 유품일까요?" },
		{ L"이런게 떨어져 있더라구요." },
		{ L"저보단 당신께 더 도움이 될 거 같으니 \n가져가세요!" }
	}));
	//

#pragma endregion
#pragma region Quest3 : 드래곤에게 향하기 위해서
// Quest3 : 드래곤에게 향하기 위해서
	// 대장장이
	m_mapTalkData.insert(make_pair(300, vector<wstring>{
		{ L"드래곤에 대한 정보를 얻었어!"},
		{ L"드래곤은 죽음의섬에 있고 죽음의 섬에 \n 가기 위해선 날 수 있어야 해!"},
		{ L"얼음섬에 살고 있는 마법사라면 \n비행에 관련된 기술을 알고 있을 것 같아."},
		{ L"얼음섬으로 가는 방법은 북쪽 해안가에 있는 \n경비가 알고 있을거야."},
		{ L"힘내!" }
	}));

	m_mapTalkData.insert(make_pair(301, vector<wstring>{
		{ L"얼음섬에서 날아서 오시는게 여기서도 보이던데!"},
		{ L"역시 너라면 해낼 줄 알았어!" },
		{ L"그리고 니가 얼음섬에 가 있는 동안 \n이런걸 찾았어." },
		{ L"부디 요긴하게 써줘!" }
	}));


	// 군인
	m_mapTalkData.insert(make_pair(310, vector<wstring>{
		{ L"마법사를 만나러 얼음섬에 가신다구요?"},
		{ L"마법사는 얼음섬에 있긴 합니다만.." },
		{ L"보시다시피 정상적인 길은 없고 뛰어서 가셔야 됩니다." },
		{ L"조심해서 다녀오세요!" }
	}));
	// 마법사
	m_mapTalkData.insert(make_pair(320, vector<wstring>{
		{ L"손님이 찾아오다니.. 반갑네."},
		{ L"비행이라면 내게 방법이 있지." },
		{ L"얼음섬 어딘가에 있는 플라잉 오브를 찾아와." },
		{ L"그럼 알려주지." }
	}));
	m_mapTalkData.insert(make_pair(321, vector<wstring>{
		{ L"진짜로 찾아왔군!"},
		{ L"이제 날기 능력을 전수해 줄 수 있겠어." },
	}));
	//

#pragma endregion
#pragma region Quest4 : 죽음의 섬으로
// Quest4 : 죽음의 섬으로
// 대장장이
	m_mapTalkData.insert(make_pair(400, vector<wstring>{
		{ L"드디어 모든 준비가 끝났구나."},
		{ L"이제 죽음의 섬으로 날아가서 \n정찰병을 만나면 될거야."},
		{ L"아마 가는 도중 해상에 있는 \n몬스터들의 방해가 있을거야."},
		{ L"해상 위의 모든 몬스터를 처치하고 \n정찰병에게 가줘!"}
	}));

	// 시티즌(1)
	m_mapTalkData.insert(make_pair(410, vector<wstring>{
		{ L"기다리고 있었습니다."},
		{ L"이 앞에 사악한 드래곤이 있습니다." },
		{ L"건투를 빕니다!"}
	}));
	//

#pragma endregion
#pragma region Quest5 : 엔딩
// Quest5 : 엔딩
	// 대장장이
	m_mapTalkData.insert(make_pair(500, vector<wstring>{
		{ L"드래곤을 물리쳤구나!"},
		{ L"덕분에 마을에 평화가 찾아오겠어!" },
		{ L"(후에 다른 NPC들 대사 추가.)"},
		{ L"정말 고마워! 사자왕께서도 \n기다리고 계실테니 얼른 가봐!" }
	}));

	// 사자왕
	m_mapTalkData.insert(make_pair(510, vector<wstring>{
		{ L"그대가 드래곤을 물리친 드래곤 블러드인가."},
		{ L"덕분에 나라가 평화를 찾을 수 있게 되었구나."},
		{ L"우리는 그대의 활약을 절대 잊지 않을 것이네."},
		{ L"다시 한번 감사를 표하네."}
	}));
	//

#pragma endregion

	m_bInit = true;
}

_bool CTalkMgr::Get_Talk(LPDIRECT3DDEVICE9 pGraphicDev, _int _iTalkID, OBJ_ID _eObjID)
{	
	auto iter = m_mapTalkData.find(_iTalkID);

	if (&iter)
	{
		if (CInputDev::GetInstance()->Key_Down('E')
			&& !CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"ShadeUI"))
		{
			if(m_iTalkIndex != 0)
				CSoundMgr::GetInstance()->PlaySound(L"button_press.wav", CHANNEL_ID::UI_0, TALK_SOUND);
			else 
				CSoundMgr::GetInstance()->PlaySound(L"npc_greet.wav", CHANNEL_ID::UI_1, MEOW_SOUND);

			// 대화 중 움직일 수 없게
			dynamic_cast<CPlayer*>(CManagement::GetInstance()
				->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"))->Set_PlayerTalk(true);

			// 마법사 대화 시작하자마자 카메라 탑뷰로 바꾸기
			// 종료
			if (_iTalkID == 320)
			{
				if (CCameraMgr::GetInstance()->Get_CurCameraAction()
					!= CAMERA_ACTION::PLAYER_BACK_TO_TOP)
				{
					CMiniGameMgr_Jump::GetInstance()->End_MiniGame(); // 미니게임 종료
				}
			}
			// 마지막 대사까지 다 출력했다면
			if (m_iTalkIndex >= iter->second.size())
			{
				m_bTalkEnd = true;
			}
			if(m_iTalkIndex < iter->second.size())
			{
				// 이미 있으면 지워라
				if (CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"))
				{
					CEventMgr::GetInstance()->Delete_Obj
					(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"));
				}
				// 생성
				if (m_iTalkIndex == 0)
				{
					CEventMgr::GetInstance()->Add_Obj(L"DialogUI", CDialogUI::Create(pGraphicDev,
						_eObjID, iter->second[m_iTalkIndex], DIALOG_TYPE::DIALOG_START));
				}
				else
				{
					CEventMgr::GetInstance()->Add_Obj(L"DialogUI", CDialogUI::Create(pGraphicDev,
						_eObjID, iter->second[m_iTalkIndex]));
				}
				++m_iTalkIndex;
			}
		}
	}

	if (m_bTalkEnd)
	{
		if (dynamic_cast<CDialogUI*>(CManagement::GetInstance()->
			Get_GameObject(OBJ_TYPE::UI, L"DialogUI"))->EndLerp_Dialog())
		{
			CEventMgr::GetInstance()->Delete_Obj
			(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"));
		
			// 다시 움직일 수 있게
			dynamic_cast<CPlayer*>(CManagement::GetInstance()
				->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"))->Set_PlayerTalk(false);
			
			m_iTalkIndex = 0;
			m_bTalkEnd = false;
			return true;
		}
	}

	return false;
}

_bool CTalkMgr::Get_CamTalk(LPDIRECT3DDEVICE9 pGraphicDev,
	_int _iTalkID, OBJ_ID _eObjID, _int _EventIndex,
	_vec3 _StartPos, _vec3 _TargetPos)
{
	auto iter = m_mapTalkData.find(_iTalkID);
	
	if (&iter)
	{
		if (CInputDev::GetInstance()->Key_Down('E')
			&& !CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"ShadeUI"))
		{
			if (m_iTalkIndex != 0)
				CSoundMgr::GetInstance()->PlaySound(L"button_press.wav", CHANNEL_ID::UI_0, TALK_SOUND);
			else
				CSoundMgr::GetInstance()->PlaySound(L"npc_greet.wav", CHANNEL_ID::UI_1, MEOW_SOUND);

			// 대화 중 움직일 수 없게
			dynamic_cast<CPlayer*>(CManagement::GetInstance()
				->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"))->Set_PlayerTalk(true);

			// 이벤트 인덱스라면
			if (m_iTalkIndex == _EventIndex)
			{
				m_pCam = dynamic_cast<CPlayer_Camera*>(CCameraMgr::GetInstance()->Get_CurCamera());
				CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::OBJ_CHANGE_TARGET, _StartPos, _TargetPos, TRUE);
				CSoundMgr::GetInstance()->PlaySoundW(L"map_transition.wav", CHANNEL_ID::UI_3, 1.f);

				m_bTargetCam = true;
			}

			// 마지막 대사까지 다 출력했다면
			if (m_iTalkIndex >= iter->second.size())
			{
				m_bTalkEnd = true;
			}
			if (m_iTalkIndex < iter->second.size())
			{
				if (m_iTalkIndex != _EventIndex)
				{
					// 이미 있으면 지워라
					if (CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"))
					{
						CEventMgr::GetInstance()->Delete_Obj
						(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"));
					}
					if (m_iTalkIndex == 0)
					{
						CEventMgr::GetInstance()->Add_Obj(L"DialogUI", CDialogUI::Create(pGraphicDev,
							_eObjID, iter->second[m_iTalkIndex], DIALOG_TYPE::DIALOG_START));
					}
					else
					{
						CEventMgr::GetInstance()->Add_Obj(L"DialogUI", CDialogUI::Create(pGraphicDev,
							_eObjID, iter->second[m_iTalkIndex]));
					}
					++m_iTalkIndex;
				}
			}
		}

		// 카메라 이벤트 시작
		if (m_bTargetCam)
		{
			if (nullptr != m_pCam)
			{
				if (!m_bStaySet)
				{
					// 카메라 이벤트 끝났으면
					if (!m_pCam->Is_LerpTargetChange())
					{
						m_iStayTime = GetTickCount64() + 1700;
						m_bStaySet = true;
					}
				}
				else
				{
					if (GetTickCount64() > m_iStayTime)
					{
						// 대기 시간 끝났으면 다시 돌아가는 카메라 이벤트 실행.
						if (!m_bReturnCam)
						{
							CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::OBJ_CHANGE_TARGET, _TargetPos, _StartPos, FALSE);
							m_pCam = dynamic_cast<CPlayer_Camera*>(CCameraMgr::GetInstance()->Get_CurCamera());
							CSoundMgr::GetInstance()->PlaySoundW(L"map_transition.wav", CHANNEL_ID::UI_3, 1.f);

							m_bReturnCam = true; 
						}
					}
				}

				if (m_bReturnCam && !m_pCam->Is_LerpTargetChange())
				{
					// 이미 있으면 지워라
					if (CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"))
					{
						CEventMgr::GetInstance()->Delete_Obj
						(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"));
					}
					// 생성
					CEventMgr::GetInstance()->Add_Obj(L"DialogUI", CDialogUI::Create(pGraphicDev,
						_eObjID, iter->second[m_iTalkIndex]));
					++m_iTalkIndex;
					m_bReturnCam = false;
					m_bTargetCam = false;
				}
			}
		}

		if (m_bTalkEnd)
		{
			if (dynamic_cast<CDialogUI*>(CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::UI, L"DialogUI"))->EndLerp_Dialog())
			{
				CEventMgr::GetInstance()->Delete_Obj
				(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"));
				
				// 움직일 수 있게 다시
				dynamic_cast<CPlayer*>(CManagement::GetInstance()
					->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"))->Set_PlayerTalk(false);
				
				m_iTalkIndex = 0;
				m_iStayTime = 0;
				m_bTargetCam = false;
				m_bStaySet = false;
				m_bReturnCam = false;
				m_bTalkEnd = false;
				return true;
			}
		}
	}


	return false;




}

void CTalkMgr::Free()
{
}
