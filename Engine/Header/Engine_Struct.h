#ifndef Engine_Struct_h__
#define Engine_Struct_h__

#include "Engine_Typedef.h"
#include "Engine_Enum.h"

namespace Engine
{

#pragma region UTILITY

	typedef struct tagMyVec3 
	{
		_vec3 up = { 0.f,  1.f,  0.f };
		_vec3 down = { 0.f, -1.f,  0.f };
		_vec3 right = { 1.f,  0.f,  0.f };
		_vec3 left = { -1.f,  0.f,  0.f };
		_vec3 forward = { 0.f,  0.f,  1.f };
		_vec3 back = { 0.f,  0.f, -1.f };
		_vec3 one = { 1.f,  1.f,  1.f };
		_vec3 zero = { 0.f,  0.f,  0.f };

	}MYVEC3;
	static const MYVEC3 vec3; 

	typedef struct tagMyColor
	{
		_color white = { 1.f	,  1.f	,  1.f	, 1.f };
		_color black = { 0.f	,  0.f	,  0.f	, 1.f };
		_color red = { 1.f	,  0.f	,  0.f	, 1.f };
		_color green = { 0.f	,  1.f	,  0.f	, 1.f };
		_color blue = { 0.f	,  0.f	,  1.f	, 1.f };
		_color pruple = { 1.f	,  0.f	,  1.f	, 1.f };
		_color gray = { 0.5f,  0.5f	,  0.5f	, 1.f };
		_color orange = { 1.f	,  0.5f	,  0.f	, 1.f };
		_color yellow = { 1.0f,  1.f	,  0.f	, 1.f };

	}MYCOLOR;
	static const MYCOLOR color;

	typedef struct tagMyMat
	{
		void	Set_Material(_mtr& _material, _color _color)
		{
			_material.Ambient = _color;
			_material.Diffuse = _color;
			_material.Specular = _color;
			_material.Emissive = _color;
			_material.Power = 100.0f;
		}

		const _mtr Get_Meretial(_color _color)
		{
			_mtr mat;

			mat.Ambient = _color;
			mat.Diffuse = _color;
			mat.Specular = _color;
			mat.Emissive = _color;
			mat.Power = 100.0f;

			return mat;
		}

		_mtr m;

	}MYMATERIAL;
	static MYMATERIAL material;

#pragma endregion

#pragma region VTX, IDX

	typedef struct tagVertexColor
	{
		_vec3		vPosition;		
		_ulong		dwColor;

	}VTXCOL;
	const _ulong	FVF_COL = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0; // D3DFVF_TEX0 = 텍스처를 사용하지 않는다.


	typedef struct tagVertexTexture
	{
		_vec3		vPosition;
		_vec2		vTexUV;												//UV 좌표계 (좌표 값이 0 ~ 1)

	}VTXTEX;
	const _ulong	FVF_TEX = D3DFVF_XYZ | D3DFVF_TEX1;					// D3DFVF_TEX1 = 각 꼭짓점에는 하나의 텍스처 좌표 집합이 있습니다.

	typedef struct tagVertexCubeTexture
	{
		_vec3		vPosition;
		_vec3		vTexUV;

	}VTXCUBE;
	const _ulong	FVF_CUBE = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0); // 텍스처의 UV 좌표 값을 FLOAT형 3개로 표현하겠다는 매크로(괄호안의 숫자 0의 의미는 본래 버텍스에 텍스쳐 UV값이 여러개가 올 수 있는데 그중 0번째 값을 지정하겠다는 의미)

	typedef struct tagVertexNormal
	{
		_vec3		vPosition;
		_vec3		vNormal;

	}VTXNOM;
	const _ulong	FVF_NOM = D3DFVF_XYZ | D3DFVF_NORMAL;

	typedef struct tagIndex16
	{
		_ushort  _0;
		_ushort  _1;
		_ushort  _2;

	}INDEX16;

	typedef struct tagIndex32
	{
		_ulong	_0;
		_ulong	_1;
		_ulong	_2;

	}INDEX32;

#pragma endregion

#pragma region CAMERA

	typedef struct tagViewSpace 
	{
		_vec3		Eye;
		_vec3		LookAt;
		_vec3		Up;

		tagViewSpace() : Eye(vec3.zero), LookAt(vec3.zero), Up(vec3.zero) {}

	}VIEWSPACE;

	typedef struct tagProjection
	{
		_float		FOV;	
		_float		Aspect;	
		_float		Near;	
		_float		Far;	

		tagProjection() : FOV(0.f), Aspect(0.f), Near(0.f), Far(0.f) {}

	}PROJECTION;

#pragma endregion

#pragma region GAMEOBJECT

	typedef struct tagMoveInfo // 움직이는 오브젝트 (플레이어, 몬스터, 투사체, 이펙트 등)
	{
		_float	fMoveSpeed;
		_float	fRotSpeed;

		tagMoveInfo() : fMoveSpeed(30.f), fRotSpeed(5.f) {}

	}MOVEINFO;


	typedef struct tagStatInfo // 살아있는 오브젝트 (플레이어, 몬스터)
	{
		_float		fMaxHP;
		_float		fCurHP;

		_float		fMaxMP;
		_float		fCurMP;

		_float		fMaxDef;
		_float		fCurDef;

		_float		fMaxExp;
		_float		fCurExp;

		_float		fAD;
		_float		fDF;

		_float		fGold;

		_bool		bDead;

		_uint		iLevel;

		tagStatInfo() : fMaxHP(100.f), fCurHP(fMaxHP), fMaxMP(100.f),
							fCurMP(fMaxMP), fMaxExp(500.f), fCurExp(0.f), fMaxDef(100.f), fCurDef(fMaxDef),
							fAD(10.f), fDF(10.f), fGold(0.f), bDead(false), iLevel(1){}

	}STATINFO;

#pragma endregion


	typedef struct MyEvent
	{
		DWORD_PTR	lParam;
		const _tchar* wParam;
		//wstring		wParam;
		EVENT_TYPE  eType;

	}EVENT;
}


#endif // Engine_Struct_h__
