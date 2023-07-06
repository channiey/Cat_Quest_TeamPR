#include "State.h"
#include "..\Header\State.h"

CState::CState(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
{
	m_pGraphicDev->AddRef();
}

CState::~CState()
{
}

void CState::Free()
{
	Safe_Release(m_pGraphicDev);
}
