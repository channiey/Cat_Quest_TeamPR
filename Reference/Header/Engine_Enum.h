#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum class SCENE_TYPE			{ INTRO, LOADING, WORLD, ENDING, TOOL, TYPEEND }; // 씬 종류

	enum class OBJ_TYPE				{ PLAYER, MONSTER, NPC, ITEM, PROJECTILE, CAMERA, LINE, 
									  ENVIRONMENT, TERRAIN, BACKGROUND, EFFECT, UI, TYPEEND }; // 오브젝트 타입

	enum class OBJ_ID			
	{


		/* ========================================= Terrain ========================================*/


		// Terrain
		TERRAIN_WORLD, TERRAIN_DUNGEON, TERRAIN_ICEWORLD, TERRAIN_TOOL,
	



		/* ========================================= Environment ========================================*/


		// Environment - Chest
		ENVIRONMENT_CHEST_COSMETIC, ENVIRONMENT_CHEST_GOLD, ENVIRONMENT_CHEST__REGULAR,
		
		// Environment - Building - House
		ENVIRONMENT_BUILDING_HOUSE_1, ENVIRONMENT_BUILDING_HOUSE_2, ENVIRONMENT_BUILDING_HOUSE_3, 
		ENVIRONMENT_BUILDING_HOUSE_4, ENVIRONMENT_BUILDING_HOUSE_5, ENVIRONMENT_BUILDING_HOUSE_6, 
		ENVIRONMENT_BUILDING_KINGHOUSE,
		
		// Environment - Building - Tower
		ENVIRONMENT_BUILDING_TOWER_1, ENVIRONMENT_BUILDING_TOWER_2, ENVIRONMENT_BUILDING_TOWER_3,
		
		// Environment - Natural - Bush
		ENVIRONMENT_NATURAL_BUSH_1, ENVIRONMENT_NATURAL_BUSH_2, ENVIRONMENT_NATURAL_BUSH_3, 
		ENVIRONMENT_NATURAL_BUSH_4, ENVIRONMENT_NATURAL_BUSH_5, ENVIRONMENT_NATURAL_BUSH_6, 
		ENVIRONMENT_NATURAL_BUSH_7, ENVIRONMENT_NATURAL_BUSH_8, ENVIRONMENT_NATURAL_BUSH_9, 
		ENVIRONMENT_NATURAL_BUSH_10, ENVIRONMENT_NATURAL_BUSH_11,

		// Environment - Natural - Mountain
		ENVIRONMENT_NATURAL_MOUNTAIN_GRASS, ENVIRONMENT_NATURAL_MOUNTAIN_ICE,

		// Environment - Natural - Pillar
		ENVIRONMENT_NATURAL_PILLAR_ICE, ENVIRONMENT_NATURAL_PILLAR_ROCK_1, ENVIRONMENT_NATURAL_PILLAR_ROCK_2, 
		ENVIRONMENT_NATURAL_PILLAR_ROCK_3, ENVIRONMENT_NATURAL_PILLAR_TEMPLE_1, ENVIRONMENT_NATURAL_PILLAR_TEMPLE_2,

		// Environment - Natural - Rock
		ENVIRONMENT_NATURAL_ROCK_1, ENVIRONMENT_NATURAL_ROCK_2, ENVIRONMENT_NATURAL_ROCK_3, ENVIRONMENT_NATURAL_ROCK_4,

		// Environment - Enterance
		ENVIRONMENT_ENTERANCE_SMITHY, ENVIRONMENT_ENTERANCE_MAGICSHOP, 
		ENVIRONMENT_ENTERANCE_DUNGEON_GRASS, ENVIRONMENT_ENTERANCE_DUNGEON_ICE, ENVIRONMENT_ENTERANCE_DUNGEON_TEMPLE,




		/* ========================================= Monster ========================================*/


		// Monster
		MONSTER_HEDGEHOG, MONSTER_DRAGON, MONSTER_BAT, MONSTER_RAM, MONSTER_FOX, MONSTER_SQUIRREL, MONSTER_WYVERN,




		/* ========================================= Npc ========================================*/


		// Npc
		NPC_BLACKSMITH, NPC_CITIZEN_1, NPC_CITIZEN_2, NPC_KING, NPC_MAGE, NPC_SOLLIDER,




		/* ========================================= Item ========================================*/


		// Item




		/* ========================================= Line ========================================*/


		// Line
		LINE,




		/* ========================================= Light ========================================*/


		// Light




		/* ========================================= Effect ========================================*/


		// Cloud
		EFFECT_CLOUD_1, EFFECT_CLOUD_2, EFFECT_CLOUD_3,



		/* ========================================= BackGround ========================================*/


		// BackGround
		BACKGROUND,




		/* ========================================= UI ========================================*/


		// UI - WORLD
		// 
		// UI - VIEWPORT
		UI_ENTER, UI_EXP, UI_LEVEL, UI_TAB, UI_ZOOM, UI_DEF, UI_HP, UI_MANA, UI_RING, UI_INDICATOR,




		/* ========================================= CAMERA ========================================*/


		// CAMERA
		CAMERA_PLAYER, CAMERA_TOOL, CAMERA_TARGET_OBJ,




		/* ========================================= PLAYER ========================================*/


		PLAYER,


		TYPEEND

	};
	
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
									BACK_IDLE, BACK_WALK, BACK_ROLL, BACK_ATTACK, BACK_ATTACK1, BACK_ATTACK2, DEAD, 
									PATROL, CHASE, COMEBACK, MONATTACK, BACK_PATROL, BACK_CHASE, BACK_COMEBACK, BACK_MONATTACK, TYPEEND }; // 원하는 상태 있으면 추가

	enum class UI_TYPE				{ VIEW , WORLD , TYPEEND }; // UI 종류 (뷰포트 사용, 월드 사용)

	enum class LINE_TYPE			{ LAND, SEA, ICE, TYPEEND }; // 라인 종류
	
	enum class EFFECT_TYPE			{ SKILL, TYPEEND };

	enum class ENTER_TYPE			{ ENTER, ENTER_NO, TYPEEND};

	enum class INTERACTION_TYPE		{ INTERACTION_ALPHA, INTERACTION_ENTER,
		INTERACTION_INSPECT, INTERACTION_CHAT, TYPEEND };

	enum class UIENTER_TYPE			{ ENTER, INSPECT, CATNAP, BUY, CHAT, TYPEEND };

	enum ARG_TAG { ARG_TERRAIN, ARG_OBJ, ARG_END }; // IMGUI 레이아웃 탭 분류

	enum TERRIAN_TAG {TERRAIN_WORLD, TERRAIN_TEMP, TERRAIN_DUNGEON_ICE, TERRAIN_END }; 	// IMGUI 터레인 저장을 위한 분류

	enum OBJ_TAG { OBJ_BUILDING, OBJ_CHEST, OBJ_ENVIRONMENT, 
		OBJ_MAGESHOP, OBJ_SMITHHOUSE, OBJ_TOWER, OBJ_OTHER }; // IMGUI 오브젝트 폴더 경로 불러오기 위한 타일 종류 분류


	enum WINMODE					{ MODE_FULL	, MODE_WIN };
	
	enum COMPONENTID				{ ID_DYNAMIC, ID_STATIC, ID_END };		
	
	enum INFO						{ INFO_RIGHT, INFO_UP, INFO_LOOK, INFO_POS,	INFO_END }; 
	
	enum ROTATION					{ ROT_X, ROT_Y, ROT_Z, ROT_END };
	
	enum DIRID						{ DIR_RIGHT, DIR_UP, DIR_FORWARD, DIR_DOWN,  DIR_END };
	
	enum TEXTUREID					{ TEX_NORMAL, TEX_CUBE,	TEX_END };		// 해당 텍스처가 일반 노말 텍스처인지 큐브 텍스처인지
	
	enum MOUSEKEYSTATE				{ DIM_LB, DIM_RB, DIM_MB, DIM_END };	// 마우스 버튼 타입

	enum MOUSEMOVESTATE				{ DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };	// 마우스 좌표 타입, z는 스크롤

	enum PROJECTID					{ ORTHOGRAPHIC, PERSPECTIVE, PROJECT_END};

	enum SPACEID					{ LOCAL, WORLD, SPACE_END };

	enum RENDERID					{ RENDER_PRIORITY, RENDER_NONALPHA, RENDER_ALPHA, RENDER_VIEWUI, RENDER_WDUI, RENDER_END };	// 현재는 장치를 통한 렌더 그룹이지만, 이후에는 셰이더에 대한 속성으로도 나뉘게 된다.
}
#endif // Engine_Enum_h__
