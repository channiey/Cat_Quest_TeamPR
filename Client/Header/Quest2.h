#pragma once
#include "Quest.h"

class CQuest2 : public CQuest
{
public:
	explicit CQuest2(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CQuest2();

public:
	virtual void Init() override;
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;

private:

private:
	virtual void Free();
};

