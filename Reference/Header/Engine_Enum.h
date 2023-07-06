#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum class SCENE_TYPE			{ INTRO, LOADING, WORLD, ENDING, TOOL, TYPEEND }; // 씬 종류

	enum class OBJ_TYPE				{ PLAYER, MONSTER, NPC, ITEM, PROJECTILE, CAMERA, 
									  ENVIORMENT, TERRAIN, BACKGROUND, UI, EFFECT, TYPEEND }; // 오브젝트 타입

	enum class COMPONENT_TYPE		{ TRANSFORM, COL_RECT, COL_CIRCLE, COL_LINE, ANIMATOR, STATEMACHINE,
										BUFFER_RC_TEX, BUFFER_RC_COL, BUFFER_CUBE, BUFFER_TERRAIN_TEX, 
										TEXTURE, CAMERA, TYPEEND }; // 컴포넌트 종류

	enum class EVENT_TYPE			{ ADD_OBJ, DELETE_OBJ, RETURN_OBJ, CHANGE_SCENE, TYPEEND }; // 이벤트 타입 (이벤트 매니저)

	enum class COL_TYPE				{ RECT, CIRCLE, LINE, TYPEEND }; // 콜라이더 종류, 충돌 종류

	enum class TILE_TYPE			{ LAND, SEA, ICE, TYPEEND }; // 타일 종류

	enum class LOADING_THREAD_TYPE	{ TOOL, STAGE, BOSS, TYPEEND };// 로딩 쓰레드 종류(로고 씬을 제외한 대부분의 씬이 보유)

	enum class PLAY_MODE			{ GAME, TOOL, TYPEEND }; // 플레이 모드 (개발자 모드 편의성 확보 목적)

	enum class GAME_STATUS			{ PLAYING, PAUSE, END }; // 현재 게임의 상태를 나타낸다.

	enum WINMODE					{ MODE_FULL	, MODE_WIN };
	
	enum COMPONENTID				{ ID_DYNAMIC, ID_STATIC, ID_END };		
	
	enum INFO						{ INFO_RIGHT, INFO_UP, INFO_LOOK, INFO_POS,	INFO_END }; 
	
	enum ROTATION					{ ROT_X, ROT_Y, ROT_Z, ROT_END };
	
	enum DIRID						{ DIR_RIGHT, DIR_UP, DIR_FORWARD, DIR_END };
	
	enum TEXTUREID					{ TEX_NORMAL, TEX_CUBE,	TEX_END };		// 해당 텍스처가 일반 노말 텍스처인지 큐브 텍스처인지
	
	enum MOUSEKEYSTATE				{ DIM_LB, DIM_RB, DIM_MB, DIM_END };	// 마우스 버튼 타입

	enum MOUSEMOVESTATE				{ DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };	// 마우스 좌표 타입, z는 스크롤

	enum PROJECTID					{ ORTHOGRAPHIC, PERSPECTIVE, PROJECT_END};

	enum SPACEID					{ LOCAL, WORLD, SPACE_END };

	enum RENDERID					{ RENDER_PRIORITY, RENDER_NONALPHA, RENDER_ALPHA, RENDER_UI, RENDER_END };	// 현재는 장치를 통한 렌더 그룹이지만, 이후에는 셰이더에 대한 속성으로도 나뉘게 된다.

}
#endif // Engine_Enum_h__
