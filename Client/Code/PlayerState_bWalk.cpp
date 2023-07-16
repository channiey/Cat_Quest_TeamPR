#include "PlayerState_bWalk.h"

#include "Export_Function.h"

#include "MoveDust.h"
#include "MoveWater.h"
CPlayerState_bWalk::CPlayerState_bWalk(LPDIRECT3DDEVICE9 pGraphicDev)
	: CState(pGraphicDev)
{
}

CPlayerState_bWalk::~CPlayerState_bWalk()
{
}

HRESULT CPlayerState_bWalk::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
		m_pOwner = pOwner;

	m_eState = STATE_TYPE::BACK_WALK;

	return S_OK;
}

STATE_TYPE CPlayerState_bWalk::Update_State(const _float& fTimeDelta)
{
    if (!m_bEnter)
    {
        m_bEnter = true;
    }

	STATE_TYPE eState = Key_Input(fTimeDelta);

    if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Hit())
        eState = STATE_TYPE::FRONT_HIT;

    if (eState != m_eState)
        m_bEnter = false;
	return eState;
}

void CPlayerState_bWalk::LateUpdate_State()
{
}

void CPlayerState_bWalk::Render_State()
{
	//cout << "지금은 뒤걷기" << endl;
}

STATE_TYPE CPlayerState_bWalk::Key_Input(const _float& fTimeDelta)
{
    if (CInputDev::GetInstance()->Key_Down(VK_LBUTTON))
        return STATE_TYPE::BACK_ATTACK;

    if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_SPACE)) {
        CGameObject* p = CMoveDust::Create(m_pGraphicDev, m_pOwner->Get_OwnerObject());
        CEventMgr::GetInstance()->Add_Obj(L"MoveDust", p);
        return STATE_TYPE::BACK_ROLL;
    }

    if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Scale(_vec3{ 3.f, 3.f, 3.f });
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.forward + vec3.right);
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
       
        if (CInputDev::GetInstance()->Key_Down('D') &&
            !CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::EFFECT, L"MoveDust")) {
            CGameObject* p = CMoveDust::Create(m_pGraphicDev, m_pOwner->Get_OwnerObject());
            CEventMgr::GetInstance()->Add_Obj(L"MoveDustL", p);
        }

        return m_eState;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Scale(_vec3{ -3.f, 3.f, 3.f });
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.forward + vec3.left);
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
        
        if (CInputDev::GetInstance()->Key_Down('D') &&
            !CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::EFFECT, L"MoveDust")) {
            CGameObject* p = CMoveDust::Create(m_pGraphicDev, m_pOwner->Get_OwnerObject());
            CEventMgr::GetInstance()->Add_Obj(L"MoveDustR", p);
        }

        return m_eState;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
    {
        CGameObject* p = CMoveDust::Create(m_pGraphicDev, m_pOwner->Get_OwnerObject());
        CEventMgr::GetInstance()->Add_Obj(L"MoveDust", p);
        return STATE_TYPE::FRONT_WALK;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
    {
        CGameObject* p = CMoveDust::Create(m_pGraphicDev, m_pOwner->Get_OwnerObject());
        CEventMgr::GetInstance()->Add_Obj(L"MoveDust", p);
        return STATE_TYPE::FRONT_WALK;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
    {
        m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.forward);
        m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
        return m_eState;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
    {
        CGameObject* p = CMoveDust::Create(m_pGraphicDev, m_pOwner->Get_OwnerObject());
        CEventMgr::GetInstance()->Add_Obj(L"MoveDust", p);
        return STATE_TYPE::FRONT_WALK;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
    {
        CGameObject* p = CMoveDust::Create(m_pGraphicDev, m_pOwner->Get_OwnerObject());
        CEventMgr::GetInstance()->Add_Obj(L"MoveDust", p);
        return STATE_TYPE::FRONT_WALK;
    }
    else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
    {
        CGameObject* p = CMoveDust::Create(m_pGraphicDev, m_pOwner->Get_OwnerObject());
        CEventMgr::GetInstance()->Add_Obj(L"MoveDust", p);
        return STATE_TYPE::FRONT_WALK;
    }

    return STATE_TYPE::BACK_IDLE;
}

CPlayerState_bWalk* CPlayerState_bWalk::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CPlayerState_bWalk* pInstance = new CPlayerState_bWalk(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Player bWalkState Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerState_bWalk::Free()
{
	__super::Free();
}
