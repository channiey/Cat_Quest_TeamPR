#pragma once

#include "Component.h"

BEGIN(Engine)

class CGameObject;

class ENGINE_DLL CRigidBody : public CComponent
{
private:
	explicit CRigidBody();
	explicit CRigidBody(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRigidBody(const CRigidBody& rhs, CGameObject* _pOwnerObject);
	virtual ~CRigidBody();



public:
	HRESULT					Ready_RigidBody();
	virtual void			LateUpdate_Component() override;

public:
	void					Knock_Back(const _vec3& _vDir, const _float& _fImpulse = DF_RB_KNOCKBACK);		    // 직접 지정한 방향으로 넉백 (방향 계산 수동)
	void					Knock_Back(CGameObject* _pAttacker, const _float& _fImpulse = DF_RB_KNOCKBACK);	// 공격자의 방향으로부터 넉백 (방향 계산 자동)

private:
	void					Add_Impulse(const _vec3& _vForce) { m_vForce += _vForce; }

	void					Zero_Force() { m_vForce = vec3.zero; }
	void					Zero_Velocity() { m_vVelocity = vec3.zero;  }

private:
	_vec3					m_vForce;
	_vec3					m_vAcc;
	_vec3					m_vVelocity;
	_vec3					m_vGravity;
	
	_float					m_fMass;
	_float					m_fMaxSpeed;
	_float					m_fFriction;

public:
	static CRigidBody*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*		Clone(CGameObject* _pOwnerObject);

private:
	virtual void			Free();

};

END