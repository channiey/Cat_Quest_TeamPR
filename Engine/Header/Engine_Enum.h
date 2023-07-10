#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum class SCENE_TYPE			{ INTRO, LOADING, WORLD, ENDING, TOOL, TYPEEND }; // 씬 종류

	enum class OBJ_TYPE				{ PLAYER, MONSTER, NPC, ITEM, PROJECTILE, CAMERA, LINE, 
									  ENVIRONMENT, TERRAIN, BACKGROUND, EFFECT, UI, TYPEEND }; // 오브젝트 타입

	enum class COMPONENT_TYPE		{ TRANSFORM, COL_RECT, COL_CIRCLE, COL_LINE, ANIMATOR, STATEMACHINE,
										BUFFER_RC_TEX, BUFFER_RC_COL, BUFFER_CUBE, BUFFER_TERRAIN_TEX, BUFFER_TERRAIN_RC_TEX,
										TEXTURE, CAMERA, AICOM, TYPEEND }; // 컴포넌트 종류


	enum class EVENT_TYPE			{ ADD_OBJ, DELETE_OBJ, RETURN_OBJ, CHANGE_SCENE, TYPEEND }; // 이벤트 타입 (이벤트 매니저)

	enum class COL_TYPE				{ RECT, CIRCLE, LINE, TYPEEND }; // 콜라이더 종류, 충돌 종류

	enum class TILE_TYPE			{ LAND, SEA, ICE, TYPEEND }; // 타일 종류

	enum class LOADING_THREAD_TYPE	{ TOOL, STAGE, BOSS, TYPEEND };// 로딩 쓰레드 종류(로고 씬을 제외한 대부분의 씬이 보유)

	enum class PLAY_MODE			{ GAME, TOOL, TYPEEND }; // 플레이 모드 (개발자 모드 편의성 확보 목적)

	enum class GAME_STATUS			{ PLAYING, PAUSE, END }; // 현재 게임의 상태를 나타낸다.

	enum class STATE_TYPE			{ FRONT_IDLE, FRONT_WALK, FRONT_ROLL, FRONT_ATTACK, FRONT_ATTACK1, FRONT_ATTACK2, FRONT_HIT,
									BACK_IDLE, BACK_WALK, BACK_ROLL, BACK_ATTACK, BACK_ATTACK1, BACK_ATTACK2, DEAD, PATROL, CHASE, BACK, TYPEEND }; // 원하는 상태 있으면 추가

	enum class UI_TYPE				{ VIEW , WORLD , TYPEEND }; // UI 종류 (뷰포트 사용, 월드 사용)

	enum class LINE_TYPE			{ LAND, SEA, ICE, TYPEEND }; // 라인 종류

	enum ARG_TAG { ARG_TILE, ARG_OBJ, ARG_END }; // IMGUI 레이아웃 탭 분류

	enum TILE_TAG {TILE_GRASS_FIELD, TILE_WATER_FIELD, TILE_ICE_FIELD, TILE_ICE_DUNGEON, TILE_STONE_DUNGEON, 
		TILE_STONE_DUNGEON2, TILE_TEMPLE_DUNGEON, TILE_SMITH, TILE_END }; 	// IMGUI 타일 폴더 경로 불러오기 위한 타일 종류 분류

	enum OBJ_TAG { OBJ_BUILDING, OBJ_CHEST, OBJ_ENVIRONMENT, 
		OBJ_MAGESHOP, OBJ_SMITHHOUSE, OBJ_TOWER, OBJ_OTHER }; // IMGUI 오브젝트 폴더 경로 불러오기 위한 타일 종류 분류


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

	enum RENDERID					{ RENDER_PRIORITY, RENDER_NONALPHA, RENDER_ALPHA, RENDER_VIEWUI, RENDER_WDUI, RENDER_END };	// 현재는 장치를 통한 렌더 그룹이지만, 이후에는 셰이더에 대한 속성으로도 나뉘게 된다.
}
#endif // Engine_Enum_h__
