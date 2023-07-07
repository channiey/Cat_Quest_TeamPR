#include "stdafx.h"
#include "..\Header\Calculator.h"

IMPLEMENT_SINGLETON(CCalculator)

CCalculator::CCalculator()
{
}

CCalculator::~CCalculator()
{
}

_vec3 CCalculator::Mouse_Picking(LPDIRECT3DDEVICE9 pGraphicDev, POINT pt)
{
	// ������� ������ ���콺 ��ǥ
	D3DXVECTOR3	 vMousePos;

	// ����Ʈ ���� ������
	D3DVIEWPORT9 viewPort;
	pGraphicDev->GetViewport(&viewPort);

	// ���콺 ��ǥ ���� ��ǥ�� ��ȯ.
	vMousePos.x = pt.x / (viewPort.Width * 0.5f) - 1;
	vMousePos.y = pt.y / -(viewPort.Height * 0.5f) + 1;
	vMousePos.z = 0.f;

	// ���� -> �� �����̽�
	D3DXMATRIX matProj;
	pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixInverse(&matProj, 0, &matProj);
	D3DXVec3TransformCoord(&vMousePos, &vMousePos, &matProj);

	// ���� ��ġ, ���� ����
	D3DXVECTOR3 vRayPos = { 0.f, 0.f, 0.f };
	D3DXVECTOR3 vRayDir = vMousePos - vRayPos;

	// �� �����̽� -> ���� �����̽�
	D3DXMATRIX matView;
	pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, 0, &matView);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);

	// D3DXMATRIX		matWorld;
	// D3DXMatrixInverse(&matWorld, 0, &CCalculator::Get_Instance()->m_matTerrainWorld);
	// D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matWorld);
	// D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matWorld);

	//return CCalculator::Get_Instance()->Pick_Tile(vRayPos, vRayDir);
	return _vec3();
}

void CCalculator::Free()
{
}
