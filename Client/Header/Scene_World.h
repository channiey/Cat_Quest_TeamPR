#pragma once

#include "Scene.h"

class CScene_World : public Engine::CScene
{
private:
	explicit CScene_World(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene_World();

public:
	virtual HRESULT		Ready_Scene() override;
	virtual _int		Update_Scene(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Scene() override;
	virtual void		Render_Scene() override;

private:

	HRESULT				Ready_Load();

	HRESULT				Ready_Layer_Camera(); // Ŭ��
	HRESULT				Ready_Layer_UI(); // Ŭ��
	HRESULT				Ready_Layer_Player(); // Ŭ��
	HRESULT				Ready_Layer_Effect(); // Ŭ��
	HRESULT				Ready_Layer_Etc(); // Ŭ��

	HRESULT				Ready_Layer_Terrain(); // ���̾� ���� ���� ���ΰ� ���� ����
	HRESULT				Ready_Layer_Environment	(); // ���̾� ���� ���� ���ΰ� ���� ����
	HRESULT				Ready_Layer_Npc(); // ���̾� ���� ���� ���ΰ� ���� ����
	HRESULT				Ready_Layer_Monster();  // ���̾� ���� ���� ���ΰ� ���� ����
	HRESULT				Ready_Layer_Item(); // ���̾� ���� ���� ���ΰ� ���� ����

	HRESULT				Ready_Layer_KSH(); // ���� �׽�Ʈ�� �߰�
	HRESULT				Ready_Layer_KJM(); // ���� �׽�Ʈ�� �߰�
	HRESULT				Ready_Layer_LHJ(); // ���� �׽�Ʈ�� �߰�
	HRESULT				Ready_Layer_YC(); // ���� �׽�Ʈ�� �߰�

public:
	static CScene_World*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free() override;
};

