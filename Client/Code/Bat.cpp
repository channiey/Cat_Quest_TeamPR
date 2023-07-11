#include "Bat.h"
#include "Export_Function.h"
#include "EventMgr.h"
#include "TimerMgr.h"

CBat::CBat(LPDIRECT3DDEVICE9 pGraphicDev)
    : CMonster(pGraphicDev)
{
}

CBat::CBat(const CMonster& rhs)
    : CMonster(rhs)
{
}

CBat::~CBat()
{
}

HRESULT CBat::Ready_Object()
{
    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	// MoveInfo
	m_tMoveInfo.fMoveSpeed = 10.f;
	m_tMoveInfo.fRotSpeed = 1.f;

	
	// Transform 
	m_pTransformCom->Set_Scale(_vec3{ 1.6f, 1.08f, 2.f });
	
	m_pTransformCom->Set_Pos(_vec3{ 20.f,
									m_pTransformCom->Get_Scale().y,
									10.f });

	m_vOriginPos = { 20.f, m_pTransformCom->Get_Scale().y, 10.f };


	fPatternTime = 2.f;
	fAccTime	 = 0.f;

    return S_OK;
}

_int CBat::Update_Object(const _float& fTimeDelta)
{

	_int iExit = CMonster::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);
	
	m_pTransformCom->Translate(fTimeDelta * m_tMoveInfo.fMoveSpeed);


	fAccTime += fTimeDelta;

	if(fPatternTime <= fAccTime)
	{
		Move(fTimeDelta);

		fAccTime = 0.f;
	}
	
	return iExit;
}

void CBat::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CBat::Render_Object()
{
	__super::Render_Object();
}

void CBat::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CBat::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CBat::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CBat::Add_Component()
{
	CComponent* pComponent = nullptr;

	//// Texture
	//pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Bat", this));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// AI
	pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);



	return S_OK;
}

void CBat::Move(const _float& fTimeDelta)
{
	
	  m_pAICom->Random_Move(fTimeDelta,m_tMoveInfo.fMoveSpeed);

}

CBat* CBat::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBat* pInstance = new CBat(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Bat Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBat::Free()
{
	__super::Free();
}