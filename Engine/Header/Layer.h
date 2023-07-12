#pragma once

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CLayer : public CBase
{
private:
	explicit CLayer();
	virtual ~CLayer();

public:
	CGameObject*						Get_GameObject(const _tchar* pObjTag);

	CComponent*							Get_Component(const _tchar* pObjTag, 
														const COMPONENT_TYPE& _eComponentType, 
														COMPONENTID eID);

	multimap<const _tchar*, CGameObject*>&	Get_ObjectMap() { return m_mapObject; }

public:
	HRESULT								Add_GameObject(const _tchar* pObjTag, CGameObject* pGameObject);

	HRESULT								Delete_GameObject(CGameObject* pGameObject);
	HRESULT								Return_GameObject(CGameObject* pGameObject);

	HRESULT								Ready_Layer();
	_int								Update_Layer(const _float& fTimeDelta);
	void								LateUpdate_Layer();

private:
	multimap<const _tchar*, CGameObject*>	m_mapObject;

public:
	static CLayer*						Create();
	virtual	void						Free();
};

END