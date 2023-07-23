#include "VioletDragonState_FullDown_Down.h"
#include "Export_Function.h"
#include "Monster.h"

CVioletDragonState_FullDown_Down::CVioletDragonState_FullDown_Down(LPDIRECT3DDEVICE9 pGraphicDev)
	:CState(pGraphicDev)
	, m_fAccTime(0.f)
{
}

CVioletDragonState_FullDown_Down::~CVioletDragonState_FullDown_Down()
{
}


HRESULT CVioletDragonState_FullDown_Down::Ready_State(CStateMachine* pOwner)
{

	if (nullptr != pOwner)
	{
		m_pOwner = pOwner;
	}
	m_eState = STATE_TYPE::BOSS_FULLDOWN_DOWN;

	m_fAccTime = 0.f;

	return S_OK;
}

STATE_TYPE CVioletDragonState_FullDown_Down::Update_State(const _float& fTimeDelta)
{
	// Monster - Animation Com
	CAnimation* pOwnerCurAnimation = m_pOwner->Get_Animator()->Get_CurAniamtion();


	// Monster - Transform Com
	CTransform* pOwnerTransform = m_pOwner->Get_OwnerObject()->Get_Transform();

	// Monster - Speed
	_float      vOwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;

	// Time
	m_fAccTime += fTimeDelta;



	if (pOwnerCurAnimation->Is_End())
	{
		//CCameraMgr::GetInstance()->Shake_Camera(0.15, 40);  // 사람들을 위해서 카메라 쉐이킹 주석처리

		if (m_fAccTime >= 1.f)
		{
			CCameraMgr::GetInstance()->Stop_Shake();
		}
	}


	// 임시로 전이 반복 시킴 
	// State Change 

	if (m_fAccTime >= 5.f)
	{
		m_fAccTime = 0.f;
		return STATE_TYPE::BOSS_FULLDOWN_FLY;
	}


	return STATE_TYPE::BOSS_FULLDOWN_DOWN;
}

void CVioletDragonState_FullDown_Down::LateUpdate_State()
{
}

void CVioletDragonState_FullDown_Down::Render_State()
{
}

STATE_TYPE CVioletDragonState_FullDown_Down::Key_Input(const _float& fTimeDelta)
{

	return m_eState;
}

CVioletDragonState_FullDown_Down* CVioletDragonState_FullDown_Down::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CVioletDragonState_FullDown_Down* pInstance = new CVioletDragonState_FullDown_Down(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("VioletDragonState Down Create Failed");
		return nullptr;

	}
	return pInstance;

}

void CVioletDragonState_FullDown_Down::Free()
{

	__super::Free();
}
