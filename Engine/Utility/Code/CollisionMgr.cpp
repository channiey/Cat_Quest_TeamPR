#include "..\..\Header\CollisionMgr.h"

#include "Management.h"
#include "Layer.h"

#include "GameObject.h"
#include "LineObject.h"

#include "Collider.h"
#include "LineCollider.h"
#include "CircleCollider.h"
#include "RectCollider.h"

#include "Transform.h"

#include <iostream>

IMPLEMENT_SINGLETON(CCollisionMgr)

inline _float DotProduct(const _float v0[3], const _float v1[3])
{
	return v0[0] * v1[0] + v0[1] * v1[1] + v0[2] * v1[2];
}


typedef		map<const _tchar*, CGameObject*>	_mapObj;
typedef		_mapObj::iterator					_iter;

CCollisionMgr::CCollisionMgr()
{

}

CCollisionMgr::~CCollisionMgr()
{
	Free();
}

void CCollisionMgr::Check_Collision(const OBJ_TYPE& _eType1, const OBJ_TYPE& _eType2, const COL_TYPE& _eColType1, const COL_TYPE& _eColType2)
{	
	CGameObject*	pObj1	=	nullptr;	 
	CGameObject*	pObj2	=	nullptr;
	CCollider*		pCol1	=	nullptr;
	CCollider*		pCol2	=	nullptr;

	map<_ulonglong, _bool>::iterator	iter;

	_mapObj& mapObj1 = CManagement::GetInstance()->Get_Layer(_eType1)->Get_ObjectMap();
	_mapObj& mapObj2 = CManagement::GetInstance()->Get_Layer(_eType2)->Get_ObjectMap();

	if (mapObj1.empty() || mapObj2.empty()) return;

	for (_iter iter1 = mapObj1.begin(); iter1 != mapObj1.end(); ++iter1)
	{
		for (_iter iter2 = mapObj2.begin(); iter2 != mapObj2.end(); ++iter2)
		{ 
			pObj1 = iter1->second;	pObj2 = iter2->second;

			if (pObj1 == pObj2 || nullptr == pObj1 || nullptr == pObj2) continue;

			if (COL_TYPE::RECT == _eColType1 && COL_TYPE::RECT == _eColType2)
			{
				pCol1 = pObj1->Get_Collider();
				pCol2 = pObj2->Get_Collider();

				if (nullptr == pCol1 || nullptr == pCol2) continue;
				Set_Info(iter, pCol1, pCol2);

				if (Check_Rect(pObj1, pObj2)) // �浹
				{
					if (iter->second) // �������� �浹
					{
						if (!pObj1->Is_Active() || !pObj2->Is_Active()) // �� �� �ϳ� ���� ����
						{
							pCol1->OnCollision_Exit(pObj2);
							pCol2->OnCollision_Exit(pObj1);
							iter->second = false;
						}
						else // ���� ���� ����
						{
							pCol1->OnCollision_Stay(pObj2);
							pCol2->OnCollision_Stay(pObj1);
						}
					}
					else // �̹��� �浹
					{
						if (pObj1->Is_Active() && pObj2->Is_Active()) // �Ѵ� ������ ������ �ƴ� ���� �浹 ó��
						{
							pCol1->OnCollision_Enter(pObj2);
							pCol2->OnCollision_Enter(pObj1);
							iter->second = true;
						}
					}
				}
				else // �浹 X
				{
					if (iter->second) // ������ �浹
					{
						pCol1->OnCollision_Exit(pObj2);
						pCol2->OnCollision_Exit(pObj1);
						iter->second = false;
					}
				}
			}
			else if (COL_TYPE::RECT == _eColType1 && COL_TYPE::CIRCLE == _eColType2)
			{
				pCol1 = pObj1->Get_Collider();
				pCol2 = pObj2->Get_Collider();

				if (nullptr == pCol1 || nullptr == pCol2) continue;
				Set_Info(iter, pCol1, pCol2);

				if (Check_Rect_Circle(pObj1, pObj2)) // �浹
				{
					if (iter->second) // �������� �浹
					{
						if (!pObj1->Is_Active() || !pObj2->Is_Active()) // �� �� �ϳ� ���� ����
						{
							pCol1->OnCollision_Exit(pObj2);
							pCol2->OnCollision_Exit(pObj1);
							iter->second = false;
						}
						else // ���� ���� ����
						{
							pCol1->OnCollision_Stay(pObj2);
							pCol2->OnCollision_Stay(pObj1);
						}
					}
					else // �̹��� �浹
					{
						if (pObj1->Is_Active() && pObj2->Is_Active()) // �Ѵ� ������ ������ �ƴ� ���� �浹 ó��
						{
							pCol1->OnCollision_Enter(pObj2);
							pCol2->OnCollision_Enter(pObj1);
							iter->second = true;
						}
					}
				}
				else // �浹 X
				{
					if (iter->second) // ������ �浹
					{
						pCol1->OnCollision_Exit(pObj2);
						pCol2->OnCollision_Exit(pObj1);
						iter->second = false;
					}
				}
			}
		}
	}
}

