#include "ConvergingFire_Bullet.h"
#include "Export_Function.h"
#include "EventMgr.h"

CConvergingFire_Bullet::CConvergingFire_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner, _float fTimeDelta)
	: CBossProjectile(pGraphicDev, OBJ_ID::PROJECTILE_BOSS_CONVERGING)
{

	m_vPos = _vPos;
	m_pTarget = pTarget;
	m_pOwner = pOwner;
}

CConvergingFire_Bullet::CConvergingFire_Bullet(const CProjectile& rhs)
	: CBossProjectile(rhs)
{
}

CConvergingFire_Bullet::~CConvergingFire_Bullet()
{
}

HRESULT CConvergingFire_Bullet::Ready_Object()
{
	__super::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	m_pTransformCom->Set_Pos(m_vPos);
	m_pTransformCom->Set_Dir(m_vDir);


	m_fSpeed = 10.f;

	m_szName = L"Projectile_ChaseBullet";

	return S_OK;
}

_int CConvergingFire_Bullet::Update_Object(const _float& fTimeDelta)
{
    Engine::Add_RenderGroup(RENDER_ALPHA, this);
    _int iExit = __super::Update_Object(fTimeDelta);

    m_fAccTime += fTimeDelta;

    if (m_fAccTime <= 2.f)
    {
        _vec3 vTargetPos = m_pTarget->Get_Transform()->Get_Info(INFO_POS);

        this->m_pAICom->Chase_Target(&vTargetPos, fTimeDelta, m_fSpeed);
    }
    else if (m_fAccTime > 2.f)
    {
        m_fSpeed = 5.f;
    }
    if (m_fAccTime >= 3.f)
    {
        CEventMgr::GetInstance()->Delete_Obj(this);
    }


    m_pTransformCom->Translate(fTimeDelta * m_fSpeed);

    return iExit;
}

void CConvergingFire_Bullet::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}

void CConvergingFire_Bullet::Render_Object()
{
    m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

    m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

    m_pBufferCom->Render_Buffer();

    m_pGraphicDev->SetTexture(0, NULL);


    __super::Render_Object();
}

HRESULT CConvergingFire_Bullet::Add_Component()
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


CConvergingFire_Bullet* CConvergingFire_Bullet::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner, _float fTimeDelta)
{
    CConvergingFire_Bullet* pInstance = new CConvergingFire_Bullet(pGraphicDev, _vPos, pTarget, pOwner, fTimeDelta);

    if (FAILED(pInstance->Ready_Object()))
    {
        Safe_Release(pInstance);

        MSG_BOX("Converging_Bullet Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CConvergingFire_Bullet::Free()
{
    __super::Free();
}
