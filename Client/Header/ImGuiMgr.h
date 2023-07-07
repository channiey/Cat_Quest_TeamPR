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


public: /* MainApp에서 돌아가야 할 기본적인 함수들 */
	HRESULT						ImGui_SetUp(LPDIRECT3DDEVICE9 pGraphicDev);
	void						ImGui_Update();
	void						ImGui_Render();

public:
	// 파일 관련
	void					FindFileList(const wstring& folderPath, vector<wstring>& fileList); // 파일 경로
	string					wstring_to_utf8(const std::wstring& str); // 문자열 타입 변환
	LPDIRECT3DTEXTURE9      LoadImageFile(const char* filePath); // 이미지 설정.

	// 레이아웃 관련
	void    Show_Arrangement(); // 배치 가능한 요소들 관리하는 매니저 레이아웃
	void	Show_Arg_Tile(); // Tile 레이아웃
	void	Show_Arg_Obj(); // Obj 레이아웃

	void	Show_Line(); // 선 레이아웃

	void	Show_ImageButton(); // 파일에 맞는 각각의 이미지를 불러오기 위한 함수.

private:
	LPDIRECT3DDEVICE9		m_pGraphicDev;
	bool m_bEnabled;

	ARG_TAG	 m_eArgTag; // 배치 레이아웃에서 현재 선택된 탭
	int		 m_iTileType; // 선택된 하위 분류

	// 파일 경로 관련.
	wstring		    folderPath; // 폴더 경로.
	wstring		    tempPath; // 저장 경로 임시 저장.
	vector<wstring> fileList; // 파일 정보를 담을 리스트

	int				iSelect; // 선택된 셀인덱스.

	// 이미지 반복 출력 방지 시도 변수.
	int					   iImgCount = 0;
	bool				   bLoadFile = true;

private:
	virtual void				Free();
};


