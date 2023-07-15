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



	// Inven World init
	for (_uint i = 0; i < INVENTORYID_END; ++i)
	{
		D3DXMatrixIdentity(&m_matInventoryWolrd[i]);
	}
	

	// BkG setting
	m_fPosX = WINCX >> 1;
	m_fPosY = WINCY >> 1;
	m_fSizeX = WINCX;
	m_fSizeY = WINCY;
	m_matInventoryWolrd[INVEN_BKG]._11 = m_fSizeX;
	m_matInventoryWolrd[INVEN_BKG]._22 = m_fSizeY;
	m_matInventoryWolrd[INVEN_BKG]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_BKG]._42 = m_fPosY;


	// Button Cancel Button
	m_fPosX = 80.f;
	m_fPosY = 80.f;
	m_fSizeX = 80.f;
	m_fSizeY = 85.f;
	m_fMultipleSizeX = 0.5f;
	m_fMultipleSizeY = 0.5f;
	m_matInventoryWolrd[INVEN_CANCELBUTTON]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_CANCELBUTTON]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_CANCELBUTTON]._11 = m_fSizeX  * m_fMultipleSizeX ;
	m_matInventoryWolrd[INVEN_CANCELBUTTON]._22 = m_fSizeY  * m_fMultipleSizeY ;


	// Tab Button  - Armor
	m_fPosX = 670.f;
	m_fPosY = 100.f;
	m_fSizeX = 176.f;
	m_fSizeY = 128.f;
	m_fMultipleSizeX = 0.38f;
	m_fMultipleSizeY = 0.28f;
	m_matInventoryWolrd[INVEN_ATABBUTTON]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_ATABBUTTON]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_ATABBUTTON]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_ATABBUTTON]._22 = m_fSizeY * m_fMultipleSizeY;


	// Tab Button Image - Armor Texture
	m_fPosX = 670.f;
	m_fPosY = 105.f;
	m_fSizeX = 88.f;
	m_fSizeY = 99.f;
	m_fMultipleSizeX = 0.25f;
	m_fMultipleSizeY = 0.25f;
	m_matInventoryWolrd[INVEN_ARMORTEX]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_ARMORTEX]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_ARMORTEX]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_ARMORTEX]._22 = m_fSizeY * m_fMultipleSizeY;




	// Tab Button - Skill   
	m_fPosX = 825.f;
	m_fPosY = 100.f;
	m_fSizeX = 176.f;
	m_fSizeY = 128.f;
	m_fMultipleSizeX = 0.38f;
	m_fMultipleSizeY = 0.28f;
	m_matInventoryWolrd[INVEN_STABBUTTON]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_STABBUTTON]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_STABBUTTON]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_STABBUTTON]._22 = m_fSizeY * m_fMultipleSizeY;



	// Tab Button Image - Skill Texture
	m_fPosX = 825.f;
	m_fPosY = 105.f;
	m_fSizeX = 92.f;
	m_fSizeY = 96.f;
	m_fMultipleSizeX = 0.25f;
	m_fMultipleSizeY = 0.25f;
	m_matInventoryWolrd[INVEN_SKILLTEX]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_SKILLTEX]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_SKILLTEX]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_SKILLTEX]._22 = m_fSizeY * m_fMultipleSizeY;


	// Tab Line 
	m_fPosX = 825.f;
	m_fPosY = 135.84f;
	m_fSizeX = 4.f;
	m_fSizeY = 4.f;
	m_fMultipleSizeX = 80.f;
	m_fMultipleSizeY = 0.25f;
	m_matInventoryWolrd[INVEN_TABLINE]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_TABLINE]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_TABLINE]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_TABLINE]._22 = m_fSizeY * m_fMultipleSizeY;


	// Button 1
	m_fPosX = 620.f;
	m_fPosY = 220.f;
	m_fSizeX = 175.f;
	m_fSizeY = 175.f;
	m_fMultipleSizeX = 0.3f;
	m_fMultipleSizeY = 0.3f;
	m_matInventoryWolrd[INVEN_BUTTON1]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_BUTTON1]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_BUTTON1]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_BUTTON1]._22 = m_fSizeY * m_fMultipleSizeY;
	
	// Button 2    
	m_fPosX = 755.f;
	m_fPosY = 220.f;
	m_fSizeX = 175.f;
	m_fSizeY = 175.f;
	m_fMultipleSizeX = 0.3f;
	m_fMultipleSizeY = 0.3f;
	m_matInventoryWolrd[INVEN_BUTTON2]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_BUTTON2]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_BUTTON2]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_BUTTON2]._22 = m_fSizeY * m_fMultipleSizeY;


	// Button 3
	m_fPosX = 890.f;
	m_fPosY = 220.f;
	m_fSizeX = 175.f;
	m_fSizeY = 175.f;
	m_fMultipleSizeX = 0.3f;
	m_fMultipleSizeY = 0.3f;
	m_matInventoryWolrd[INVEN_BUTTON3]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_BUTTON3]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_BUTTON3]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_BUTTON3]._22 = m_fSizeY * m_fMultipleSizeY;

	// Button 4
	m_fPosX = 1025.f;
	m_fPosY = 220.f;
	m_fSizeX = 175.f;
	m_fSizeY = 175.f;
	m_fMultipleSizeX = 0.3f;
	m_fMultipleSizeY = 0.3f;
	m_matInventoryWolrd[INVEN_BUTTON4]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_BUTTON4]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_BUTTON4]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_BUTTON4]._22 = m_fSizeY * m_fMultipleSizeY;


	// Button 5
	m_fPosX = 620.f;
	m_fPosY = 343.f;
	m_fSizeX = 175.f;
	m_fSizeY = 175.f;
	m_fMultipleSizeX = 0.3f;
	m_fMultipleSizeY = 0.3f;
	m_matInventoryWolrd[INVEN_BUTTON5]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_BUTTON5]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_BUTTON5]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_BUTTON5]._22 = m_fSizeY * m_fMultipleSizeY;


	// Button 6
	m_fPosX = 755.f;
	m_fPosY = 343.f;
	m_fSizeX = 175.f;
	m_fSizeY = 175.f;
	m_fMultipleSizeX = 0.3f;
	m_fMultipleSizeY = 0.3f;
	m_matInventoryWolrd[INVEN_BUTTON6]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_BUTTON6]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_BUTTON6]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_BUTTON6]._22 = m_fSizeY * m_fMultipleSizeY;



	// Button 7
	m_fPosX = 890.f;
	m_fPosY = 343.f;
	m_fSizeX = 175.f;
	m_fSizeY = 175.f;
	m_fMultipleSizeX = 0.3f;
	m_fMultipleSizeY = 0.3f;
	m_matInventoryWolrd[INVEN_BUTTON7]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_BUTTON7]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_BUTTON7]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_BUTTON7]._22 = m_fSizeY * m_fMultipleSizeY;



	// Button 8
	m_fPosX = 1025.f;
	m_fPosY = 343.f;
	m_fSizeX = 175.f;
	m_fSizeY = 175.f;
	m_fMultipleSizeX = 0.3f;
	m_fMultipleSizeY = 0.3f;
	m_matInventoryWolrd[INVEN_BUTTON8]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_BUTTON8]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_BUTTON8]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_BUTTON8]._22 = m_fSizeY * m_fMultipleSizeY;



	// Button 9
	m_fPosX = 620.f;
	m_fPosY = 466.f;
	m_fSizeX = 175.f;
	m_fSizeY = 175.f;
	m_fMultipleSizeX = 0.3f;
	m_fMultipleSizeY = 0.3f;
	m_matInventoryWolrd[INVEN_BUTTON9]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_BUTTON9]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_BUTTON9]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_BUTTON9]._22 = m_fSizeY * m_fMultipleSizeY;



	// Button 10
	m_fPosX = 755.f;
	m_fPosY = 466.f;
	m_fSizeX = 175.f;
	m_fSizeY = 175.f;
	m_fMultipleSizeX = 0.3f;
	m_fMultipleSizeY = 0.3f;
	m_matInventoryWolrd[INVEN_BUTTON10]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_BUTTON10]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_BUTTON10]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_BUTTON10]._22 = m_fSizeY * m_fMultipleSizeY;


	// Button 11
	m_fPosX = 890.f;
	m_fPosY = 466.f;
	m_fSizeX = 175.f;
	m_fSizeY = 175.f;
	m_fMultipleSizeX = 0.3f;
	m_fMultipleSizeY = 0.3f;
	m_matInventoryWolrd[INVEN_BUTTON11]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_BUTTON11]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_BUTTON11]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_BUTTON11]._22 = m_fSizeY * m_fMultipleSizeY;


	// Button 12
	m_fPosX = 1025.f;
	m_fPosY = 466.f;
	m_fSizeX = 175.f;
	m_fSizeY = 175.f;
	m_fMultipleSizeX = 0.3f;
	m_fMultipleSizeY = 0.3f;
	m_matInventoryWolrd[INVEN_BUTTON12]._41 = m_fPosX;
	m_matInventoryWolrd[INVEN_BUTTON12]._42 = WINCY - m_fPosY;
	m_matInventoryWolrd[INVEN_BUTTON12]._11 = m_fSizeX * m_fMultipleSizeX;
	m_matInventoryWolrd[INVEN_BUTTON12]._22 = m_fSizeY * m_fMultipleSizeY;

	// Inven Sort Button
	//m_fPosX = 520.f;
	//m_fPosY = 220.f;
	//m_fSizeX = 175.f;
	//m_fSizeY = 175.f;
	//m_fMultipleSizeX = 0.3f;
	//m_fMultipleSizeY = 0.3f;
	//m_matInventoryWolrd[INVEN_SORTBUTTON]._41 = m_fPosX;
	//m_matInventoryWolrd[INVEN_SORTBUTTON]._42 = WINCY - m_fPosY;
	//m_matInventoryWolrd[INVEN_SORTBUTTON]._11 = m_fSizeX * m_fMultipleSizeX;
	//m_matInventoryWolrd[INVEN_SORTBUTTON]._22 = m_fSizeY * m_fMultipleSizeY;


	return S_OK;
}

