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
				// 이거 연산 괜찮을까
				pCol1 = pObj1->Get_Collider();
				pCol2 = pObj2->Get_Collider();

				if (nullptr == pCol1 || nullptr == pCol2) continue;
				Set_Info(iter, pCol1, pCol2);

				if (Check_Rect(pObj1, pObj2)) // 충돌
				{
					if (iter->second) // 이전에도 충돌
					{
						if (!pObj1->Is_Active() || !pObj2->Is_Active()) // 둘 중 하나 삭제 예정
						{
							pCol1->OnCollision_Exit(pObj2);
							pCol2->OnCollision_Exit(pObj1);
							iter->second = false;
						}
						else // 삭제 예정 없음
						{
							pCol1->OnCollision_Stay(pObj2);
							pCol2->OnCollision_Stay(pObj1);
						}
					}
					else // 이번에 충돌
					{
						if (pObj1->Is_Active() && pObj2->Is_Active()) // 둘다 삭제될 예정이 아닐 때만 충돌 처리
						{
							pCol1->OnCollision_Enter(pObj2);
							pCol2->OnCollision_Enter(pObj1);
							iter->second = true;
						}
					}
				}
				else // 충돌 X
				{
					if (iter->second) // 이전에 충돌
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

				if (Check_Rect_Circle(pObj1, pObj2)) // 충돌
				{
					if (iter->second) // 이전에도 충돌
					{
						if (!pObj1->Is_Active() || !pObj2->Is_Active()) // 둘 중 하나 삭제 예정
						{
							pCol1->OnCollision_Exit(pObj2);
							pCol2->OnCollision_Exit(pObj1);
							iter->second = false;
						}
						else // 삭제 예정 없음
						{
							pCol1->OnCollision_Stay(pObj2);
							pCol2->OnCollision_Stay(pObj1);
						}
					}
					else // 이번에 충돌
					{
						if (pObj1->Is_Active() && pObj2->Is_Active()) // 둘다 삭제될 예정이 아닐 때만 충돌 처리
						{
							pCol1->OnCollision_Enter(pObj2);
							pCol2->OnCollision_Enter(pObj1);
							iter->second = true;
						}
					}
				}
				else // 충돌 X
				{
					if (iter->second) // 이전에 충돌
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

	map<_ulonglong, _bool>::iterator	iter;

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

			if (Check_Line_Rect(pObj1, pLine)) // 충돌
			{
				if (iter->second) // 이전에도 충돌
				{
					if (!pObj1->Is_Active() || !pLine->Is_Active()) // 둘 중 하나 삭제 예정
					{
						pCol1->OnCollision_Exit(pLine);
						pCol2->OnCollision_Exit(pObj1);
						iter->second = false;
					}
					else // 삭제 예정 없음
					{
						pCol1->OnCollision_Stay(pLine);
						pCol2->OnCollision_Stay(pObj1);
					}
				}
				else // 이번에 충돌
				{
					if (pObj1->Is_Active() && pLine->Is_Active()) // 둘다 삭제될 예정이 아닐 때만 충돌 처리
					{
						pCol1->OnCollision_Enter(pLine);
						pCol2->OnCollision_Enter(pObj1);
						iter->second = true;
					}
				}
			}
			else // 충돌 X
			{
				if (iter->second) // 이전에 충돌
				{
					pCol1->OnCollision_Exit(pLine);
					pCol2->OnCollision_Exit(pObj1);
					iter->second = false;
				}
			}

		}
	}
}

const _bool CCollisionMgr::Check_Rect(CGameObject* const _pObj1, CGameObject* const _pObj2)
{
	// 건물과 플레이어블 오브젝트 (밀어내기 필요) 
	// 플레이어블 오브젝트와 투사체?
	
	// 밀어내기는 밀어낼 값을 콜라이더에 저장하고, 밀어내기에 대한 구현은 각 오브젝트의 OnCollision에서 구현하도록 한다.

	CRectCollider* pCol1 = static_cast<CRectCollider*>(_pObj1->Get_Collider());
	CRectCollider* pCol2 = static_cast<CRectCollider*>(_pObj2->Get_Collider());

	CTransform* pTrans1 = _pObj1->Get_Transform();
	CTransform* pTrans2 = _pObj2->Get_Transform();

	_float fX = fabs(pTrans1->Get_Info(INFO_POS).x - pTrans2->Get_Info(INFO_POS).x);
	_float fZ = fabs(pTrans1->Get_Info(INFO_POS).z - pTrans2->Get_Info(INFO_POS).z);

	_float fRadiusX = fabs(pTrans1->Get_Scale().x + pTrans2->Get_Scale().x) * 0.5f;
	_float fRadiusZ = fabs(pTrans1->Get_Scale().z + pTrans2->Get_Scale().z) * 0.5f;

	if ((fRadiusX >= fX) && (fRadiusZ >= fZ))
	{
		_float fOverX = fRadiusX - fX;
		_float fOverY = fRadiusZ - fZ;

		pCol1->Set_OverLap(_vec3{ fOverX, fOverY, 0.f });
		pCol2->Set_OverLap(_vec3{ fOverX, fOverY, 0.f });

		return TRUE;
	}

	return FALSE;
}

