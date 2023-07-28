#include "PlayerState_fFlight.h"

#include "Export_Function.h"

#include "CameraMgr.h"

CPlayerState_fFlight::CPlayerState_fFlight(LPDIRECT3DDEVICE9 pGraphicDev)
	: CState(pGraphicDev)
{
}

CPlayerState_fFlight::~CPlayerState_fFlight()
{
}

HRESULT CPlayerState_fFlight::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
		m_pOwner = pOwner;

	m_eState = STATE_TYPE::FRONT_FLIGHT;

	return S_OK;
}

STATE_TYPE CPlayerState_fFlight::Update_State(const _float& fTimeDelta)
{
	if (!m_bEnter)
	{
		CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Hp")->Set_Active(false);
		CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Def")->Set_Active(false);
		CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Mana")->Set_Active(false);

		m_pOwner->Get_OwnerObject()->Get_Transform()->Reset_Lerp();
		m_bIsSky = false;
		m_bIsLand = false;
		m_bEnter = true;
		m_bFlying = true;
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_MoveSpeed(40.f);

		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_IDL_TO_FLY); // << Test
	}
	if(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed <= 40)
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_MoveSpeed(40.f);


	STATE_TYPE eState = m_eState;
	if (!m_bIsSky)
	{
		_vec3 vStart = m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Info(INFO::INFO_POS);
		_vec3 vOut = m_pOwner->Get_OwnerObject()->Get_Transform()->Lerp(vStart, _vec3{ vStart.x, vStart.y + 0.8f, vStart.z }, 1.f, fTimeDelta, LERP_MODE::SMOOTHSTEP);
		if (vOut.x != -99)
		{
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Pos(vOut);
		}
		else
		{
			m_bIsSky = true;
			static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_Fly(true);
		}
			
	}

	if (m_bIsSky && !m_bIsLand)
	{
		/*if (m_bFlying)
		{
			_vec3 vStart = m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Info(INFO::INFO_POS);
			_vec3 vOut = m_pOwner->Get_OwnerObject()->Get_Transform()->Lerp(vStart, _vec3{ vStart.x, vStart.y + 0.1f, vStart.z }, 0.2f, fTimeDelta, LERP_MODE::SMOOTHERSTEP);
			if (vOut.x != -99)
			{
				m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Pos(vOut);
			}
			else
				m_bFlying = false;
		}
		if (!m_bFlying)
		{
			_vec3 vStart = m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Info(INFO::INFO_POS);
			_vec3 vOut = m_pOwner->Get_OwnerObject()->Get_Transform()->Lerp(vStart, _vec3{ vStart.x, vStart.y - 0.1f, vStart.z }, 0.2f, fTimeDelta, LERP_MODE::SMOOTHERSTEP);
			if (vOut.x != -99)
			{
				m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Pos(vOut);
			}
			else
				m_bFlying = true;
		}*/
		
		eState = Key_Input(fTimeDelta);
	}
		
	if (m_bIsLand)
	{
		_vec3 vStart = m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Info(INFO::INFO_POS);
		_vec3 vOut = m_pOwner->Get_OwnerObject()->Get_Transform()->Lerp(vStart, _vec3{ vStart.x, vStart.y - 0.6f, vStart.z }, 1.f, fTimeDelta, LERP_MODE::EASE_OUT);
		if (vOut.x != -99)
		{
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Pos(vOut);
		}
		else
		{
			CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_FLY_TO_IDL); 
			/*CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Lerp_FOV(
				1.f, CAM_FOV_PLAYER_FLIGHT, CAM_FOV_DEFAULT, LERP_MODE::SMOOTHERSTEP);*/
			static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_MoveSpeed(20.f);
			if(CLASS_TYPE::NINJA == static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_PlayerClass())
				static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_MoveSpeed(25.f);
			static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_Fly(false);
			m_bEnter = false;
			return STATE_TYPE::FRONT_IDLE;
		}

	}	

	if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Hit() && !m_bIsLand && m_bIsSky)
	{
		return STATE_TYPE::FRONT_HIT;
	}



	return eState;
}

void CPlayerState_fFlight::LateUpdate_State()
{
}

void CPlayerState_fFlight::Render_State()
{
	//cout << "������ �ռ��ֱ�" << endl;
}

STATE_TYPE CPlayerState_fFlight::Key_Input(const _float& fTimeDelta)
{
	// ���ڲٳ�	
	if (CInputDev::GetInstance()->Key_Down('F'))
	{
		m_bIsLand = true;
		return m_eState;
	}

	if (!m_bIsLand && m_bIsSky &&  CInputDev::GetInstance()->Key_Down(VK_LBUTTON) && static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_PlayerClass() == CLASS_TYPE::MAGE)
	{
		return STATE_TYPE::FRONT_ATTACK1;
	}
		

	if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.left + vec3.back);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
		m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
		return m_eState;
	}
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.right + vec3.back);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
		m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
		return m_eState;
	}
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.left + vec3.forward);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
		m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
		return m_eState;
	}
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.right + vec3.forward);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
		m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
		return m_eState;
	}
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.left);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
		m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
		return m_eState;
	}
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.right);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
		m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
		return m_eState;
	}
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.back);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
		m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
		return m_eState;
	}
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.forward);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
		m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
		return m_eState;
	}
#pragma endregion

		return m_eState;
}

CPlayerState_fFlight* CPlayerState_fFlight::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CPlayerState_fFlight* pInstance = new CPlayerState_fFlight(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Player fFlgiht Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerState_fFlight::Free()
{
	__super::Free();
}
