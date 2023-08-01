#pragma
#include "GameObject.h"
#include "FlagOwner.h"
#include "FlagStart.h"
#include "Bingo_Launcher.h"
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
	
	void	ShowFlag();

public:
	_bool	Get_IsInit() { return m_bInit; } // 최초 초기화

	_bool	Get_Active()				  { return m_bActive; } // 활성 상태 확인
	void	Set_Active(_bool _isActive)   { m_bActive = _isActive; } // 활성화 

	_bool	Get_FlagShow()				  { return m_bShowFlag; }
	void	Set_FlagShow(_bool _isShow)	  { m_bShowFlag = _isShow; }
public:
	HRESULT	Flag_Check(const OBJ_ID& _eID);

private:
	LPDIRECT3DDEVICE9		m_pGraphicDev; // 디바이스
	CFlagOwner*				m_pFlagOwner;  // 오너 정보
	CBingo_Launcher*		m_pLauncher;   // 빙고 장치
	vector<CFlag*>			m_FlagVector;  // 국기 저장.
	vector<CFlag*>			m_BingoVector; // 정답 국기 저장.
	CFlagStart*				m_pStartFlag;  // 가운데 빈 국기

	_bool	m_bInit; // 최초 초기화
	_bool	m_bStart; // 게임 세팅
	_bool	m_bShuffle; // 한 번 섞기
	_bool	m_bActive; // 활성화 상태
	_bool	m_bShowFlag; // 정답 국기 보여주는 상태

	_int	m_iIndex; // 게임 진행 인덱스
	_int	m_iShowIndex; // 보여주기 인덱스
	_int	m_iLevel; // 레벨
	_int	m_iBingoCount; // 총 저장할 개수

	LERP_FLOAT_INFO	m_tFlagShowLerp;
private:
	virtual void			Free();
};

END