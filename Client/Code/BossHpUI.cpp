#include "BossHpUI.h"
#include "Export_Function.h"

#include "Monster.h"

CBossHpUI::CBossHpUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev, OBJ_ID::UI_HP), m_pMonster(nullptr), m_fHpRatio(1.f), m_fCurRatio(1.f)
{
}

CBossHpUI::CBossHpUI(const CBossHpUI& rhs)
	: CUI(rhs)
{
}

CBossHpUI::~CBossHpUI()
{
}

HRESULT CBossHpUI::Ready_Object()
{
	CGameObject::Ready_Object();

	m_eUIType = UI_TYPE::VIEW;


	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	for (_uint i = 0; i < 5; ++i)
		D3DXMatrixIdentity(&m_matUI[i]);

	m_fPosX = WINCX >> 1;
	m_fPosY = 100;

	m_fSizeX = 15.f;
	m_fSizeY = 15.f;
	m_fBarMultiX = 20.f;
	m_fBarMultiY = 1.2f;

	//m_fCapSizeX = 24.f;
	//m_fCapSizeY = 23.5f;
	//m_fCapMultiX = 0.5f;
	//m_fCapMultiY = 0.5f;

	m_fBarRealX = m_fSizeX * m_fBarMultiX;
	m_fBarRealY = m_fSizeY * m_fBarMultiY;
	//m_fCapRealX = m_fCapSizeX * m_fCapMultiX;
	//m_fCapRealY = m_fCapSizeY * m_fCapMultiY;


	m_matUI[0]._11 = m_fBarRealX;
	m_matUI[0]._22 = m_fBarRealY;
	m_matUI[0]._41 = m_fPosX;
	m_matUI[0]._42 = m_fPosY;

	m_matUI[1]._11 = m_fBarRealX;
	m_matUI[1]._22 = m_fBarRealY;
	m_matUI[1]._41 = m_fPosX;
	m_matUI[1]._42 = m_fPosY;

	//m_matUI[2]._11 = m_fBarRealX;
	//m_matUI[2]._22 = m_fBarRealY;

	/*m_matUI[3]._11 = m_fCapRealX;
	m_matUI[3]._22 = m_fCapRealY;

	m_matUI[4]._11 = m_fCapRealX;
	m_matUI[4]._22 = m_fCapRealY;*/

	m_bPurpleEnd = false;
	m_bRedEnd = false;

	return S_OK;
}

_int CBossHpUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	NULL_CHECK_RETURN(m_pMonster, E_FAIL);

	if (dynamic_cast<CMonster*>(m_pMonster)->Get_StatInfo().bDead)
	{
		CEventMgr::GetInstance()->Delete_Obj(this);  // ����
		return iExit;
	}

	_float fHpRatio = dynamic_cast<CMonster*>(m_pMonster)->Get_StatInfo().fCurHP / dynamic_cast<CMonster*>(m_pMonster)->Get_StatInfo().fMaxHP;

	if (1.f <= fHpRatio)
	{
		m_fCurRatio = 1.f;
		fHpRatio = 1.f;
	}
		

	if (m_fCurRatio != fHpRatio)
	{
		m_tSize.Init_Lerp();
		m_tSize.Set_Lerp(0.5f, m_fCurRatio, fHpRatio);

		m_fCurRatio = fHpRatio;
	}

	m_tSize.Update_Lerp(fTimeDelta);

	return iExit;
}

void CBossHpUI::LateUpdate_Object()
{
	if (m_tSize.bActive)
	{
		float fMoveX = (1.f - m_tSize.fCurValue) * m_fBarRealX;

		m_matUI[1]._11 = m_tSize.fCurValue * m_fBarRealX;
		m_matUI[1]._41 = m_fPosX - fMoveX;
	}
	if (m_fCurRatio <= 0 && !m_tSize.bActive)
	{
		float fMoveX = (1.f - m_fCurRatio) * m_fBarRealX;

		m_matUI[1]._11 = m_fCurRatio * m_fBarRealX;
		m_matUI[1]._41 = m_fPosX - fMoveX;
	}

	__super::LateUpdate_Object();

}

void CBossHpUI::Render_Object()
{
	if (dynamic_cast<CMonster*>(m_pMonster)->Get_StateMachine()->Get_CurState() != STATE_TYPE::PATROL			&&
		dynamic_cast<CMonster*>(m_pMonster)->Get_StateMachine()->Get_CurState() != STATE_TYPE::BACK_PATROL		&&
		dynamic_cast<CMonster*>(m_pMonster)->Get_StateMachine()->Get_CurState() != STATE_TYPE::COMEBACK			&&
		dynamic_cast<CMonster*>(m_pMonster)->Get_StateMachine()->Get_CurState() != STATE_TYPE::BACK_COMEBACK	&&
		dynamic_cast<CMonster*>(m_pMonster)->Get_StateMachine()->Get_CurState() != STATE_TYPE::BOSS_INTRO_DOWN	&&
		dynamic_cast<CMonster*>(m_pMonster)->Get_StateMachine()->Get_CurState() != STATE_TYPE::BOSS_INTRO_SWORD &&
		dynamic_cast<CMonster*>(m_pMonster)->Get_StateMachine()->Get_CurState() != STATE_TYPE::BOSS_INTRO_WING	&&
		dynamic_cast<CMonster*>(m_pMonster)->Get_StateMachine()->Get_CurState() != STATE_TYPE::BOSSDEAD)
	{
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matUI[0]);
		m_pTextureCom->Render_Texture(7);
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matUI[1]);
		m_pTextureCom->Render_Texture(1);
		m_pBufferCom->Render_Buffer();

		/*m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matUI[2]);
		m_pTextureCom->Render_Texture(9);
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matUI[3]);
		m_pTextureCom->Render_Texture(6);
		m_pBufferCom->Render_Buffer();*/

		/*m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matUI[4]);
		m_pTextureCom->Render_Texture(10);
		m_pBufferCom->Render_Buffer();*/

	}
		
}

void CBossHpUI::Caulate_Purple_Bar()
{
}

void CBossHpUI::Caulate_Red_Bar()
{
}

HRESULT CBossHpUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Bar", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	for (_uint i = 0; i < 5; ++i)
	{
		pComponent = m_pUITransformCom[i] = dynamic_cast<CTransform*>(Engine::Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);
	}

	return S_OK;
}




CBossHpUI* CBossHpUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pMonster)
{
	CBossHpUI* pInstance = new CBossHpUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("MonHpUI Create Failed");
		return nullptr;
	}
	pInstance->Set_Owner(pMonster);

	return pInstance;
}

void CBossHpUI::Free()
{
	__super::Free();

}

