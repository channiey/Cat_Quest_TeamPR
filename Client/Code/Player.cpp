#include "stdafx.h"
#include "..\Header\Player.h"

#include "Export_Function.h"

#include "CubeCol.h"
#include "PlayerState_fWalk.h"
#include "PlayerState_fIdle.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::PLAYER)
{
}

CPlayer::CPlayer(const CPlayer& rhs)
	: Engine::CGameObject(rhs)
	, m_tMoveInfo(rhs.m_tMoveInfo)
	, m_tStatInfo(rhs.m_tStatInfo)
{

}

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Ready_Object()
{
	CGameObject::Ready_Object();
	
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 2.f, 2.f, 2.f });
	m_pTransformCom->Set_Pos(_vec3{ VTXCNTX / 2.f, m_pTransformCom->Get_Scale().y, 10.f });

	// 앞 걷기상태 추가
	CState* pState = CPlayerState_fWalk::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::WALK, pState);
	// 앞 서기상태 추가
	pState = CPlayerState_fIdle::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::IDLE, pState);
	// 앞 걷기애니메이션 추가
	CAnimation* pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::WALK)], STATE_TYPE::WALK, 0.12f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::WALK, pAnimation);
	// 앞 서기애니메이션 추가
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::IDLE)], STATE_TYPE::IDLE, 0.2f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::IDLE, pAnimation);

	m_pStateMachineCom->Set_Animator(m_pAnimatorCom);
	m_pStateMachineCom->Set_State(STATE_TYPE::IDLE);


	// Camera Setting
	if (PLAY_MODE::TOOL != CManagement::GetInstance()->Get_PlayMode())
	{
		CCameraMgr::GetInstance()->Set_Follow(this);
		CCameraMgr::GetInstance()->Set_LookAt(this);
	}

	return S_OK;
}

Engine::_int CPlayer::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	m_pStateMachineCom->Update_StateMachine(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);
	
	//Key_Input(fTimeDelta);

	return iExit;
}

void CPlayer::LateUpdate_Object()
{
	m_pStateMachineCom->LateUpdate_StateMachine();

	__super::LateUpdate_Object();
}

void CPlayer::Render_Object()
{	
	//m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!
	

	if(m_pColliderCom->Is_Collision())
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.green));
	else
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat()); 
	
	m_pStateMachineCom->Render_StateMachine();
	m_pBufferCom->Render_Buffer();						

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
}

HRESULT CPlayer::Add_Component()
{
	CComponent*		pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::IDLE)]= dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fIdle", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::WALK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fWalk", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pStateMachineCom = dynamic_cast<CStateMachine*>(Engine::Clone_Proto(COMPONENT_TYPE::STATEMACHINE, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::STATEMACHINE, pComponent);

	pComponent = m_pAnimatorCom = dynamic_cast<CAnimator*>(Engine::Clone_Proto(COMPONENT_TYPE::ANIMATOR, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::ANIMATOR, pComponent);

	return S_OK;
}

void CPlayer::Key_Input(const _float& fTimeDelta)
{
	if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
		m_pTransformCom->Translate(vec3.forward + vec3.right, fTimeDelta * m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
		m_pTransformCom->Translate(vec3.forward + -vec3.right, fTimeDelta * m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
		m_pTransformCom->Translate(-vec3.forward + vec3.right, fTimeDelta * m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
		m_pTransformCom->Translate(-vec3.forward - vec3.right, fTimeDelta * m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
		m_pTransformCom->Translate(DIR_FORWARD	, fTimeDelta *	 m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
		m_pTransformCom->Translate(DIR_FORWARD	, fTimeDelta *	-m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
		m_pTransformCom->Translate(DIR_RIGHT	, fTimeDelta *	 m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
		m_pTransformCom->Translate(DIR_RIGHT	, fTimeDelta *	-m_tMoveInfo.fMoveSpeed);
}

void CPlayer::Free()
{
	__super::Free();
}

CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayer*	pInstance = new CPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Player Create Failed");
		return nullptr;
	}

	return pInstance;
}
