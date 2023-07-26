#include "ComeBack_Bullet.h"
#include "Export_Function.h"
#include "EventMgr.h"

CComBack_Bullet::CComBack_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner)
	: CBossProjectile(pGraphicDev, OBJ_ID::PROJECTILE_BOSS_CONVERGING)
{

	m_vPos = _vPos;
	m_pTarget = pTarget;
	m_pOwner = pOwner;
}

CComBack_Bullet::CComBack_Bullet(const CProjectile& rhs)
	: CBossProjectile(rhs)
{
}

CComBack_Bullet::~CComBack_Bullet()
{
}

HRESULT CComBack_Bullet::Ready_Object()
{
	__super::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	m_pTransformCom->Set_Pos(m_vPos);
	//m_pTransformCom->Set_Dir(m_vDir);

    m_vOriginPos = m_pTransformCom->Get_Info(INFO_POS);

    m_bComeBack = false;
    m_bStop = false;


	m_fSpeed = 5.f;
    m_fAccTime = 0.f;
	m_szName = L"Projectile_Boss_ComeBack_Bullet";

	return S_OK;
}

_int CComBack_Bullet::Update_Object(const _float& fTimeDelta)
{
    Engine::Add_RenderGroup(RENDER_ALPHA, this);
    _int iExit = __super::Update_Object(fTimeDelta);

    _vec3 vTargetPos = m_pTarget->Get_Transform()->Get_Info(INFO_POS);

    _vec3 vDir = -(vTargetPos - m_pTransformCom->Get_Info(INFO_POS));  // 타겟과의 방향 반대

    _vec3 vOwnerPos = m_pOwner->Get_Transform()->Get_Info(INFO_POS);

    _vec3 vOwnerDir = -(vOwnerPos - m_pTransformCom->Get_Info(INFO_POS)); // 주인과의 방향 반대 

    vOwnerDir = { vOwnerDir.x, 0.f, vOwnerDir.z }; // Y값 제거

    _vec3 vOriginDir = m_vOriginPos - m_pTransformCom->Get_Info(INFO_POS);

    _float fDistanceOrigin = D3DXVec3Length(&vOriginDir);


    m_fAccTime += fTimeDelta;

    if (m_fAccTime < 1.f)
    {
        m_pTransformCom->Set_Dir(vec3.zero);
    }
 
    if ( m_bComeBack == false && m_bStop == false && m_fAccTime >= 1.f)
    {
        m_fSpeed = 30.f;
        m_pTransformCom->Set_Dir(vOwnerDir);
        m_bStop = true;

    }
    if (m_bComeBack == false && m_bStop == true && m_fAccTime >= 2.f)
    {
        m_fSpeed = 0.f;
        m_bComeBack = true;
    } 
    
    if (m_bComeBack == true && m_bStop == true && m_fAccTime >= 3.f)
    {
        m_fSpeed = 40.f;
        //m_pTransformCom->Set_Dir(vec3.zero);
        this->m_pAICom->Chase_TargetY(&m_vOriginPos, fTimeDelta, m_fSpeed);
       
    }
     
    if (m_bComeBack == true && m_bStop == true && fDistanceOrigin <= 2.f || m_fAccTime >= 6.f)
    {
        m_fAccTime = 0.f;
        CEventMgr::GetInstance()->Delete_Obj(this);
    }
    
    

    m_pTransformCom->Translate(fTimeDelta * m_fSpeed);



    return iExit;
}

void CComBack_Bullet::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}

void CComBack_Bullet::Render_Object()
{
    m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

    m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

    m_pBufferCom->Render_Buffer();

    m_pGraphicDev->SetTexture(0, NULL);


    __super::Render_Object();
}

void CComBack_Bullet::Comeback(const _float& fTimeDelta)
{
    this->m_pAICom->Chase_TargetY(&m_vOriginPos, fTimeDelta, m_fSpeed);
}

HRESULT CComBack_Bullet::Add_Component()
{
    CComponent* pComponent;

    // Texture
    pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Projectile_PupleBullet", this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

    // AI
    pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);

    return S_OK;
}


CComBack_Bullet* CComBack_Bullet::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner)
{
    CComBack_Bullet* pInstance = new CComBack_Bullet(pGraphicDev, _vPos, pTarget, pOwner);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("Converging_Bullet Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CComBack_Bullet::Free()
{
    __super::Free();
}
