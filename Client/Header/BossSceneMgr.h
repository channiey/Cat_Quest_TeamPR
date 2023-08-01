#pragma once

#include "Base.h"
#include "Engine_Define.h"

enum class PAGE { INIT, START, DEAD, FADE_OUT, FADE_END, FINISH, TYPEEND };

BEGIN(Engine)

class CGameObject;

END

class CBossSceneMgr : public CBase
{
	DECLARE_SINGLETON(CBossSceneMgr)

private:
	explicit CBossSceneMgr();
	virtual ~CBossSceneMgr();

public:
	HRESULT					Ready_BossSceneMgr(LPDIRECT3DDEVICE9 _pGraphicDev);
	void					Update_BossSceneMgr(const _float& fTimeDelta);

public:
	const _bool&			Is_Ready() const { return m_arrPage[(_uint)PAGE::INIT]; }
	const _bool				Is_Start() const { return m_arrPage[(_uint)PAGE::START]; }
	const _bool				Is_Active_Boss(); 

public:
	HRESULT					Start_BossScene(); // 보스 연출 시작시 호출 (보스 활성화)
	void					Play_Dead_BossScene(); // 보스 데드 애니메이션 종료시 호출

private:
	void					Set_Npc(); 

private:
	LPDIRECT3DDEVICE9		m_pGraphicDev;
	_bool					m_arrPage[(_uint)PAGE::TYPEEND];

	_float					m_fAcc;
	_float					m_fDeadFadeStayTime;

	_bool					m_bFadeIn_End;
	_bool					m_bFadeOut_End;
	


private:
	virtual void			Free();
};



