#pragma once
#include "Quest.h"

class CQuest5 : public CQuest
{
public:
	explicit CQuest5();
	virtual ~CQuest5();

public:
	virtual void Init() override;
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;

private:

private:
	virtual void Free();
};

