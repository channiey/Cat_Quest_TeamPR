#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CQuestMgr : public CBase
{
	DECLARE_SINGLETON(CQuestMgr)
private:
	explicit CQuestMgr();
	virtual ~CQuestMgr();

public:
	void	Init();

public:

private:

private:
	virtual void			Free();
};

END

