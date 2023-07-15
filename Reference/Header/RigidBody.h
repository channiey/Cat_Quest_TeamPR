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
	void					Knock_Back(const _vec3& _vDir, const _float& _fImpulse = DF_RB_KNOCKBACK);		    // ���� ������ �������� �˹� (���� ��� ����)
	void					Knock_Back(CGameObject* _pAttacker, const _float& _fImpulse = DF_RB_KNOCKBACK);	// �������� �������κ��� �˹� (���� ��� �ڵ�)

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