#include "Squirrel.h"
#include "Export_Function.h"
#include "EventMgr.h"

#include "SquirrelState_Patrol.h"
#include "SquirrelState_Chase.h"
#include "SquirrelState_ComeBack.h"
#include "SquirrelState_Attack.h"

CSquirrel::CSquirrel(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonster(pGraphicDev)
{
}

CSquirrel::CSquirrel(const CMonster& rhs)
	: CMonster(rhs)
{
}

CSquirrel::~CSquirrel()
{
}

HRESULT CSquirrel::Ready_Object()
{
	__super::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(),E_FAIL);

	// MoveInfo
	m_tMoveInfo.fMoveSpeed = 3.f;
	m_tMoveInfo.fRotSpeed = 1.f;

	// Stat Info
	//m_tStatInfo.bDead = false;


	// Transform 
	m_pTransformCom->Set_Scale(_vec3{ 0.5f * 2.5f, 0.52f * 2.5f , 1.f });


	m_pTransformCom->Set_Pos(_vec3{ 170.f, m_pTransformCom->Get_Scale().y, 110.f });

	m_pTransformCom->Set_Dir({ 1.38f, 0.f, 1.46f });

	m_vOriginPos = m_pTransformCom->Get_Info(INFO_POS);

	fPatternTime = 2.f;

	m_fJumpingSpeed = 0.05;

#pragma region State Add

	CState* pState;

	// Patrol
	pState = CSquirrelState_Patrol::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::PATROL, pState);

	// Chase
	pState = CSquirrelState_Chase::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::CHASE, pState);


	// ComeBack
	pState = CSquirrelState_ComeBack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::COMEBACK, pState);

	// Attack
	pState = CSquirrelState_Attack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::MONATTACK, pState);

#pragma endregion

	// 상태 세팅 - 상태만 사용 몬스터
	m_pStateMachineCom->Set_State(STATE_TYPE::PATROL);


	return S_OK;
}

_int CSquirrel::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CMonster::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this); 



	// Jumping 

	_vec3		vOwnerPos = m_pTransformCom->Get_Info(INFO_POS);
	float Y = m_pTransformCom->Get_Scale().y;
	STATE_TYPE eCurType = m_pStateMachineCom->Get_CurState();

	if (eCurType != STATE_TYPE::MONATTACK && eCurType != STATE_TYPE::BACK_MONATTACK)
	{

		if (vOwnerPos.y < Y || vOwnerPos.y > Y + 1.f)
		{
			m_fJumpingSpeed *= -1;
		}
		m_pTransformCom->Translate(DIR_UP, m_fJumpingSpeed, WORLD);

	}
	

	
	return iExit;
}

void CSquirrel::LateUpdate_Object()
{
	
	__super::LateUpdate_Object();

}

void CSquirrel::Render_Object()
{
	// 애니메이터 사용 x
	_vec3 Dir = m_pTransformCom->Get_Dir();

	//cout << Dir.z << endl;

	if (m_pTransformCom->Get_Dir().z <= 0)
	{
		m_pTextureCom[(_uint)STATE_TYPE::PATROL]->Render_Texture();
	}
	else
		m_pTextureCom[(_uint)STATE_TYPE::BACK_PATROL]->Render_Texture();

	
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	
	m_pBufferCom->Render_Buffer();
	
	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	
	// monster class보다 상위에서 바로 가져옴
	CGameObject::Render_Object(); // 콜라이더 출력

}

void CSquirrel::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CSquirrel::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CSquirrel::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CSquirrel::Add_Component()
{
	CComponent*		pComponent = nullptr;

	// AI
	pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);


	


#pragma region Texture

	pComponent = m_pTextureCom[_uint(STATE_TYPE::PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Squirrel", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Squirrel", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


#pragma endregion


	return S_OK;
}




CSquirrel* CSquirrel::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSquirrel* pInstance = new CSquirrel(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Squirrel Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSquirrel::Free()
{
	__super::Free();
}
