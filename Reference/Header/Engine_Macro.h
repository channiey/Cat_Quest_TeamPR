#ifndef Engine_Macro_h__
#define Engine_Macro_h__

#include <iostream>

namespace Engine
{
#define	VK_MAX				0xff

#define	MIN_STR				64
#define	MAX_STR				256

#define	MAX_GROUP			32

#define NPC_IDLE_FRAME      8

#define HITCOLOR_A					255
#define HITCOLOR_R					255
#define HITCOLOR_G					120
#define HITCOLOR_B					120

	/*--------------------- ! (점선 안의 내용) 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

#define	DF_CAMERA_SHAKE_INTENSITY	20.f
#define	DF_CAMERA_SHAKE_TIME		0.13f

#define	DF_RB_KNOCKBACK				10000.f
#define DF_RB_KNOCKUP				100.f

#define	WINCX						1280
#define	WINCY						720

#define CAM_DEFAULT_DISTANCE		23.f

#define	VTXCNTX						65
#define VTXCNTZ						65
#define VTXITV						3

	/*-------------------------------------------------------------------------------*/

#define SCREEN_MSG(_message, _rc) CGraphicDev::GetInstance()->Get_Font()->\
										DrawText(NULL, _message, lstrlen(_message), &_rc,\
										DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(150, 255, 255, 255));\
										rc.top += 20;

#define	CONSOLE_OUT_VEC3(_msg, _vPos) std::cout << _msg << "\t" << _vPos.x << "\t" << _vPos.y << "\t" << _vPos.z << std::endl;

#ifndef	MSG_BOX
#define	MSG_BOX(_message)	MessageBox(NULL, TEXT(_message), L"System Message", MB_OK)
#endif

#define	BEGIN(NAMESPACE)	namespace NAMESPACE {
#define	END					}

#define	USING(NAMESPACE)	using namespace NAMESPACE;

#ifdef	ENGINE_EXPORTS
#define ENGINE_DLL			_declspec(dllexport)
#else
#define ENGINE_DLL			_declspec(dllimport)
#endif

#define NULL_CHECK( _ptr)	\
	{if( _ptr == 0){ return;}}

#define NULL_CHECK_RETURN( _ptr, _return)	\
	{if( _ptr == 0){return _return;}}

#define NULL_CHECK_MSG( _ptr, _message )		\
	{if( _ptr == 0){MessageBox(NULL, _message, L"System Message",MB_OK);}}

#define NULL_CHECK_RETURN_MSG( _ptr, _return, _message )	\
	{if( _ptr == 0){MessageBox(NULL, _message, L"System Message",MB_OK);return _return;}}


#define FAILED_CHECK(_hr)	if( ((HRESULT)(_hr)) < 0 )	\
	{ MessageBoxW(NULL, L"Failed", L"System Error",MB_OK); return E_FAIL;}

#define FAILED_CHECK_RETURN(_hr, _return)	if( ((HRESULT)(_hr)) < 0 )		\
	{ MessageBoxW(NULL, L"Failed", L"System Error",MB_OK); return _return;}

#define FAILED_CHECK_MSG( _hr, _message)	if( ((HRESULT)(_hr)) < 0 )	\
	{ MessageBoxW(NULL, _message, L"System Message",MB_OK); return E_FAIL;}

#define FAILED_CHECK_RETURN_MSG( _hr, _return, _message)	if( ((HRESULT)(_hr)) < 0 )	\
	{ MessageBoxW(NULL, _message, L"System Message",MB_OK); return _return;}



#define NO_COPY(CLASSNAME)								\
		private:										\
		CLASSNAME(const CLASSNAME&);					\
		CLASSNAME& operator = (const CLASSNAME&);		

#define DECLARE_SINGLETON(CLASSNAME)					\
		NO_COPY(CLASSNAME)								\
		private:										\
		static CLASSNAME*	m_pInstance;				\
		public:											\
		static CLASSNAME*	GetInstance( void );		\
		static void DestroyInstance( void );			

#define IMPLEMENT_SINGLETON(CLASSNAME)					\
		CLASSNAME*	CLASSNAME::m_pInstance = NULL;		\
		CLASSNAME*	CLASSNAME::GetInstance( void )	{	\
			if(NULL == m_pInstance) {					\
				m_pInstance = new CLASSNAME;			\
			}											\
			return m_pInstance;							\
		}												\
		void CLASSNAME::DestroyInstance( void ) {		\
			if(NULL != m_pInstance)	{					\
				delete m_pInstance;						\
				m_pInstance = NULL;						\
			}											\
		}
}

#endif // Engine_Macro_h__
