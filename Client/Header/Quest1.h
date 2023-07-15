#pragma once
#include "Quest.h"

class CQuest1 : public CQuest
{
public:
	explicit CQuest1();
	virtual ~CQuest1();

public:
	virtual void Init() override;
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;

private:

private:
	virtual void Free();
};