void CCollisionMgr::Check_Line_Collision(const OBJ_TYPE& _eType)
{
	CGameObject* pObj1 = nullptr;

	CCollider* pCol1 = nullptr;
	CCollider* pCol2 = nullptr;

	map<_ulonglong, _bool>::iterator iter;

	_mapObj& mapObj1 = CManagement::GetInstance()->Get_Layer(_eType)->Get_ObjectMap();

	if (mapObj1.empty()) return;

	for (_iter iter1 = mapObj1.begin(); iter1 != mapObj1.end(); ++iter1)
	{
		for (auto& pLine : m_vecLine)
		{
			pObj1 = iter1->second;

			if (nullptr == pObj1 || nullptr == pLine ) continue;

			pCol1 = static_cast<CCollider*>(pObj1->Get_Component(COMPONENT_TYPE::COL_RECT, ID_STATIC));
			pCol2 = static_cast<CCollider*>(pLine->Get_Component(COMPONENT_TYPE::COL_LINE, ID_STATIC));

			if (nullptr == pCol1 || nullptr == pCol2) continue;

			Set_Info(iter, pCol1, pCol2);

			if (Check_Line_Rect(pObj1, pLine)) // �浹
			{
				if (iter->second) // �������� �浹
				{
					if (!pObj1->Is_Active() || !pLine->Is_Active()) // �� �� �ϳ� ���� ����
					{
						pCol1->OnCollision_Exit(pLine);
						pCol2->OnCollision_Exit(pObj1);
						iter->second = false;
					}
					else // ���� ���� ����
					{
						pCol1->OnCollision_Stay(pLine);
						pCol2->OnCollision_Stay(pObj1);

						//cout << "Stay\n";
					}
				}
				else // �̹��� �浹
				{
					if (pObj1->Is_Active() && pLine->Is_Active()) // �Ѵ� ������ ������ �ƴ� ���� �浹 ó��
					{
						pCol1->OnCollision_Enter(pLine);
						pCol2->OnCollision_Enter(pObj1);
						iter->second = true;

						//cout << "Enter\n";
					}
				}
			}
			else // �浹 X
			{
				if (iter->second) // ������ �浹
				{
					pCol1->OnCollision_Exit(pLine);
					pCol2->OnCollision_Exit(pObj1);
					iter->second = false;

					//cout << "Exit\n";

				}
			}

		}
	}
}

