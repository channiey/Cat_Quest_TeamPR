#pragma once
#include "Quest.h"

class CQuest6 : public CQuest
{
public:
	explicit CQuest6();
	virtual ~CQuest6();

public:
	virtual void Init() override;
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;

private:

private:
	virtual void Free();
};

