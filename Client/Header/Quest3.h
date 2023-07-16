#pragma once
#include "Quest.h"

class CQuest3 : public CQuest
{
public:
	explicit CQuest3(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CQuest3();

public:
	virtual void Init() override;
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;

private:

private:
	virtual void Free();
};

