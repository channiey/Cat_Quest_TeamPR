#pragma once

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)


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
	// ���� ����
	void					FindFileList(const wstring& folderPath, vector<wstring>& fileList); // ���� ���
	string					wstring_to_utf8(const std::wstring& str); // ���ڿ� Ÿ�� ��ȯ
	LPDIRECT3DTEXTURE9      LoadImageFile(const char* filePath); // �̹��� ����.

	// ���̾ƿ� ����
	void    Show_Arrangement(); // ��ġ ������ ��ҵ� �����ϴ� �Ŵ��� ���̾ƿ�
	void	Show_Arg_Tile(); // Tile ���̾ƿ�
	void	Show_Arg_Obj(); // Obj ���̾ƿ�

	void	Show_Line(); // �� ���̾ƿ�

	void	Show_ImageButton(); // ���Ͽ� �´� ������ �̹����� �ҷ����� ���� �Լ�.

private:
	LPDIRECT3DDEVICE9		m_pGraphicDev;
	bool m_bEnabled;

	ARG_TAG	 m_eArgTag; // ��ġ ���̾ƿ����� ���� ���õ� ��
	int		 m_iTileType; // ���õ� ���� �з�

	// ���� ��� ����.
	wstring		    folderPath; // ���� ���.
	wstring		    tempPath; // ���� ��� �ӽ� ����.
	vector<wstring> fileList; // ���� ������ ���� ����Ʈ

	int				iSelect; // ���õ� ���ε���.

	// �̹��� �ݺ� ��� ���� �õ� ����.
	int					   iImgCount = 0;
	bool				   bLoadFile = true;

private:
	virtual void				Free();
};


