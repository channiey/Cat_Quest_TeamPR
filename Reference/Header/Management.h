#pragma once

#include "Engine_Define.h"
#include "Base.h"
#include "Scene.h"


BEGIN(Engine)

class ENGINE_DLL CManagement : public CBase
{
	DECLARE_SINGLETON(CManagement)

private:
	explicit CManagement();
	virtual ~CManagement();

#pragma region Access Methods

public:
	CScene*				Get_Scene		() const { return m_pScene; }

	CLayer*				Get_Layer		(const OBJ_TYPE& _eType);

	CGameObject*		Get_GameObject	(const OBJ_TYPE& _eObjType, 
											const _tchar* pObjTag);

	CComponent*			Get_Component	(const OBJ_TYPE& _eObjType,
											const _tchar* pObjTag,
											const COMPONENT_TYPE& _eComponentType,
											COMPONENTID eID);

	const PLAY_MODE&	Get_PlayMode	() const { return m_ePlayMode; }
	const GAME_STATUS&	Get_GameStatus	() const { return m_eGameStatus; }


	HRESULT				Set_Scene		(CScene* pScene);

	HRESULT				Change_Scene(const SCENE_TYPE& _eScene_Type) { return S_OK; };

	void				Set_PlayMode	(const PLAY_MODE& _eMode) { m_ePlayMode = _eMode; }
	void				Set_GameStatus  (const GAME_STATUS& _eStatus) {m_eGameStatus = _eStatus; }

	HRESULT				Add_Object		(const OBJ_TYPE& _eObjType,
											const _tchar* _pObjTag, CGameObject* _pObj);

#pragma endregion

public:
	_int				Update_Scene(const _float& fTimeDelta);
	void				LateUpdate_Scene();
	void				Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	CScene*				m_pScene;

	PLAY_MODE			m_ePlayMode;
	GAME_STATUS			m_eGameStatus;

public:
	virtual void		Free();
};

END