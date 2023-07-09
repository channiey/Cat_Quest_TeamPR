#include "Hedgehog.h"
#include "Export_Function.h"
#include "EventMgr.h"

CHedgehog::CHedgehog(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonster(pGraphicDev)
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
	m_tMoveInfo.fMoveSpeed = 5.f;
	m_tMoveInfo.fRotSpeed = 1.f;

	// Stat Info
	//m_tStatInfo.bDead = false;


	// Transform 
	m_pTransformCom->Set_Scale(_vec3{ 1.46f, 1.04f, 2.f });
	//m_pTransformCom->Set_Pos(_vec3{ 300.f, m_pTransformCom->Get_Scale().y, 300.f });

	m_pTransformCom->Set_Pos(_vec3{ _float(VTXCNTX - 30.f + rand() % 40),
									m_pTransformCom->Get_Scale().y,
									_float(rand() % 70) });


	return S_OK;
}

_int CHedgehog::Update_Object(const _float& fTimeDelta)
{

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	Move(fTimeDelta);


	_int iExit = CMonster::Update_Object(fTimeDelta);
	return iExit;
}

void CHedgehog::LateUpdate_Object()
{
	__super::LateUpdate_Object();

}

void CHedgehog::Render_Object()
{
	__super::Render_Object();

}

void CHedgehog::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CHedgehog::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CHedgehog::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CHedgehog::Add_Component()
{
	CComponent*		pComponent = nullptr;

	// Texture
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Hedgehog", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// AI
	pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);




	return S_OK;
}

void CHedgehog::Move(const _float& fTimeDelta)
{

	// 플레이어 위치 가져오기
	CTransform * pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
	NULL_CHECK(pPlayerTransform);

	_vec3	vPlayerPos;
	vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);

	_vec3	vOwnerPos;
	vOwnerPos = m_pTransformCom->Get_Info(INFO_POS);
	
	_vec3		vLook;
	vLook = vOwnerPos - vPlayerPos;
	// _float fDistance = D3DXVec3Length(&vLook);

	m_pAICom->Chase_Target(&vPlayerPos, fTimeDelta, m_tMoveInfo.fMoveSpeed);


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
