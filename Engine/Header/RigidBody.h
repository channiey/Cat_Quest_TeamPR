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

	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/


public:						// 직접 지정한 방향으로 넉백 (방향 계산 수동)
	void					Knock_Back(const _vec3& _vDir, const _float& _fImpulse = DF_RB_KNOCKBACK);		    
							
							// 공격자의 방향으로부터 넉백 (방향 계산 자동)
	void					Knock_Back(CGameObject* _pAttacker, const _float& _fImpulse = DF_RB_KNOCKBACK);		

	const _bool				Is_Vel_Zero() { if (0.1f > D3DXVec3Length(&m_vVelocity)) return TRUE; else return FALSE; }
	void					Zero_KnockBack() { m_vForce = vec3.zero; m_vVelocity = vec3.zero; m_vAcc = vec3.zero; }

	void					Jump();

	const _bool&			Is_Jump() const { return m_bJump; }

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

	_bool					m_bJump;
	_float					m_fStartY;

public:
	static CRigidBody*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*		Clone(CGameObject* _pOwnerObject);

private:
	virtual void			Free();

};

END