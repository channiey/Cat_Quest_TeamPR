#pragma once
#include "Quest.h"

class CQuest4 : public CQuest
{
public:
	explicit CQuest4(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CQuest4();

public:
	virtual void Init() override;
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;

private:

private:
	virtual void Free();
};