const _bool CCollisionMgr::Check_Rect(CGameObject* const _pObj1, CGameObject* const _pObj2)
{
	// �о��� �о ���� �ݶ��̴��� ���ο� �����ϰ�, �о�⿡ ���� ������ �� ������Ʈ�� OnCollision���� �����ϵ��� �Ѵ�.

	CRectCollider* pCol1 = static_cast<CRectCollider*>(_pObj1->Get_Collider());
	CRectCollider* pCol2 = static_cast<CRectCollider*>(_pObj2->Get_Collider());

	CTransform* pTrans1 = _pObj1->Get_Transform();
	CTransform* pTrans2 = _pObj2->Get_Transform();
	
	_float fX = fabs(pTrans1->Get_Info(INFO_POS).x - pTrans2->Get_Info(INFO_POS).x);
	_float fZ = fabs(pTrans1->Get_Info(INFO_POS).z - pTrans2->Get_Info(INFO_POS).z);

	// �ִϸ��̼ǿ��� �������� -�� ����ϴ� ��쿡 ���� ����ó��
	_float fRadiusX = (fabs(pTrans1->Get_Scale().x) + fabs(pTrans2->Get_Scale().x)) * 0.5f;
	_float fRadiusZ = (fabs(pTrans1->Get_Scale().z) + fabs(pTrans2->Get_Scale().z)) * 0.5f;

	// Z ������ ����ó��
	//if (pTrans1->Get_Info(INFO_POS).z < pTrans2->Get_Info(INFO_POS).z)
	//	fRadiusZ += fabs(pTrans2->Get_Scale().z);

	if ((fRadiusX >= fX) && (fRadiusZ >= fZ))
	{
		_float fOverX = fRadiusX - fX;
		_float fOverZ = fRadiusZ - fZ;

		pCol1->Set_OverLap_Rect(_vec3{ fOverX, 0.f, fOverZ });
		pCol2->Set_OverLap_Rect(_vec3{ fOverX, 0.f, fOverZ });

		return TRUE;
	}

	return FALSE;
}

const _bool CCollisionMgr::Check_Rect_Circle(CGameObject* const _pObj1, CGameObject* const _pObj2)
{

	return TRUE;
}

const _bool CCollisionMgr::Check_Line_Rect(CGameObject* const _pObj1, CLineObject* const _pObj2)
{
	CRectCollider* pCol1 = static_cast<CRectCollider*>(_pObj1->Get_Component(COMPONENT_TYPE::COL_RECT, ID_STATIC));
	CLineCollider* pCol2 = static_cast<CLineCollider*>(_pObj2->Get_Component(COMPONENT_TYPE::COL_LINE, ID_STATIC));

	_vec3 vPos = _pObj1->Get_Transform()->Get_Info(INFO_POS);
	_vec3 vScale = _pObj1->Get_Transform()->Get_Scale();

	if (0 > vScale.x) vScale.x *= -1.f;
	if (0 > vScale.z) vScale.z *= -1.f;

	_vec3 vRectPtList[4] =
	{
		_vec3{vPos.x - (vScale.x * 0.5f), 0.f, vPos.z + (vScale.z * 0.5f)},
		_vec3{vPos.x + (vScale.x * 0.5f), 0.f, vPos.z + (vScale.z * 0.5f)},
		_vec3{vPos.x + (vScale.x * 0.5f), 0.f, vPos.z - (vScale.z * 0.5f)},
		_vec3{vPos.x - (vScale.x * 0.5f), 0.f, vPos.z - (vScale.z * 0.5f)}
	};
	_vec3 vLinePtList[2] =
	{
		_vec3{ pCol2->m_vPointList[0].x, 0.f, pCol2->m_vPointList[0].z - vScale.z }, // z����ó��
		_vec3{ pCol2->m_vPointList[1].x, 0.f, pCol2->m_vPointList[1].z - vScale.z },
	};

	for (int i = 0; i < 3; ++i)
	{
		if ((Check_CCW(vRectPtList[i], vRectPtList[i + 1], vLinePtList[0])
			!= Check_CCW(vRectPtList[i], vRectPtList[i + 1], vLinePtList[1]))
			&&
			(Check_CCW(vLinePtList[0], vLinePtList[1], vRectPtList[i])
			!= Check_CCW(vLinePtList[0], vLinePtList[1], vRectPtList[i + 1])))
		{
			//if(������ �� ���� �����̶��)

			pCol2->m_vOverlapLine = Get_LineCollision_Data(vRectPtList, vLinePtList);

			return TRUE;
		}
	}

	return FALSE;
}

