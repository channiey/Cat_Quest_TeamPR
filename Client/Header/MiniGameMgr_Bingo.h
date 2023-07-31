#pragma
#include "GameObject.h"
#include "FlagOwner.h"
#include "Flag.h"

BEGIN(Engine)

class CMiniGameMgr_Bingo : public CBase
{
	DECLARE_SINGLETON(CMiniGameMgr_Bingo)
private:
	explicit CMiniGameMgr_Bingo();
	virtual ~CMiniGameMgr_Bingo();
	
public:
	HRESULT	Init(LPDIRECT3DDEVICE9 _pGraphicDev);
	void	Update(const _float& _fDelta);
public:
	_bool	Get_Start()				{ return m_bStart; } // 활성 상태 확인
	void	Set_Start(_bool _isStart) { m_bStart = _isStart; } // 활성화 

	_bool	Get_IsInit() { return m_bInit; } // 최초 초기화
private:
	LPDIRECT3DDEVICE9		m_pGraphicDev; // 디바이스
	CFlagOwner*				m_pFlagOwner;  // 오너 정보
	vector<CFlag*>			m_FlagVector;  // 깃발들 저장.

	_bool	m_bInit = false; // 최초 초기화
	_bool	m_bStart = false; // 게임 세팅
	_bool	m_bActive;

private:
	virtual void			Free();
};

END