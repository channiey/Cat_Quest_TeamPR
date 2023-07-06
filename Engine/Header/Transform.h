#pragma once

#include "Component.h"

BEGIN(Engine)
class CGameObject;
class ENGINE_DLL CTransform :	public CComponent
{
private:
	explicit CTransform();
	explicit CTransform(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTransform(const CTransform& rhs, CGameObject* _pOwnerObject);
	virtual ~CTransform();

public:
	const _vec3&			Get_Info		(const INFO& _eInfo) const	{ return m_vInfo[_eInfo]; }
	const _matrix&			Get_WorldMat	() const					{ return m_matWorld; }
	const _vec3&			Get_Scale		() const					{ return m_vScale; }

public:
	void					Rotate			(const DIRID& _eDir , const _float& fSpeed	, const SPACEID _eSpace = LOCAL);

	void					Translate		(const DIRID& _eDir	, const _float& fSpeed	, const SPACEID _eSpace = LOCAL); 
	void					Translate		(const _vec3& _vDir	, const _float& fSpeed);

	void					Set_Pos			(const _vec3& _vPos);								
	void					Set_Rot			(const _vec3& _vRot, const SPACEID _eSpace = LOCAL);
	void					Set_Scale		(const _vec3& _vPos);

public:
	HRESULT					Ready_Transform	();
	virtual _int			Update_Component(const _float& fTimeDelta);

private:
	void					Cal_WorldMat	(); 

private:
	_vec3					m_vInfo[INFO_END];	// �ܺο��� ���� Ʈ������ ������ �˰� ���� �� (���� ���⺤��, ���� ������)
	_matrix					m_matWorld;			// ���� ���� ��Ʈ����
	
	_quat					m_quatQ;		
	_vec3					m_vScale;		
	_vec3					m_vAngle;		

public:
	static CTransform*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*		Clone(CGameObject* _pOwnerObject);

private:
	virtual void			Free();

	friend class CCollisionMgr;

	friend class CRectCollider;
	friend class CCircleCollider;
	friend class CLineCollider;
};

END