_int CInventory::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Key_Input();


	return iExit;
}

void CInventory::LateUpdate_Object()
{

	__super::LateUpdate_Object();


}

void CInventory::Render_Object()
{

	if (m_bIsOn)
	{
		// BackGround
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(240, 255, 255, 255));
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_BKG]);

		m_pInventoryTexCom[INVEN_BKG]->Render_Texture();
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));


		// Cancel Button
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_CANCELBUTTON]);
		m_pInventoryTexCom[INVEN_CANCELBUTTON]->Render_Texture();
		m_pBufferCom->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


		// Tab Button - Armor
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_ATABBUTTON]);
		m_pInventoryTexCom[INVEN_ATABBUTTON]->Render_Texture();
		m_pBufferCom->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


		// Tab Button - Skill
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_STABBUTTON]);
		m_pInventoryTexCom[INVEN_STABBUTTON]->Render_Texture();
		m_pBufferCom->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


		// Tab Button Image - Armor Texture
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_ARMORTEX]);
		m_pInventoryTexCom[INVEN_ARMORTEX]->Render_Texture();
		m_pBufferCom->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


		// Tab Button Image - Skill Texture
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_SKILLTEX]);
		m_pInventoryTexCom[INVEN_SKILLTEX]->Render_Texture();
		m_pBufferCom->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

		// Tab Line 
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_TABLINE]);
		m_pInventoryTexCom[INVEN_TABLINE]->Render_Texture();
		m_pBufferCom->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


		// 1 Line
		// Button 1
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_BUTTON1]);
		m_pInventoryTexCom[INVEN_BUTTON1]->Render_Texture();
		m_pBufferCom->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	
		// Button 2
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_BUTTON2]);
		m_pInventoryTexCom[INVEN_BUTTON2]->Render_Texture();
		m_pBufferCom->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


		// Button 3
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_BUTTON3]);
		m_pInventoryTexCom[INVEN_BUTTON3]->Render_Texture();
		m_pBufferCom->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

		// Button 4
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_BUTTON4]);
		m_pInventoryTexCom[INVEN_BUTTON4]->Render_Texture();
		m_pBufferCom->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

		// 2 Line
		// Button 5
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_BUTTON5]);
		m_pInventoryTexCom[INVEN_BUTTON5]->Render_Texture();
		m_pBufferCom->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


		// Button 6
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_BUTTON6]);
		m_pInventoryTexCom[INVEN_BUTTON6]->Render_Texture();
		m_pBufferCom->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


		// Button 7
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_BUTTON7]);
		m_pInventoryTexCom[INVEN_BUTTON7]->Render_Texture();
		m_pBufferCom->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


		// Button 8
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_BUTTON8]);
		m_pInventoryTexCom[INVEN_BUTTON8]->Render_Texture();
		m_pBufferCom->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


		// 3 Line 
		// Button 9
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_BUTTON9]);
		m_pInventoryTexCom[INVEN_BUTTON9]->Render_Texture();
		m_pBufferCom->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


		// Button 10
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_BUTTON10]);
		m_pInventoryTexCom[INVEN_BUTTON10]->Render_Texture();
		m_pBufferCom->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


		// Button 11
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_BUTTON11]);
		m_pInventoryTexCom[INVEN_BUTTON11]->Render_Texture();
		m_pBufferCom->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


		// Button 12
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_BUTTON12]);
		m_pInventoryTexCom[INVEN_BUTTON12]->Render_Texture();
		m_pBufferCom->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


		//// Sort Button
		//m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		//m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matInventoryWolrd[INVEN_SORTBUTTON]);
		//m_pInventoryTexCom[INVEN_SORTBUTTON]->Render_Texture();
		//m_pBufferCom->Render_Buffer();
		//m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);



	}
	
	__super::Render_Object();

}

