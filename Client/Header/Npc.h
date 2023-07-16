#pragma once

#include "GameObject.h"
#include "Quest.h"
BEGIN(Engine)
class CTexture;
class CAnimation;
class CRcTex;
END

class CNpc : public Engine::CGameObject
{
protected:
	explicit CNpc(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CNpc(const CNpc& rhs);
	virtual ~CNpc();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	// 모두 같은 기능이라 부모에서 통일
	void					Play_ColLogic(const _float& fTimeDelta); // 충돌 로직

public:
	CTexture*				Get_Texture() { return m_pTextureCom; }

	// 퀘스트를 줄 준비
	_bool					Get_IsReadyQuest() { return m_bReadyQuest; }
	void					Set_IsReadyQuest(_bool _isReady) { m_bReadyQuest = _isReady; }
	// npc가 가지고 있는 퀘스트 
	CQuest*				    Get_HaveQuest() {return m_pHaveQuest[m_iQuestNum];}
	// 가지고 있는 퀘스트를 다음 퀘스트로 넘긴다.
	void					Set_NextQuest() { m_iQuestNum += 1; }



private:
	HRESULT					Add_Component();

protected:
	CTexture*	m_pTextureCom = nullptr; 
	CAnimation* m_pAnimation;

	vector<CQuest*>		m_pHaveQuest;  // 가지고 있을 퀘스트
	_int				m_iQuestNum;   // 퀘스트 넘버.
	_bool				m_bReadyQuest; // 퀘스트를 줄 준비가 되어있나.

protected:
	virtual void			Free() override;

};

