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
	// ��� ���� ����̶� �θ𿡼� ����
	void					Play_ColLogic(const _float& fTimeDelta); // �浹 ����

public:
	CTexture*				Get_Texture() { return m_pTextureCom; }

	// ����Ʈ�� �� �غ�
	_bool					Get_IsReadyQuest() { return m_bReadyQuest; }
	void					Set_IsReadyQuest(_bool _isReady) { m_bReadyQuest = _isReady; }
	// npc�� ������ �ִ� ����Ʈ 
	CQuest*				    Get_HaveQuest() {return m_pHaveQuest[m_iQuestNum];}
	// ������ �ִ� ����Ʈ�� ���� ����Ʈ�� �ѱ��.
	void					Set_NextQuest() { m_iQuestNum += 1; }



private:
	HRESULT					Add_Component();

protected:
	CTexture*	m_pTextureCom = nullptr; 
	CAnimation* m_pAnimation;

	vector<CQuest*>		m_pHaveQuest;  // ������ ���� ����Ʈ
	_int				m_iQuestNum;   // ����Ʈ �ѹ�.
	_bool				m_bReadyQuest; // ����Ʈ�� �� �غ� �Ǿ��ֳ�.

protected:
	virtual void			Free() override;

};

