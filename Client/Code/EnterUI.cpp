#include "EnterUI.h"
#include "Export_Function.h"

CEnterUI::CEnterUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev), m_bIsOn(false), m_bIsShirk(false), m_bIsExpand(false), m_bIsStart(false), m_bIsEnd(false)
{
}

CEnterUI::CEnterUI(const CEnterUI& rhs)
	: CUI(rhs)
{
}

CEnterUI::~CEnterUI()
{
}

HRESULT CEnterUI::Ready_Object()
{
	m_eUIType = UI_TYPE::VIEW;

	D3DXMatrixIdentity(&m_UImatWorld);

	m_fSizeX = 0.f;
	m_fSizeY = 12.f;

	m_UImatWorld._11 = m_fSizeX;
	m_UImatWorld._22 = m_fSizeY;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CEnterUI::Update_Object(const _float& fTimeDelta)
{
	if (m_bIsOn)
	{
		_int iExit = __super::Update_Object(fTimeDelta);

		if (m_bIsStart)
		{
			m_fSizeX += 100.f * fTimeDelta;
			m_fSizeY += 100.f * fTimeDelta;

			if (m_fSizeX >= 55)
			{
				m_bIsShirk = true;
				m_bIsStart = false;
			}
				
		}

		if (m_bIsEnd)
		{
			m_fSizeX -= 100.f * fTimeDelta;
			m_fSizeY -= 115.f * fTimeDelta;

			if (m_fSizeX <= 0)
			{
				m_fSizeX = 0.f;
				m_fSizeY = 12.f;

				m_UImatWorld._11 = m_fSizeX;
				m_UImatWorld._22 = m_fSizeY;

				m_bIsOn = false;
				m_bIsEnd = false;
			}
		}


		if (m_bIsExpand)
		{
			m_fSizeX += 16.f * fTimeDelta;
			m_fSizeY += 16.f * fTimeDelta;

			if (55 < m_fSizeX)
			{
				m_bIsExpand = false;
				m_bIsShirk = true;
			}
		}

		if (m_bIsShirk)
		{
			m_fSizeX -= 30.f * fTimeDelta;
			m_fSizeY -= 30.f * fTimeDelta;

			if (45 > m_fSizeX)
			{
				m_bIsExpand = true;
				m_bIsShirk = false;
			}
		}



		return iExit;
	}
	return 0;
}

void CEnterUI::LateUpdate_Object()
{
	if (m_bIsOn)
	{
		m_UImatWorld._11 = m_fSizeX;
		m_UImatWorld._22 = m_fSizeY;

		__super::LateUpdate_Object();
	}
	
}

void CEnterUI::Render_Object()
{
	if (m_bIsOn)
	{
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_UImatWorld);

		m_pTextureCom->Render_Texture();
		m_pBufferCom->Render_Buffer();
	}
	
}

void CEnterUI::EnterUI_On(CGameObject* pObj)
{
	if (m_bIsOn)
		return;

	m_bIsOn = true;
	m_bIsStart = true;

	_vec3 vObjWorldPos = pObj->Get_Transform()->Get_Info(INFO::INFO_POS);
	_matrix matWorld = pObj->Get_Transform()->Get_WorldMat();
	_matrix matView = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatView();
	_matrix matProj = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatProj();
	D3DVIEWPORT9 pViewport = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_ViewPort();

	D3DXVec3TransformCoord(&vObjWorldPos, &vObjWorldPos, &matView);
	D3DXVec3TransformCoord(&vObjWorldPos, &vObjWorldPos, &matProj);

	_float ScreenX = vObjWorldPos.x * (pViewport.Width / 2) + pViewport.X + (pViewport.Width / 2);
	_float ScreenY = -vObjWorldPos.y * (pViewport.Height / 2) + pViewport.Y + (pViewport.Height / 2);

	m_UImatWorld._41 = ScreenX;
	m_UImatWorld._42 = ScreenY + 70;
}

void CEnterUI::EnterUI_Off(CGameObject* pObj)
{
	if (m_bIsStart)
		return;

	m_bIsExpand = false;
	m_bIsShirk = false;
	m_bIsEnd = true;
}

HRESULT CEnterUI::Add_Component()
{

	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Enter", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

CEnterUI* CEnterUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CEnterUI* pInstance = new CEnterUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("EnterUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEnterUI::Free()
{
	__super::Free();

}
