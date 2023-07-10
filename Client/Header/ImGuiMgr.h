#pragma once

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class CGameObject;

END

class CImGuiMgr : public CBase
{
	DECLARE_SINGLETON(CImGuiMgr)

private:
	explicit CImGuiMgr();
	virtual ~CImGuiMgr();


public: /* MainApp���� ���ư��� �� �⺻���� �Լ��� */
	HRESULT						ImGui_SetUp(LPDIRECT3DDEVICE9 pGraphicDev);
	void						ImGui_Update();
	void						ImGui_Render();

public:
	// �ʹ� ����
	void					Ready_Terrain();
	void					Ready_Environment();

	// ���� ����
	void					FindFileList(const wstring& folderPath, vector<wstring>& m_objFileList); // ���� ���
	string					wstring_to_utf8(const std::wstring& str); // ���ڿ� Ÿ�� ��ȯ
	LPDIRECT3DTEXTURE9      LoadImageFile(const char* filePath); // �̹��� ����.

	// ���̾ƿ� ����
	void    Show_Arrangement(); // ��ġ ������ ��ҵ� �����ϴ� �Ŵ��� ���̾ƿ�
	void	Show_Arg_Terrain(); // Tile ���̾ƿ�
	void	Show_Arg_Obj(); // Obj ���̾ƿ�

	void	Show_Line(); // �� ���̾ƿ�

	void	Show_ImageButton(); // ���Ͽ� �´� ������ �̹����� �ҷ����� ���� �Լ�.

	void    Pick_Create_Object();

private:
	LPDIRECT3DDEVICE9		m_pGraphicDev;
	bool m_bEnabled;

	ARG_TAG	 m_eArgTag; // ��ġ ���̾ƿ����� ���� ���õ� ��
	int      m_iObjType; // ���õ� ���� �з�(������Ʈ)
	int      m_iSelTerrain; // �� �׸��⸦ ���� ���õ� �ͷ��� �����.
	int      m_iSelObj; // ȯ�� ������Ʈ �׸��⸦ ���� ���õ� �ͷ��� �����.

	// ���� ��� ����.
	wstring		    folderPath; // ���� ���.
	wstring		    tempPath; // ���� ��� �ӽ� ����.
	vector<wstring> m_objFileList; // ������Ʈ ���� ������ ���� ����Ʈ
	vector<wstring> m_terFileList; // �ͷ��� ���� ������ ���� ����Ʈ

	// �� �����̳�
	vector<CGameObject*>  m_vecLoadObj; // ������ ������Ʈ�� ���� ����Ʈ
	vector<const _tchar*> m_vecLoadObjImgPath; // ������Ʈ �̹��� ��θ� ���� ����Ʈ
	vector<CGameObject*>  m_vecObj; // ����ؼ� �߰��� �迭

	int				iSelect; // ���õ� ���ε���.

	// �̹��� �ݺ� ��� ���� �õ� ����.
	int					   iImgCount = 0;
	bool				   bLoadFile = true;

	// �ߺ� Ű �� ����
	_int				   m_iAddCount; // ��ü �̸� �ߺ� ����
	_int				   tempCount;
	
private:
	virtual void				Free();
};


