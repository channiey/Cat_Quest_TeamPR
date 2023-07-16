#include "ExpCoin.h"
#include "Export_Function.h"
#include "EventMgr.h"

#include "Shadow_Item.h"

CExpCoin::CExpCoin(LPDIRECT3DDEVICE9 pGraphicDev)
	: CItem_Object(pGraphicDev, OBJ_ID::ITEM_EXP)
{
}

CExpCoin::CExpCoin(const CItem& rhs)
	: CItem_Object(rhs)
{
}

CExpCoin::~CExpCoin()
{

}

HRESULT CExpCoin::Ready_Object()
{
	__super::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	// STATEINFO Setting
	m_tStatInfo.fCurExp = 100.f;

	// ���� �̹��� ũ��
	m_vImageSize.x = 0.68f;  // 100px = 1.f
	m_vImageSize.y = 0.68f;
	m_vImageSize.z = 2.f;   // ���� ��



	// Transform Setting
	m_pTransformCom->Set_Scale(_vec3{ m_vImageSize.x * 1.5f, m_vImageSize.y * 1.5f, m_vImageSize.z });
	m_pTransformCom->Set_Pos(_vec3{ 85.f, m_pTransformCom->Get_Scale().y, 30.f });
	
	m_fJumpingSpeed = 0.01;

	CEventMgr::GetInstance()->Add_Obj(L"Exp_Shadow", CShadow_Item::Create(m_pGraphicDev, this));

	return S_OK;
}

_int CExpCoin::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CItem::Update_Object(fTimeDelta);   // ���� ����
	Engine::Add_RenderGroup(RENDER_ALPHA, this);	 //	���� �׷� �߰�


	// Jumping 

	_vec3		vOwnerPos	= m_pTransformCom->Get_Info(INFO_POS);
	float		Y			= m_pTransformCom->Get_Scale().y;



	if (vOwnerPos.y < Y || vOwnerPos.y > Y + 0.3f)
	{
		m_fJumpingSpeed *= -1;
	}
	m_pTransformCom->Translate(DIR_UP, m_fJumpingSpeed, WORLD);





	return iExit;
}

void CExpCoin::LateUpdate_Object()
{
	__super::LateUpdate_Object();

}

void CExpCoin::Render_Object()
{

	m_pTextureCom->Render_Texture(); // �ؽ�ó ���� -> ���� ���� ���� ��!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	CGameObject::Render_Object(); // �ݶ��̴� ���

}

HRESULT CExpCoin::Add_Component()
{
	CComponent* pComponent = nullptr;

	
	// Texture
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Item_Exp", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);



	return S_OK;
}

CExpCoin* CExpCoin::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CExpCoin* pInstance = new CExpCoin(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("ExpCoin Create Failed");
		return nullptr;
	}
	return pInstance;
}

void CExpCoin::Free()
{

	__super::Free();
}