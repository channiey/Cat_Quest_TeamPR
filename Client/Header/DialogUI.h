#pragma once
#include "UI.h"

BEGIN(Engine)

class CTexture;

END

class CDialogUI : public CUI     // 뷰포트 사용 | 화면에 고정된 표시를 위한 UI  프로토타입 입니다.
{

protected:

	explicit CDialogUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CDialogUI(const CDialogUI& rhs);
	virtual ~CDialogUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;
	HRESULT					Ready_Dialog(OBJ_ID eNpc, wstring strDialog, SPIRITEMO_TYPE eEmo);
	void					Select_Npc(OBJ_ID eNpc, SPIRITEMO_TYPE eEmo);
	void					Typing_Effect(const _float& fTimeDelta);

private:
	CTexture*				m_pUITextureCom[3];
	_matrix					m_matUI[2];

	OBJ_ID					m_eObjID;
	SPIRITEMO_TYPE			m_eEmo;

	wstring					m_strDialog;
	wstring					m_strTyping;
	_uint					m_iTextCnt;

	_float					m_fAcc;
	_uint					m_iNpc;

	RECT					m_rcText;

	_bool					m_bShrink;

	_float					m_fMultipleX;
	_float					m_fMultipleY;

public:

	static CDialogUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev, OBJ_ID eNpc, wstring strDialog, SPIRITEMO_TYPE eEmo = SPIRITEMO_TYPE::HAPPY);


protected:
	virtual void			Free() override;
};