const _bool CCollisionMgr::Check_Rect_Circle(CGameObject* const _pObj1, CGameObject* const _pObj2)
{
	// 몬스터 범위기반 콜라이더

	// 아직 필요가 확실치 않다.

	// 필요하면 그때 바로 구현

	// Ref
	// https://www.google.com/search?q=%EC%82%AC%EA%B0%81%ED%98%95+%EC%9B%90+%EC%B6%A9%EB%8F%8C&newwindow=1&sxsrf=AB5stBgc6PwOAQK7Ftd2ZsFN2JfzcZQq4w%3A1688429989915&ei=pWWjZOC_N9PWseMPmpGLyAM&ved=0ahUKEwigppvu4_P_AhVTa2wGHZrIAjkQ4dUDCA8&uact=5&oq=%EC%82%AC%EA%B0%81%ED%98%95+%EC%9B%90+%EC%B6%A9%EB%8F%8C&gs_lp=Egxnd3Mtd2l6LXNlcnAiFOyCrOqwge2YlSDsm5Ag7Lap64-MMgUQABiABEilG1AAWMUacAZ4AJABAZgBnwGgAa0TqgEEMC4yMrgBA8gBAPgBAcICBBAjGCfCAhAQLhiABBgUGIcCGLEDGIMBwgILEAAYgAQYsQMYgwHCAgcQABiKBRhDwgIOEC4YxwEYsQMY0QMYgATCAgsQLhiABBixAxiDAcICCBAAGIAEGLEDwgIKEAAYgAQYFBiHAsICBBAAGB7CAgYQABgeGA_CAggQABgeGA8YCsICBhAAGAUYHsICCBAAGAUYHhgPwgIGEAAYCBgewgIHECEYoAEYCsICBxAAGA0YgATiAwQYACBBiAYB&sclient=gws-wiz-serp


	return TRUE;
}

const _bool CCollisionMgr::Check_Line_Rect(CGameObject* const _pObj1, CLineObject* const _pObj2)
{
	// 경계와 플레이어블 오브젝트

	// 밀어내기는 밀어낼 값을 콜라이더에 저장하고, 밀어내기에 대한 구현은 각 오브젝트의 OnCollision에서 구현하도록 한다.

	CRectCollider* pCol1 = static_cast<CRectCollider*>(_pObj1->Get_Component(COMPONENT_TYPE::COL_RECT, ID_STATIC));
	CLineCollider* pCol2 = static_cast<CLineCollider*>(_pObj2->Get_Component(COMPONENT_TYPE::COL_LINE, ID_STATIC));

	// 피벗이 적용된 오브젝트의 최종 콜라이더 포지션 설정
	_vec3 vColPos = _pObj1->Get_Transform()->Get_Info(INFO_POS) + pCol1->m_vOffset;

	// 콜라이더 스케일 설정 
	_vec3 vColSize = pCol1->m_vSize;

	// 반복문 돌면서 렉트를 구성하는 선분 4개와 라인 선분 1를 CCW해야한다.
	// 사각형과 선분의 충돌 검사라면 CCW 16번인데 괜찮을까? -> 일단 해보고 최적화




	return TRUE;
}

const _int CCollisionMgr::Check_CCW(const _vec3& _vLineStart, const _vec3& _vLineEnd, const _vec3& _vPT)
{
	long long t1 = long long(_vLineStart.x * _vLineEnd.y + _vLineEnd.x * _vPT.y + _vPT.x * _vLineStart.y);
	long long t2 = long long(_vLineStart.y * _vLineEnd.x + _vLineEnd.y * _vPT.x + _vPT.y * _vLineStart.x);

	long long tRes = t1 - t2;

	if (tRes > 0)
		return 1;
	else if (tRes == 0)
		return 0;
	else
		return -1;

	return 0;
}



void CCollisionMgr::Set_Info(map<_ulonglong, _bool>::iterator & _iter, CCollider * _pCol1, CCollider * _pCol2)
{
	COLLIDER_ID ID;

	ID.iLeft_id = _pCol1->Get_ID();
	ID.iRight_id = _pCol2->Get_ID();

	// 이전에 충돌 검사 여부 조사
	_iter = m_mapColInfo.find(ID.ID);

	// 없다면 새로 추가
	if (m_mapColInfo.end() == _iter)
	{
		m_mapColInfo.insert({ ID.ID, false });
		_iter = m_mapColInfo.find(ID.ID);
	}
}



void CCollisionMgr::Free()
{
}
