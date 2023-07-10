#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum class SCENE_TYPE			{ INTRO, LOADING, WORLD, ENDING, TOOL, TYPEEND }; // �� ����

	enum class OBJ_TYPE				{ PLAYER, MONSTER, NPC, ITEM, PROJECTILE, CAMERA, LINE, 
									  ENVIRONMENT, TERRAIN, BACKGROUND, EFFECT, UI, TYPEEND }; // ������Ʈ Ÿ��

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
									BACK_IDLE, BACK_WALK, BACK_ROLL, BACK_ATTACK, BACK_ATTACK1, BACK_ATTACK2, DEAD, PATROL, CHASE, BACK, TYPEEND }; // ���ϴ� ���� ������ �߰�

	enum class UI_TYPE				{ VIEW , WORLD , TYPEEND }; // UI ���� (����Ʈ ���, ���� ���)

	enum class LINE_TYPE			{ LAND, SEA, ICE, TYPEEND }; // ���� ����

	enum ARG_TAG { ARG_TILE, ARG_OBJ, ARG_END }; // IMGUI ���̾ƿ� �� �з�

	enum TILE_TAG {TILE_GRASS_FIELD, TILE_WATER_FIELD, TILE_ICE_FIELD, TILE_ICE_DUNGEON, TILE_STONE_DUNGEON, 
		TILE_STONE_DUNGEON2, TILE_TEMPLE_DUNGEON, TILE_SMITH, TILE_END }; 	// IMGUI Ÿ�� ���� ��� �ҷ����� ���� Ÿ�� ���� �з�

	enum OBJ_TAG { OBJ_BUILDING, OBJ_CHEST, OBJ_ENVIRONMENT, 
		OBJ_MAGESHOP, OBJ_SMITHHOUSE, OBJ_TOWER, OBJ_OTHER }; // IMGUI ������Ʈ ���� ��� �ҷ����� ���� Ÿ�� ���� �з�


	enum WINMODE					{ MODE_FULL	, MODE_WIN };
	
	enum COMPONENTID				{ ID_DYNAMIC, ID_STATIC, ID_END };		
	
	enum INFO						{ INFO_RIGHT, INFO_UP, INFO_LOOK, INFO_POS,	INFO_END }; 
	
	enum ROTATION					{ ROT_X, ROT_Y, ROT_Z, ROT_END };
	
	enum DIRID						{ DIR_RIGHT, DIR_UP, DIR_FORWARD, DIR_END };
	
	enum TEXTUREID					{ TEX_NORMAL, TEX_CUBE,	TEX_END };		// �ش� �ؽ�ó�� �Ϲ� �븻 �ؽ�ó���� ť�� �ؽ�ó����
	
	enum MOUSEKEYSTATE				{ DIM_LB, DIM_RB, DIM_MB, DIM_END };	// ���콺 ��ư Ÿ��

	enum MOUSEMOVESTATE				{ DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };	// ���콺 ��ǥ Ÿ��, z�� ��ũ��

	enum PROJECTID					{ ORTHOGRAPHIC, PERSPECTIVE, PROJECT_END};

	enum SPACEID					{ LOCAL, WORLD, SPACE_END };

	enum RENDERID					{ RENDER_PRIORITY, RENDER_NONALPHA, RENDER_ALPHA, RENDER_VIEWUI, RENDER_WDUI, RENDER_END };	// ����� ��ġ�� ���� ���� �׷�������, ���Ŀ��� ���̴��� ���� �Ӽ����ε� ������ �ȴ�.
}
#endif // Engine_Enum_h__