const _int CCollisionMgr::Check_CCW(const _vec3& _vLineStart, const _vec3& _vLineEnd, const _vec3& _vPT)
{
	long long t1 = long long(_vLineStart.x * _vLineEnd.z + _vLineEnd.x * _vPT.z + _vPT.x * _vLineStart.z);
	long long t2 = long long(_vLineStart.z * _vLineEnd.x + _vLineEnd.z * _vPT.x + _vPT.z * _vLineStart.x);

	long long tres = t1 - t2;

	if (tres > 0)
		return 1;
	else if (tres == 0)
		return 0;
	else
		return -1;

	return 0;
}

const _vec3& CCollisionMgr::Get_LineCollision_Data(_vec3* _vRectPtList, _vec3* _vLinePtList)
{
	// �浹 ������ŭ ���ֱ� ���� ������ ���� -> ���� �ݶ��̴��� ����
	_vec3 vCross, v1, v2;
	_bool bPrevY[4]; // ������ y ���� �������� �������
	_vec3 vOutPoint; // ��Ʈ 4�� �� ���� ��
	_vec3 vOverlap;  // ������� ����
	ZeroMemory(&vOverlap, sizeof(_vec3));

	// 1. �������� 4�� �� ��� ���� ���ι����� �������� ã�´�
	for (int i = 0; i < 4; ++i)
	{
		v1 = _vRectPtList[i] - _vLinePtList[0];
		v2 = _vLinePtList[1] - _vLinePtList[0];

		D3DXVec3Cross(&vCross, &v1, &v2);
		if (0 < vCross.y)
			bPrevY[i] = true;
		else
			bPrevY[i] = false;
	}

	_bool bPrev;
	for (int i = 0; i < 4; ++i)
	{
		if (0 == i)
		{
			bPrev = bPrevY[i]; 
			continue;
		}

		if (bPrev != bPrevY[i])
		{
			if (1 == i && bPrevY[0] == bPrevY[2])
			{
				vOutPoint = _vRectPtList[i];
				break;
			}
			else if (1 == i && bPrevY[0] != bPrevY[2])
			{
				vOutPoint = _vRectPtList[0];

				break;
			}
			vOutPoint = _vRectPtList[i];
			break;
		}
	}

	// 2. ������ ���������� ���ο��� ��ġ�� x, z ���� ���Ѵ�.
	_float fZ = ((_vLinePtList[1].z - _vLinePtList[0].z) / (_vLinePtList[1].x - _vLinePtList[0].x)) 
					* (vOutPoint.x - _vLinePtList[0].x) 
					+ _vLinePtList[0].z;

	_float fX = (vOutPoint.z - _vLinePtList[0].z) 
					/ ((_vLinePtList[1].z - _vLinePtList[0].z) / (_vLinePtList[1].x - _vLinePtList[0].x))	
					+ _vLinePtList[0].x;

	// 3. �о ���� ��ġ 
	vOverlap.x = fX - vOutPoint.x;
	vOverlap.z = fZ - vOutPoint.z;

	// 3. �� �������� ���� �ݶ��̴��� �����Ѵ�.
	return vOverlap;
}

void CCollisionMgr::Set_Info(map<_ulonglong, _bool>::iterator & _iter, CCollider * _pCol1, CCollider * _pCol2)
{
	COLLIDER_ID ID;

	ID.iLeft_id = _pCol1->Get_ID();
	ID.iRight_id = _pCol2->Get_ID();

	// ������ �浹 �˻� ���� ����
	_iter = m_mapColInfo.find(ID.ID);

	// ���ٸ� ���� �߰�
	if (m_mapColInfo.end() == _iter)
	{
		m_mapColInfo.insert({ ID.ID, false });
		_iter = m_mapColInfo.find(ID.ID);
	}
}

void CCollisionMgr::Free()
{
}
