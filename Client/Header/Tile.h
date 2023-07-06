#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CRcTex;
class CTexture;

END

class CTile : public CGameObject
{
public:
	explicit CTile();
	virtual ~CTile();
};

