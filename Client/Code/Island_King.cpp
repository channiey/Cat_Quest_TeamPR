#include "stdafx.h"
#include "..\Header\Island_King.h"

#include "Export_Function.h"

#include "RangeObj.h"
#include "EffectGenerator.h"

CIsland_King::CIsland_King(LPDIRECT3DDEVICE9 pGraphicDev)
	: CIsland(pGraphicDev, OBJ_ID::ISLAND_RANGE_KING)
{
}
CIsland_King::CIsland_King(const CIsland_King& rhs)
	: CIsland(rhs)
{

}
CIsland_King::~CIsland_King()
{
}

HRESULT CIsland_King::Ready_Object(void)
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	FAILED_CHECK_RETURN(Add_RangeObj(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 220.f, 0.f , 384.f });

	m_szName = L"Island_King";

	return S_OK;
}

Engine::_int CIsland_King::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CIsland_King::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();
}

void CIsland_King::Render_Object(void)
{
	__super::Render_Object();
}

HRESULT CIsland_King::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	return S_OK;
}


HRESULT CIsland_King::Add_RangeObj()
{
	CRangeObj* pGameObject = nullptr;

	// 01
	pGameObject = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Island_King_RangeObj_01", pGameObject);
	pGameObject->Set_Radius(50.f);
	pGameObject->Set_Pos(_vec3{ 560.f, 0.f , 60.f });
	m_vecRangeObj.push_back(pGameObject);

	return S_OK;
}

void CIsland_King::Enter_Player()
{
	// �÷��̾ �ش� ���� ó�� ������ ��

	// Action : ��� �̸� UI, �÷��̾� �̲�����, ��� ����, �� ����Ʈ On
	CEffectGenerator* pGenerator = dynamic_cast<CEffectGenerator*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::GENERATOR, L"Effect_Generator"));
	NULL_CHECK(pGenerator);
	pGenerator->Set_Locate(m_eID);

}

void CIsland_King::Stay_Player()
{
	CEffectGenerator* pGenerator = dynamic_cast<CEffectGenerator*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::GENERATOR, L"Effect_Generator"));
	NULL_CHECK(pGenerator);
	pGenerator->Set_Locate(m_eID);
}

void CIsland_King::Exit_Player()
{
	// �÷��̾ �ش� ������ ������ ��
	CEffectGenerator* pGenerator = dynamic_cast<CEffectGenerator*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::GENERATOR, L"Effect_Generator"));
	NULL_CHECK(pGenerator);
	pGenerator->Set_Locate(OBJ_ID::TYPEEND);
}

void CIsland_King::Free()
{
	__super::Free();
}

CIsland_King* CIsland_King::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CIsland_King* pInstance = new CIsland_King(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Island_King Create Failed");
		return nullptr;
	}

	return pInstance;
}