HRESULT CInventory::Add_Component()
{
	CComponent* pComponent = nullptr;

	// RcTex Com
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


#pragma region Texture


	// BackGround
	pComponent = m_pInventoryTexCom[INVEN_BKG] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_BKG", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - cancel
	pComponent = m_pInventoryTexCom[INVEN_CANCELBUTTON] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_Cancel", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - Tab Button Armor
	pComponent = m_pInventoryTexCom[INVEN_ATABBUTTON] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Tab", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - Tab Button Armor Tex
	pComponent = m_pInventoryTexCom[INVEN_ARMORTEX] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Tab_Armors_Texture", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// UI - Tab Button Skill
	pComponent = m_pInventoryTexCom[INVEN_STABBUTTON] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Tab", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// UI - Tab Button Skill Tex
	pComponent = m_pInventoryTexCom[INVEN_SKILLTEX] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Tab_Skill_Texture", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// UI - Tab Line
	pComponent = m_pInventoryTexCom[INVEN_TABLINE] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Line", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	
	// 1 Line
	// UI - Button1
	pComponent = m_pInventoryTexCom[INVEN_BUTTON1] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_blank", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - Button2
	pComponent = m_pInventoryTexCom[INVEN_BUTTON2] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_blank", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - Button3
	pComponent = m_pInventoryTexCom[INVEN_BUTTON3] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_blank", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - Button4
	pComponent = m_pInventoryTexCom[INVEN_BUTTON4] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_blank", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// 2 Line
	// UI - Button5
	pComponent = m_pInventoryTexCom[INVEN_BUTTON5] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_blank", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - Button6
	pComponent = m_pInventoryTexCom[INVEN_BUTTON6] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_blank", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// UI - Button7
	pComponent = m_pInventoryTexCom[INVEN_BUTTON7] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_blank", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - Button8
	pComponent = m_pInventoryTexCom[INVEN_BUTTON8] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_blank", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// 3 Line
	// UI - Button9
	pComponent = m_pInventoryTexCom[INVEN_BUTTON9] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_blank", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	
	// UI - Button10
	pComponent = m_pInventoryTexCom[INVEN_BUTTON10] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_blank", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - Button11
	pComponent = m_pInventoryTexCom[INVEN_BUTTON11] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_blank", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// UI - Button12
	pComponent = m_pInventoryTexCom[INVEN_BUTTON12] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_blank", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	//// UI - Sort button 
	//pComponent = m_pInventoryTexCom[INVEN_SORTBUTTON] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Inventory_Button_Plain", this));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

#pragma endregion





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

void CInventory::Key_Input()
{
	if (CInputDev::GetInstance()->Key_Down(VK_TAB))
	{
		m_bIsOn = !m_bIsOn;
	}

	if (m_bIsOn == true)
	{
		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::PLAYER)->Layer_SetActive(false);
		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::MONSTER)->Layer_SetActive(false);
		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::EFFECT)->Layer_SetActive(false);

	}
	else
	{
		Ready_Object();
		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::PLAYER)->Layer_SetActive(true);
		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::EFFECT)->Layer_SetActive(true);
		CManagement::GetInstance()->Get_Layer(OBJ_TYPE::MONSTER)->Layer_SetActive(true);
	}
	

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
