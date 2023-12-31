#ifndef InputDev_h__
#define InputDev_h__

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CInputDev : public CBase
{
	DECLARE_SINGLETON(CInputDev)

private:
	explicit CInputDev(void);
	virtual ~CInputDev(void);
	
public:
	// API 때 사용하던 키 인풋 함수
	_bool			Key_Pressing(_int _iKey);
	_bool			Key_Down(_int _iKey);
	_bool			Key_Up(_int _iKey);

	_byte			Get_DIKeyState(_ubyte byKeyID)				{ return m_byKeyState[byKeyID]; }
	_byte			Get_DIMouseState(MOUSEKEYSTATE eMouse) 		{ return m_tMouseState.rgbButtons[eMouse]; 	}
	_long			Get_DIMouseMove(MOUSEMOVESTATE eMouseState)	{ return *(((_long*)&m_tMouseState) + eMouseState); } // 마우스 무브 인풋 사용법
																																/*
							
							if (dwMouse = CInputDev::GetInstance()->Get_DIMouseMove(DIMS_Y))
							{
								// 스크린 좌표계를 기준으로 이전 프레임에서 현재프레임의 마우스 y포지션 차이를 반환한다.
								// 마우스를 올리면 -값, 내리면 +값
							}

							if (dwMouse = CInputDev::GetInstance()->Get_DIMouseMove(DIMS_X))
							{
								// 스크린 좌표계를 기준으로 이전 프레임에서 현재프레임의 마우스 x포지션 차이를 반환한다.
								// 마우스를 오른쪽으로 하면 +값, 왼쪽으로 하면 -값
							}

							if (dwMouse = CInputDev::GetInstance()->Get_DIMouseMove(DIMS_Z))
							{
								// 위로 스크롤 하면 120 반환
								// 아래로 스크롤 하면 -120 반환
							}

							*/

public:
	HRESULT					Ready_InputDev(HINSTANCE hInst, HWND hWnd);
	void					Update_InputDev(void);	// 매 업데이트 마다 인풋 상태를 갱신한다 (Main App에서 호출)

private:
	LPDIRECTINPUT8			m_pInputSDK = nullptr;	// 인풋 장치 SKD

private:
	LPDIRECTINPUTDEVICE8	m_pKeyBoard = nullptr;	// 인풋 컴객체
	LPDIRECTINPUTDEVICE8	m_pMouse	= nullptr;	// 인풋 컴객체

private:
	_byte					m_byKeyState[256];		// 키보드에 있는 모든 키값을 저장하기 위한 변수
	DIMOUSESTATE			m_tMouseState;	

	bool					m_bKeyState[VK_MAX];

public:
	virtual void			Free(void);

};
END
#endif // InputDev_h__
