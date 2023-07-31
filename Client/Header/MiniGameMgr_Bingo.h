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
	_bool	Get_Start()				{ return m_bStart; } // Ȱ�� ���� Ȯ��
	void	Set_Start(_bool _isStart) { m_bStart = _isStart; } // Ȱ��ȭ 

	_bool	Get_IsInit() { return m_bInit; } // ���� �ʱ�ȭ
private:
	LPDIRECT3DDEVICE9		m_pGraphicDev; // ����̽�
	CFlagOwner*				m_pFlagOwner;  // ���� ����
	vector<CFlag*>			m_FlagVector;  // ��ߵ� ����.

	_bool	m_bInit = false; // ���� �ʱ�ȭ
	_bool	m_bStart = false; // ���� ����
	_bool	m_bActive;

private:
	virtual void			Free();
};

END