#include "MonHpUI.h"
#include "Export_Function.h"

#include "Monster.h"

CMonHpUI::CMonHpUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev, OBJ_ID::UI_HP), m_pMonster(nullptr), m_fHpRatio(1.f), m_fCurRatio(1.f)
{
}

CMonHpUI::CMonHpUI(const CMonHpUI& rhs)
	: CUI(rhs)
{
}

CMonHpUI::~CMonHpUI()
{
}

HRESULT CMonHpUI::Ready_Object()
{
	CGameObject::Ready_Object();

	m_eUIType = UI_TYPE::WORLD;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pUITransformCom[0]->Set_Scale(_vec3{ 1.4f, 0.4f, 1.f });
	m_pUITransformCom[1]->Set_Scale(_vec3{ 1.4f, 0.4f, 1.f });
	m_pUITransformCom[2]->Set_Scale(_vec3{ 0.6f, 0.6f, 1.f });
	m_pUITransformCom[3]->Set_Scale(_vec3{ 0.6f, 0.6f, 1.f });
	m_pUITransformCom[4]->Set_Scale(_vec3{ 1.4f, 0.4f, 1.f });


	return S_OK;
}

_int CMonHpUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	if (dynamic_cast<CMonster*>(m_pMonster)->Get_StatInfo().bDead)
	{
		CEventMgr::GetInstance()->Delete_Obj(this);  // ªË¡¶
		return iExit;
	}

	if (nullptr != m_pMonster)
		m_fCurRatio = dynamic_cast<CMonster*>(m_pMonster)->Get_StatInfo().fCurHP / dynamic_cast<CMonster*>(m_pMonster)->Get_StatInfo().fMaxHP;

	if (1.f < m_fCurRatio)
	{
		m_fCurRatio = 1.f;
		m_fHpRatio = m_fCurRatio;
	}
		

	return iExit;
}

void CMonHpUI::LateUpdate_Object()
{
	Follow_Owner();

	_vec3 vInitPosition = m_pUITransformCom[1]->Get_Info(INFO::INFO_POS);

	float fMoveX = (1.0f - m_fCurRatio) * 1.6f;
	_vec3 vNewPosition = _vec3(vInitPosition.x - fMoveX, vInitPosition.y, vInitPosition.z);

	m_pUITransformCom[1]->Set_Scale(_vec3{ 1.6f * m_fCurRatio, 0.4f, 1.0f });
	m_pUITransformCom[1]->Set_Pos(vNewPosition);

	if (m_fCurRatio >= 1.f)
	{
		m_pUITransformCom[4]->Set_Scale(_vec3{ 1.6f, 0.4f, 1.f });
	}
	else if (m_fCurRatio != m_fHpRatio && m_fCurRatio < 1.f)
	{
		_vec3 vOutScale = m_pUITransformCom[4]->Lerp(m_pUITransformCom[4]->Get_Scale()
			, m_pUITransformCom[1]->Get_Scale(), 1.2f, Engine::Get_TimeDelta(L"Timer_FPS65"));

		if (vOutScale.z != -99)
		{
			_vec3 vGoldInitPosition = m_pUITransformCom[4]->Get_Info(INFO::INFO_POS);

			float fGoldMoveX = (1.0f - (vOutScale.x / 1.6f)) * 1.6f;
			_vec3 vGoldNewPosition = _vec3(vGoldInitPosition.x - fGoldMoveX, vGoldInitPosition.y, vGoldInitPosition.z);

			m_pUITransformCom[4]->Set_Scale(vOutScale);
			m_pUITransformCom[4]->Set_Pos(vGoldNewPosition);
		}
		else
			m_fHpRatio = m_fCurRatio;
	}

	if (m_fCurRatio == m_fHpRatio)
	{
		m_pUITransformCom[4]->Set_Scale(_vec3{ 1.6f * m_fCurRatio, 0.4f, 1.0f });
		m_pUITransformCom[4]->Set_Pos(vNewPosition);
	}




	__super::LateUpdate_Object();

}

void CMonHpUI::Render_Object()
{
	if (dynamic_cast<CMonster*>(m_pMonster)->Get_StateMachine()->Get_CurState() == STATE_TYPE::CHASE ||
		dynamic_cast<CMonster*>(m_pMonster)->Get_StateMachine()->Get_CurState() == STATE_TYPE::BACK_CHASE ||
		dynamic_cast<CMonster*>(m_pMonster)->Get_StateMachine()->Get_CurState() == STATE_TYPE::MONATTACK || 
		dynamic_cast<CMonster*>(m_pMonster)->Get_StateMachine()->Get_CurState() == STATE_TYPE::BACK_MONATTACK || 
		dynamic_cast<CMonster*>(m_pMonster)->Get_StateMachine()->Get_CurState() == STATE_TYPE::FRONT_HIT)
	{
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[0]->Get_WorldMat());
		m_pTextureCom->Render_Texture(7);
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[4]->Get_WorldMat());
		m_pTextureCom->Render_Texture(10);
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[1]->Get_WorldMat());
		m_pTextureCom->Render_Texture(1);
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[2]->Get_WorldMat());
		m_pTextureCom->Render_Texture(9);
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pUITransformCom[3]->Get_WorldMat());
		m_pTextureCom->Render_Texture(6);
		m_pBufferCom->Render_Buffer();
	}

	

}

HRESULT CMonHpUI::Add_Component()
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

void CMonHpUI::Follow_Owner()
{
	CTransform* pMonsterTransform = m_pMonster->Get_Transform();
	NULL_CHECK(pMonsterTransform);

	_vec3		vMonsterPos;
	vMonsterPos = pMonsterTransform->Get_Info(INFO_POS);

	m_pUITransformCom[0]->Set_Pos({ vMonsterPos.x , vMonsterPos.y, vMonsterPos.z - 3.5f });
	m_pUITransformCom[1]->Set_Pos({ vMonsterPos.x, vMonsterPos.y, vMonsterPos.z - 3.5f });
	m_pUITransformCom[2]->Set_Pos({ vMonsterPos.x - 1.9f, vMonsterPos.y, vMonsterPos.z - 3.5f });
	m_pUITransformCom[3]->Set_Pos({ vMonsterPos.x + 1.4f, vMonsterPos.y, vMonsterPos.z - 3.5f });
	m_pUITransformCom[4]->Set_Pos({ vMonsterPos.x , vMonsterPos.y, vMonsterPos.z - 3.5f });
}

CMonHpUI* CMonHpUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pMonster)
{
	CMonHpUI* pInstance = new CMonHpUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("MonHpUI Create Failed");
		return nullptr;
	}
	pInstance->Set_Owner(pMonster);

	return pInstance;
}

void CMonHpUI::Free()
{
	__super::Free();

}
