#pragma once
#include "Engine_Define.h"
#include "Base.h"

class CCalculator : public CBase
{
	DECLARE_SINGLETON(CCalculator)

private:
	explicit CCalculator();
	virtual ~CCalculator();

public:
	_vec3	Mouse_Picking(LPDIRECT3DDEVICE9 pGraphicDev, POINT pt);
private:
	virtual void Free() override;
};
