#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum class SCENE_TYPE			{ INTRO, LOADING, WORLD, ENDING, TOOL, TYPEEND }; // �� ����

	enum class OBJ_TYPE				{ PLAYER, MONSTER, NPC, ITEM, PROJECTILE, CAMERA, 
									  ENVIORMENT, TERRAIN, BACKGROUND, UI, EFFECT, TYPEEND }; // ������Ʈ Ÿ��

	enum class COMPONENT_TYPE		{ TRANSFORM, COL_RECT, COL_CIRCLE, COL_LINE, ANIMATOR, STATEMACHINE,
										BUFFER_RC_TEX, BUFFER_RC_COL, BUFFER_CUBE, BUFFER_TERRAIN_TEX, 
										TEXTURE, CAMERA, TYPEEND }; // ������Ʈ ����

	enum class EVENT_TYPE			{ ADD_OBJ, DELETE_OBJ, RETURN_OBJ, CHANGE_SCENE, TYPEEND }; // �̺�Ʈ Ÿ�� (�̺�Ʈ �Ŵ���)

	enum class COL_TYPE				{ RECT, CIRCLE, LINE, TYPEEND }; // �ݶ��̴� ����, �浹 ����

	enum class TILE_TYPE			{ LAND, SEA, ICE, TYPEEND }; // Ÿ�� ����

	enum class LOADING_THREAD_TYPE	{ TOOL, STAGE, BOSS, TYPEEND };// �ε� ������ ����(�ΰ� ���� ������ ��κ��� ���� ����)

	enum class PLAY_MODE			{ GAME, TOOL, TYPEEND }; // �÷��� ��� (������ ��� ���Ǽ� Ȯ�� ����)

	enum class GAME_STATUS			{ PLAYING, PAUSE, END }; // ���� ������ ���¸� ��Ÿ����.

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

	enum RENDERID					{ RENDER_PRIORITY, RENDER_NONALPHA, RENDER_ALPHA, RENDER_UI, RENDER_END };	// ����� ��ġ�� ���� ���� �׷�������, ���Ŀ��� ���̴��� ���� �Ӽ����ε� ������ �ȴ�.

}
#endif // Engine_Enum_h__
