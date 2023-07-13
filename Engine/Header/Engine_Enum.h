#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum class SCENE_TYPE			{ INTRO, LOADING, WORLD, ENDING, TOOL, TYPEEND }; // �� ����

	enum class OBJ_TYPE				{ PLAYER, MONSTER, NPC, ITEM, PROJECTILE, CAMERA, LINE, 
									  ENVIRONMENT, TERRAIN, BACKGROUND, EFFECT, UI, TYPEEND }; // ������Ʈ Ÿ��

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
										TEXTURE, CAMERA, AICOM, TYPEEND }; // ������Ʈ ����


	enum class EVENT_TYPE			{ ADD_OBJ, DELETE_OBJ, RETURN_OBJ, CHANGE_SCENE, TYPEEND }; // �̺�Ʈ Ÿ�� (�̺�Ʈ �Ŵ���)

	enum class COL_TYPE				{ RECT, CIRCLE, LINE, TYPEEND }; // �ݶ��̴� ����, �浹 ����

	enum class TILE_TYPE			{ LAND, SEA, ICE, TYPEEND }; // Ÿ�� ����

	enum class LOADING_THREAD_TYPE	{ TOOL, STAGE, BOSS, TYPEEND };// �ε� ������ ����(�ΰ� ���� ������ ��κ��� ���� ����)

	enum class PLAY_MODE			{ GAME, TOOL, TYPEEND }; // �÷��� ��� (������ ��� ���Ǽ� Ȯ�� ����)

	enum class GAME_STATUS			{ PLAYING, PAUSE, END }; // ���� ������ ���¸� ��Ÿ����.

	enum class STATE_TYPE			{ FRONT_IDLE, FRONT_WALK, FRONT_ROLL, FRONT_ATTACK, FRONT_ATTACK1, FRONT_ATTACK2, FRONT_HIT,
									BACK_IDLE, BACK_WALK, BACK_ROLL, BACK_ATTACK, BACK_ATTACK1, BACK_ATTACK2, DEAD, 
									PATROL, CHASE, COMEBACK, MONATTACK, BACK_PATROL, BACK_CHASE, BACK_COMEBACK, BACK_MONATTACK, TYPEEND }; // ���ϴ� ���� ������ �߰�

	enum class UI_TYPE				{ VIEW , WORLD , TYPEEND }; // UI ���� (����Ʈ ���, ���� ���)

	enum class LINE_TYPE			{ LAND, SEA, ICE, TYPEEND }; // ���� ����
	
	enum class EFFECT_TYPE			{ SKILL, TYPEEND };

	enum class ENTER_TYPE			{ ENTER, ENTER_NO, TYPEEND};

	enum class INTERACTION_TYPE		{ INTERACTION_ALPHA, INTERACTION_ENTER,
		INTERACTION_INSPECT, INTERACTION_CHAT, TYPEEND };

	enum class UIENTER_TYPE			{ ENTER, INSPECT, CATNAP, BUY, CHAT, TYPEEND };

	enum ARG_TAG { ARG_TERRAIN, ARG_OBJ, ARG_END }; // IMGUI ���̾ƿ� �� �з�

	enum TERRIAN_TAG {TERRAIN_WORLD, TERRAIN_TEMP, TERRAIN_DUNGEON_ICE, TERRAIN_END }; 	// IMGUI �ͷ��� ������ ���� �з�

	enum OBJ_TAG { OBJ_BUILDING, OBJ_CHEST, OBJ_ENVIRONMENT, 
		OBJ_MAGESHOP, OBJ_SMITHHOUSE, OBJ_TOWER, OBJ_OTHER }; // IMGUI ������Ʈ ���� ��� �ҷ����� ���� Ÿ�� ���� �з�


	enum WINMODE					{ MODE_FULL	, MODE_WIN };
	
	enum COMPONENTID				{ ID_DYNAMIC, ID_STATIC, ID_END };		
	
	enum INFO						{ INFO_RIGHT, INFO_UP, INFO_LOOK, INFO_POS,	INFO_END }; 
	
	enum ROTATION					{ ROT_X, ROT_Y, ROT_Z, ROT_END };
	
	enum DIRID						{ DIR_RIGHT, DIR_UP, DIR_FORWARD, DIR_DOWN,  DIR_END };
	
	enum TEXTUREID					{ TEX_NORMAL, TEX_CUBE,	TEX_END };		// �ش� �ؽ�ó�� �Ϲ� �븻 �ؽ�ó���� ť�� �ؽ�ó����
	
	enum MOUSEKEYSTATE				{ DIM_LB, DIM_RB, DIM_MB, DIM_END };	// ���콺 ��ư Ÿ��

	enum MOUSEMOVESTATE				{ DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };	// ���콺 ��ǥ Ÿ��, z�� ��ũ��

	enum PROJECTID					{ ORTHOGRAPHIC, PERSPECTIVE, PROJECT_END};

	enum SPACEID					{ LOCAL, WORLD, SPACE_END };

	enum RENDERID					{ RENDER_PRIORITY, RENDER_NONALPHA, RENDER_ALPHA, RENDER_VIEWUI, RENDER_WDUI, RENDER_END };	// ����� ��ġ�� ���� ���� �׷�������, ���Ŀ��� ���̴��� ���� �Ӽ����ε� ������ �ȴ�.
}
#endif // Engine_Enum_h__
