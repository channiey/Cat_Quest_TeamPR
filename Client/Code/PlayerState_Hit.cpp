#include "PlayerState_Hit.h"

#include "Export_Function.h"

CPlayerState_Hit::CPlayerState_Hit(LPDIRECT3DDEVICE9 pGraphicDev)
	: CState(pGraphicDev)
{
}

CPlayerState_Hit::~CPlayerState_Hit()
{
}

HRESULT CPlayerState_Hit::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
		m_pOwner = pOwner;

	m_eState = STATE_TYPE::FRONT_HIT;
	m_fAcc = 0.f;

	return S_OK;
}

STATE_TYPE CPlayerState_Hit::Update_State(const _float& fTimeDelta)
{
	if (!m_bEnter)
	{
		m_bEnter = true;
        m_fAcc = 0.f;
	}

	STATE_TYPE eState = Key_Input(fTimeDelta);
    
    m_fAcc += fTimeDelta;
    if (m_fAcc > 0.3)
    {
        m_fAcc = 0.f;
        static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_HIt(false);
        m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
        eState = STATE_TYPE::FRONT_IDLE;
    }


	if (eState != m_eState)
		m_bEnter = false;
	return eState;
}

void CPlayerState_Hit::LateUpdate_State()
{
}

void CPlayerState_Hit::Render_State()
{
  
}

STATE_TYPE CPlayerState_Hit::Key_Input(const _float& fTimeDelta)
{
    if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Scale(_vec3{ 3.f, 3.f, 3.f });
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.forward + vec3.right);
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Scale(_vec3{ -3.f, 3.f, 3.f });
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.forward + vec3.left);
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Scale(_vec3{ 3.f, 3.f, 3.f });
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.back + vec3.right);
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
        return m_eState;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Scale(_vec3{ -3.f, 3.f, 3.f });
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.back + vec3.left);
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
        return m_eState;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.forward);
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
        return m_eState;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.back);
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);

        return m_eState;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Scale(_vec3{ 3.f, 3.f, 3.f });
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.right);
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
        return m_eState;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Scale(_vec3{ -3.f, 3.f, 3.f });
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.left);
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
        return m_eState;
    }


    return m_eState;
}

CPlayerState_Hit* CPlayerState_Hit::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CPlayerState_Hit* pInstance = new CPlayerState_Hit(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Player HitState Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerState_Hit::Free()
{
	__super::Free();
}
