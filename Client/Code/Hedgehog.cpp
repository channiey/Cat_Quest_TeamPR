#include "Hedgehog.h"
#include "Export_Function.h"
#include "EventMgr.h"

//state
#include "HedgehogState_Patrol.h"
#include "HedgehogState_Chase.h"
#include "HedgehogState_ComeBack.h"
#include "HedgehogState_Attack.h"

#include "Shadow_Monster.h"

CHedgehog::CHedgehog(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonster(pGraphicDev, OBJ_ID::MONSTER_HEDGEHOG)
{
}

CHedgehog::CHedgehog(const CMonster& rhs)
	: CMonster(rhs)
{
}

CHedgehog::~CHedgehog()
{
}

HRESULT CHedgehog::Ready_Object()
{
	__super::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(),E_FAIL);

	// MoveInfo
	m_tMoveInfo.fMoveSpeed  = 3.f;
	m_tMoveInfo.fRotSpeed	= 1.f;

	// Stat Info
	//m_tStatInfo.bDead = false;



	// 원래 이미지 크기
	m_vImageSize.x = 0.73f;  // 100px = 1.f
	m_vImageSize.y = 0.52f;
	m_vImageSize.z = 2.f;   // 고정 값


	// Transform 
	m_pTransformCom->Set_Scale(_vec3{ m_vImageSize.x *2.5f , m_vImageSize.y  * 2.5f, m_vImageSize.z });
	m_pTransformCom->Set_Pos(_vec3{ 70.f, m_pTransformCom->Get_Scale().y, 110.f });
	m_pTransformCom->Set_Dir({ 0.f, 0.f, -1.f });


	m_vOriginPos	= m_pTransformCom->Get_Info(INFO_POS);

	fPatternTime	= 2.f;
	m_fJumpingSpeed = 0.05;

	CEventMgr::GetInstance()->Add_Obj(L"Monster_Bat_Shadow", CShadow_Monster::Create(m_pGraphicDev, this));
	m_fMaxJumpY = m_pTransformCom->Get_Scale().y + 1.f;

#pragma region State Add

	CState* pState;

	// Patrol
	pState = CHedgehogState_Patrol::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::PATROL, pState);

	// Chase
	pState = CHedgehogState_Chase::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::CHASE, pState);


	// ComeBack
	pState = CHedgehogState_ComeBack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::COMEBACK, pState);

	// Attack
	pState = CHedgegohState_Attack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::MONATTACK, pState);

#pragma endregion


	// 상태 세팅 - 상태만 사용 몬스터
	m_pStateMachineCom->Set_State(STATE_TYPE::PATROL);


	return S_OK;
}

_int CHedgehog::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CMonster::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);
	



	// Jumping 

	_vec3		vOwnerPos = m_pTransformCom->Get_Info(INFO_POS);
	_float Y = m_pTransformCom->Get_Scale().y;
	STATE_TYPE eCurType = m_pStateMachineCom->Get_CurState();

	if (eCurType != STATE_TYPE::MONATTACK && eCurType != STATE_TYPE::BACK_MONATTACK)
	{

		if (vOwnerPos.y < Y || vOwnerPos.y >  m_fMaxJumpY)
		{
			m_fJumpingSpeed *= -1;
		}
		m_pTransformCom->Translate(DIR_UP, m_fJumpingSpeed, WORLD);

	}


	return iExit;
}

void CHedgehog::LateUpdate_Object()
{
	
	

	__super::LateUpdate_Object();

}

void CHedgehog::Render_Object()
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

void CHedgehog::OnCollision_Enter(CGameObject* _pColObj)
{
	__super::OnCollision_Enter(_pColObj);
}

void CHedgehog::OnCollision_Stay(CGameObject* _pColObj)
{
	__super::OnCollision_Stay(_pColObj);
}

void CHedgehog::OnCollision_Exit(CGameObject* _pColObj)
{
	__super::OnCollision_Exit(_pColObj);
}

HRESULT CHedgehog::Add_Component()
{
	CComponent*		pComponent = nullptr;

	// AI
	pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);




#pragma region Texture

	pComponent = m_pTextureCom[_uint(STATE_TYPE::PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Hedgehog", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Hedgehog", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


#pragma endregion


	return S_OK;
}





CHedgehog* CHedgehog::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHedgehog* pInstance = new CHedgehog(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Hedgehog Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHedgehog::Free()
{
	__super::Free();
}
