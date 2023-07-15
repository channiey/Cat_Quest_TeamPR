#pragma once

#include "GameObject.h"

class CRangeObj;

BEGIN(Engine)

class CRcTex;
class CTexture;
class CStateMachine;
class CAnimator;
END

class CPlayer : public Engine::CGameObject
{
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPlayer(const CPlayer& rhs);
	virtual ~CPlayer();

public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;

public:
	virtual void		OnCollision_Enter(CGameObject* _pColObj);
	virtual void		OnCollision_Stay(CGameObject* _pColObj);
	virtual void		OnCollision_Exit(CGameObject* _pColObj);

#pragma region Access Methood

#pragma region MOVEINFO

public:
	const MOVEINFO&		Get_MoveInfo() const { return m_tMoveInfo; }

	void				Set_MoveSpeed(const _float& _fMoveSpeed) { m_tMoveInfo.fMoveSpeed = _fMoveSpeed; }
	void				Set_RotSpeed(const _float& _fRotSpeed) { m_tMoveInfo.fRotSpeed = _fRotSpeed; }

	void				Add_MoveSpeed(const _float& _fMoveSpeed) { m_tMoveInfo.fMoveSpeed += _fMoveSpeed; }
	void				Add_RotSpeed(const _float& _fRotSpeed) { m_tMoveInfo.fRotSpeed += _fRotSpeed; }

#pragma endregion

#pragma region STATINFO
public:

	const STATINFO& Get_StatInfo() const { return m_tStatInfo; }

	const _bool& Is_Dead() const { return m_tStatInfo.bDead; }

	void				Set_Dead(const _bool& _bDead = TRUE) { m_tStatInfo.bDead = _bDead; }

	void				Set_MaxHP(const _float& _fMaxHp) { m_tStatInfo.fMaxHP = _fMaxHp; }
	void				Set_CurHP(const _float& _fCurHp) { m_tStatInfo.fCurHP = _fCurHp; }

	void				Set_MaxMP(const _float& _fMaxMp) { m_tStatInfo.fMaxMP = _fMaxMp; }
	void				Set_CurMP(const _float& _fCurMp) { m_tStatInfo.fCurMP = _fCurMp; }

	void				Set_MaxDef(const _float& _fMaxDef) { m_tStatInfo.fMaxDef = _fMaxDef; }
	void				Set_CurDef(const _float& _fCurDef) { m_tStatInfo.fCurDef = _fCurDef; }

	void				Set_MaxExp(const _float& _fMaxExp) { m_tStatInfo.fMaxExp = _fMaxExp; }
	void				Set_CurExp(const _float& _fCurExp) { m_tStatInfo.fCurExp = _fCurExp; }

	void				Set_AD(const _float& _fAD) { m_tStatInfo.fAD = _fAD; }
	void				Set_DF(const _float& _fDF) { m_tStatInfo.fDF = _fDF; }

	void				Set_Gold(const _float& _fGold) { m_tStatInfo.fGold = _fGold; }

	void				Set_Level(const _uint& _iLevel) { m_tStatInfo.iLevel = _iLevel; }

	void				Add_MaxHP(const _float& _fMaxHp) { m_tStatInfo.fMaxHP += _fMaxHp; }
	void				Add_CurHP(const _float& _fCurHp) { m_tStatInfo.fCurHP += _fCurHp; }

	void				Add_MaxMP(const _float& _fMaxMp) { m_tStatInfo.fMaxMP += _fMaxMp; }
	void				Add_CurMP(const _float& _fCurMp) { m_tStatInfo.fCurMP += _fCurMp; }

	void				Add_MaxDef(const _float& _fMaxDef) { m_tStatInfo.fMaxDef += _fMaxDef; }
	void				Add_CurDef(const _float& _fCurDef) { m_tStatInfo.fCurDef += _fCurDef; }

	void				Add_MaxExp(const _float& _fMaxExp) { m_tStatInfo.fMaxExp += _fMaxExp; }
	void				Add_CurExp(const _float& _fCurExp) { m_tStatInfo.fCurExp += _fCurExp; }

	void				Add_AD(const _float& _fAD) { m_tStatInfo.fAD += _fAD; }
	void				Add_DF(const _float& _fDF) { m_tStatInfo.fDF += _fDF; }

	void				Add_Gold(const _float& _fGold) { m_tStatInfo.fGold += _fGold; }

	void				Add_Level(const _uint& _iLevel) { m_tStatInfo.iLevel += _iLevel; }
#pragma endregion

#pragma region OTHER

	void				Set_CurGroudType(const LINE_TYPE& _eType)	{ m_eCurGroundType = _eType; }
	const LINE_TYPE&	Get_CurGroundType() const					{ return m_eCurGroundType; }

#pragma endregion

#pragma endregion

private:
	HRESULT				Add_Component();
	void				Key_Input(const _float& fTimeDelta);

private:
	MOVEINFO			m_tMoveInfo;
	STATINFO			m_tStatInfo;

	LINE_TYPE			m_eCurGroundType; // 현재 플레이어가 위치한 그라운드 정보

private:
	CTexture*			m_pTextureCom[_uint(STATE_TYPE::TYPEEND)];
	CStateMachine*		m_pStateMachineCom;

	_uint				m_iTempMode;

	_bool				m_bExpand;
	_bool				m_bShirnk;

	// << : Test : Range Test
	enum class RANGE_TYPE { BASIC_ATTACK, SKILL_ATK1, TYPEEND };
	CRangeObj* arrRangeObj[(UINT)RANGE_TYPE::TYPEEND]; // Set Active로 상황에 맞게 껐다 켰다
	// >> :

public:
	static CPlayer*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free() override;

};

