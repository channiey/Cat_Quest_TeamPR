#include "Inventory.h"
#include "Export_Function.h"

CInventory::CInventory(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev, OBJ_ID::UI_INVENTORY)
	, m_bIsOn(false)

{
}

CInventory::CInventory(const CInventory& rhs)
	:CUI(rhs)
{
}

CInventory::~CInventory()
{
}

HRESULT CInventory::Ready_Object()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eUIType = UI_TYPE::VIEW;
	m_eUILayer = UI_LAYER::LV1;

	m_bShirnk = true;






	return S_OK;
}

_int CInventory::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);






	return iExit;
}

void CInventory::LateUpdate_Object()
{

	__super::LateUpdate_Object();


}

void CInventory::Render_Object()
{
}

HRESULT CInventory::Add_Component()
{





	return S_OK;
}

void CInventory::Picking_UI()
{

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	D3DVIEWPORT9 ViewPort;

	m_pGraphicDev->GetViewport(&ViewPort);

	pt.y = WINCY - pt.y;


}

void CInventory::Mouse_Input()
{


}

CInventory* CInventory::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CInventory* pInstance = new CInventory(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Inventory Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CInventory::Free()
{
	__super::Free();
}
