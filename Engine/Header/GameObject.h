#pragma once

#include "Component.h"


BEGIN(Engine)

class CTransform;
class CCollider;
class CVIBuffer;
class CAnimator;

class ENGINE_DLL CGameObject : public CBase
{
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_TYPE& _eType);
	explicit CGameObject(const CGameObject& rhs);
	virtual ~CGameObject();

public:
	virtual CGameObject* Clone() { return nullptr; }

#pragma region Access Methods

public:
	CComponent*							Get_Component(const COMPONENT_TYPE& _eType, COMPONENTID eID);
	CTransform*							Get_Transform() const { return m_pTransformCom; }
	CCollider*							Get_Collider() const { return m_pColliderCom; }
	CAnimator*							Get_Animator() const { return m_pAnimatorCom; }
	CVIBuffer*							Get_VIBuffer() const { return m_pBufferCom; }
	const _tchar*						Get_Name() const { return m_szName; } // 팀장 허락 받고 사용

	CGameObject*						Get_Parent() const { return m_pParentObj; }
	CGameObject*						Get_Child(const _uint& _iIndex = 0);

	const _float&						Get_ViewZ();  // 알파 출력 오브젝트들의 알파소팅
	void								Set_ViewZ();  // 알파 출력 오브젝트들의 알파소팅
	const OBJ_TYPE						Get_Type() const { return m_eType; }

	void								Set_Parent(CGameObject* const _pParent) { m_pParentObj = _pParent; }
	void								Set_Name(const _tchar* _szName) { m_szName = _szName; } // 팀장 허락 받고 사용
	void								Set_Active(const _bool& _bActive) { m_bActive = _bActive; }

	const _bool&						Is_Active() const { return m_bActive; }
	const _bool							Is_Component(const COMPONENT_TYPE& _eType, COMPONENTID eID);
	
	UI_LAYER							Get_LayerLv() { return m_eUILayer; }

	// 상호작용 및 충돌 시 이벤트 관련
	ENTER_TYPE				Get_EnterType() { return m_eEnter; }
	INTERACTION_TYPE		Get_InterType() { return m_eInterType; }

	void					Set_IsEnter(_bool _switch) { m_bEnter = _switch; }
	void					Set_EventSwitch(_bool _switch) { m_bEventSwitch = _switch; }
#pragma endregion

#pragma region Collision Methods

public:
	virtual void						OnCollision_Enter(CGameObject* _pColObj) {};
	virtual void						OnCollision_Stay(CGameObject* _pColObj) {};
	virtual void						OnCollision_Exit(CGameObject* _pColObj) {};

#pragma endregion

public:
	virtual HRESULT						Ready_Object();
	virtual _int						Update_Object(const _float& fTimeDelta);
	virtual void						LateUpdate_Object();
	virtual void						Render_Object();

private:
	CComponent*							Find_Component(const COMPONENT_TYPE& _eType, COMPONENTID eID);

protected:
	LPDIRECT3DDEVICE9					m_pGraphicDev;

	const _tchar*						m_szName;
	multimap<COMPONENT_TYPE, CComponent*>	m_mapComponent[ID_END];

	CTransform*							m_pTransformCom;	
	CCollider*							m_pColliderCom;
	CVIBuffer*							m_pBufferCom;
	CAnimator*							m_pAnimatorCom;

	CGameObject*						m_pParentObj;
	vector<CGameObject*>				m_vecChilds;
	
	OBJ_TYPE							m_eType;
	_bool								m_bActive;

	_float                              m_fViewZ;// 알파 출력 오브젝트들의 알파소팅

	// UI_Layer
	UI_LAYER							m_eUILayer;

	// 상호작용 및 충돌 시 이벤트 관련
	ENTER_TYPE				m_eEnter;
	INTERACTION_TYPE		m_eInterType;
	_bool					m_bEventSwitch = false;
	_bool					m_bEnter = false;
public:
	virtual void						Free();
};


END