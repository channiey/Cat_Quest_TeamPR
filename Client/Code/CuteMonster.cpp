#include "stdafx.h"
#include "..\Header\CuteMonster.h"

#include "Export_Function.h"

#include "EventMgr.h"

CCuteMonster::CCuteMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonster(pGraphicDev)
{
}

CCuteMonster::CCuteMonster(const CMonster& rhs)
	: CMonster(rhs)
{

}

CCuteMonster::~CCuteMonster()
{
}

static float iZ = 0;
HRESULT CCuteMonster::Ready_Object()
{
	CMonster::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	
	//m_pTransformCom->Set_Scale(_vec3{ 2.f, 2.f, 2.f });
	m_pTransformCom->Set_Scale(_vec3{ 2.f + ((rand() % 10 + 1) * 0.1f), 
										2.f + ((rand() % 10 + 1) * 0.1f), 
										2.f + ((rand() % 10 + 1) * 0.1f) });

	/*iZ += 5.f;
	m_pTransformCom->Set_Pos(_vec3{ _float(VTXCNTX - 30.f), 
		m_pTransformCom->Get_Scale().y, 
		iZ });*/

	m_pTransformCom->Set_Pos(_vec3{ _float(VTXCNTX - 30.f + rand() % 40),
									m_pTransformCom->Get_Scale().y,
									_float(rand() % 70) });
	
	return S_OK;
}

Engine::_int CCuteMonster::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CMonster::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	Move(fTimeDelta);

	return iExit;
}

void CCuteMonster::LateUpdate_Object()
{
	CMonster::LateUpdate_Object();
}

void CCuteMonster::Render_Object()
{
	CMonster::Render_Object();
}

void CCuteMonster::OnCollision_Enter(CGameObject* _pColObj)
{
	/*if (OBJ_TYPE::PLAYER == _pColObj->Get_Type())
	{
		Set_Active(false);
		CEventMgr::GetInstance()->Delete_Obj(this);
	}*/
}

void CCuteMonster::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CCuteMonster::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CCuteMonster::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Monster", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

void CCuteMonster::Move(const _float& fTimeDelta)
{
	m_pTransformCom->Translate(DIR_RIGHT, fTimeDelta * -m_tMoveInfo.fMoveSpeed * 0.1f);
}

void CCuteMonster::Free()
{
	CMonster::Free();
}

CCuteMonster* CCuteMonster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCuteMonster* pInstance = new CCuteMonster(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Monster Create Failed");
		return nullptr;
	}

	return pInstance;
}
