#include "..\..\Header\RigidBody.h"

#include "GameObject.h"
#include "Export_Function.h"

CRigidBody::CRigidBody()
{
	
}

CRigidBody::CRigidBody(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev, COMPONENT_TYPE::RIGIDBODY)
{
	ZeroMemory(&m_vForce, sizeof(_vec3));
	ZeroMemory(&m_vAcc, sizeof(_vec3));
	ZeroMemory(&m_vVelocity, sizeof(_vec3));

	// 수정시 팀장 보고 후 수정
	m_fMass		= 10.f;
	m_fMaxSpeed = 30.f;
	m_fFriction = 0.1f;
	m_vGravity = vec3.down;
}

CRigidBody::CRigidBody(const CRigidBody& rhs, CGameObject* _pOwnerObject)
	: CComponent(rhs, _pOwnerObject)
	, m_vForce(rhs.m_vForce)
	, m_vAcc(rhs.m_vAcc)
	, m_vVelocity(rhs.m_vVelocity)
	, m_vGravity(rhs.m_vGravity)
	, m_fMass(rhs.m_fMass)
	, m_fMaxSpeed(rhs.m_fMaxSpeed)
	, m_fFriction(rhs.m_fFriction)

{
	Ready_RigidBody();
}

CRigidBody::~CRigidBody()
{
}

HRESULT CRigidBody::Ready_RigidBody()
{


	return S_OK;
}

void CRigidBody::LateUpdate_Component()
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	// 현재 속도 계산
	NULL_CHECK(m_pOwnerObject);

	m_vForce += (m_vGravity * m_fMass);
	m_vForce.y = 0;

	if (D3DXVec3Length(&m_vForce) > 0.f) // 임시 마찰 
	{
		m_vForce -= m_vForce * m_fFriction;
	}

	m_vAcc = m_vForce / m_fMass;							

	m_vVelocity = m_vAcc * Engine::Get_TimeDelta(L"Timer_FPS65");

	if (D3DXVec3Length(&m_vVelocity) > m_fMaxSpeed)
	{
		D3DXVec3Normalize(&m_vVelocity, &m_vVelocity);
		m_vVelocity *= m_fMaxSpeed;
	}

	// 포지션 적용
	_vec3 vPos = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS);

	vPos += m_vVelocity;

	m_pOwnerObject->Get_Transform()->Set_Pos(vPos);
}

void CRigidBody::Knock_Back(const _vec3& _vDir, const _float& _fImpulse)
{
	_vec3 vDir;

	if (1.3f < D3DXVec3Length(&_vDir))
		D3DXVec3Normalize(&vDir, &_vDir);
	else
		vDir = _vDir;

	Add_Impulse(vDir * _fImpulse);
}

void CRigidBody::Knock_Back(CGameObject* _pAttacker, const _float& _fImpulse)
{
	NULL_CHECK(_pAttacker);

	_vec3 vDir = m_pOwnerObject->Get_Transform()->Get_Info(INFO_POS) - _pAttacker->Get_Transform()->Get_Info(INFO_POS);

	D3DXVec3Normalize(&vDir, &vDir);

	Add_Impulse(vDir * _fImpulse);
}


CRigidBody* CRigidBody::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRigidBody* pInstance = new CRigidBody(pGraphicDev);

	if (FAILED(pInstance->Ready_RigidBody()))
	{
		Safe_Release(pInstance);
		MSG_BOX("RigidBody Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent* CRigidBody::Clone(CGameObject* _pOwnerObject)
{
	return new CRigidBody(*this, _pOwnerObject);
}

void CRigidBody::Free()
{
	CComponent::Free();
}
