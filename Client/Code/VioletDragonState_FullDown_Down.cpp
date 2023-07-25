#include "VioletDragonState_FullDown_Down.h"
#include "Export_Function.h"
#include "Monster.h"
#include "Player.h"

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
	// Monster - Ai Com
	CComponent* pOwnerAI = dynamic_cast<CAIComponent*>(m_pOwner->Get_OwnerObject()->Get_Component(COMPONENT_TYPE::AICOM, COMPONENTID::ID_DYNAMIC));
	NULL_CHECK_MSG(pOwnerAI, L"pOwnerAI nullptr");

	// Monster - Transform Com
	CTransform* pOwnerTransform = m_pOwner->Get_OwnerObject()->Get_Transform();
	NULL_CHECK_MSG(pOwnerTransform, L"pOwnerTransform nullptr");
	
	//Monster - Animator
	CComponent* pOwnerAnimator = dynamic_cast<CAnimator*>(m_pOwner->Get_OwnerObject()->Get_Component(COMPONENT_TYPE::ANIMATOR, COMPONENTID::ID_STATIC));
	NULL_CHECK_MSG(pOwnerAnimator, L"pOwnerAnimator nullptr");

	// Monster - Cur Animation info
	CAnimation* pOwenrCurAnimation = dynamic_cast<CAnimator*>(pOwnerAnimator)->Get_CurAniamtion();
	NULL_CHECK_MSG(pOwenrCurAnimation, L"pOwnerCurAnimation nullptr");



	// Player
	CGameObject* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));
	NULL_CHECK_MSG(pPlayer, L"pPlayer nullptr");

	// Player - Transform Com
	CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
	NULL_CHECK_MSG(pPlayerTransform, L"pPlayerTransform nullptr");

	// Monster - Pos
	_vec3       vOwnerPos = pOwnerTransform->Get_Info(INFO_POS);
	NULL_CHECK_MSG(vOwnerPos, L"vOwnerPos nullptr");

	// Mosnter - Origin Pos
	_vec3       vOwnerOriginPos = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_OriginPos();
	NULL_CHECK_MSG(vOwnerOriginPos, L"vOwnerOriginPos nullptr");

	// Monster - Speed
	_float      vOwnerSpeed = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed;
	NULL_CHECK_MSG(vOwnerSpeed, L"vOwnerSpeed nullptr");

	// Monster - PatternTime
	_float      vOwnerPatternTime = dynamic_cast<CMonster*>(m_pOwner->Get_OwnerObject())->Get_PatternTime();
	NULL_CHECK_MSG(vOwnerPatternTime, L"vOwnerPatternTime nullptr");

	// Monster - Scale
	_vec3 vOwnerScale = pOwnerTransform->Get_Scale();
	NULL_CHECK_MSG(vOwnerScale, L"vOwnerScale nullptr");

	// Monster - Dir
	_vec3 vOwnerDir = pOwnerTransform->Get_Dir();
	NULL_CHECK_MSG(vOwnerDir, L"vOwnerDir nullptr");

	// Player - Pos
	_vec3       vPlayerPos;
	vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);
	NULL_CHECK_MSG(pPlayerTransform, L"pPlayerTransform nullptr");

	// Time
	m_fAccTime += fTimeDelta;



	if (pOwenrCurAnimation->Is_End())
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
		return STATE_TYPE::BOSS_CONVERGING_FIRE;
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
