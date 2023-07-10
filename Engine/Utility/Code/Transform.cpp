#include "..\..\Header\Transform.h"

#include "CameraMgr.h"
#include "GameObject.h"

CTransform::CTransform()
	: m_vAngle(vec3.zero)
	, m_vScale(vec3.one)
	, m_vDir(vec3.right)
{
	ZeroMemory(m_vInfo, sizeof(m_vInfo));
	D3DXMatrixIdentity(&m_matWorld);
}

CTransform::CTransform(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev, COMPONENT_TYPE::TRANSFORM)
{
	ZeroMemory(&m_vAngle	, sizeof(_vec3));
	ZeroMemory(&m_vScale	, sizeof(_vec3));
	ZeroMemory(&m_quatQ		, sizeof(_quat));
	ZeroMemory(&m_vInfo		, sizeof(_vec3) * INFO_END);
	ZeroMemory(& m_vDir     , sizeof(_vec3));
	D3DXMatrixIdentity(&m_matWorld);

	Cal_WorldMat();
}

CTransform::CTransform(const CTransform & rhs, CGameObject* _pOwnerObject)
	: CComponent(rhs, _pOwnerObject)
{
	Ready_Transform();
}

CTransform::~CTransform()
{
}

void CTransform::Translate(const DIRID& _eDir, const _float& fSpeed, const SPACEID _eSpace)
{
	// ���� �ڽ��� ��ġ���� ������ �������� �̵��Ѵ�. (eDir : ��, _eSpace �����̽� ����)
	// �� : ���� Ȥ�� ���带 ���������� �ڽ��� x, y, z �� 6���� ����

	// SPACEID�� ������ ��� �ڽ��� ������ ���� �������� �̵��ϰ�, ������ ��� ������ ���� �������� �̵��Ѵ�.

	if (LOCAL == _eSpace)
		m_vInfo[INFO_POS] += m_vInfo[_eDir] * fSpeed;
	else
		switch (_eDir)
		{
		case DIR_UP:
			m_vInfo[INFO_POS] += vec3.up * fSpeed;
			break;
		case DIR_RIGHT:
			m_vInfo[INFO_POS] += vec3.right * fSpeed;
			break;
		case DIR_FORWARD:
			m_vInfo[INFO_POS] += vec3.forward * fSpeed;
			break;
		}

	memcpy(&m_matWorld.m[INFO_POS][0], &m_vInfo[INFO_POS], sizeof(_vec3));

	Cal_WorldMat();
}

void CTransform::Translate(const _vec3 & _vDir, const _float & fSpeed)
{
	// ���� �ڽ��� ��ġ���� �Ű������� ���� '������ ����'���� �̵��Ѵ�.
	
	_vec3 vDir{};

	m_vInfo[INFO_POS] += *D3DXVec3Normalize(&vDir, &_vDir) * fSpeed;

	memcpy(&m_matWorld.m[INFO_POS][0], &m_vInfo[INFO_POS], sizeof(_vec3));

	Cal_WorldMat();
}

void CTransform::Translate(const _float& fSpeed)
{
	m_vInfo[INFO_POS] += *D3DXVec3Normalize(&m_vDir, &m_vDir) * fSpeed;

	memcpy(&m_matWorld.m[INFO_POS][0], &m_vInfo[INFO_POS], sizeof(_vec3));

	Cal_WorldMat();
}

void CTransform::Rotate(const DIRID & _eDir, const _float& fSpeed, const SPACEID _eSpace)
{
	// ���� �ڽ��� ȸ�� ���¿��� �Ű������� ���� ���� �������� �Ű������� ���� �� ��ŭ ȸ���Ѵ�.(eDir : ��, _eSpace �����̽� ����)
	// �� : ���� Ȥ�� ���带 ���������� �ڽ��� x, y, z �� 6���� ����

	// SPACEID�� ������ ��� �ڽ��� ������ ���� �������� �̵��ϰ�, ������ ��� ������ ���� �������� �̵��Ѵ�.

	
	*(((_float*)&m_vAngle) + _eDir) += fSpeed;	//ȸ�� ���� ���̺� (�� ������ �������� ���ʹϾ�� ȸ������� �ٽ� ���Ѵ�)
																				

	if (LOCAL == _eSpace)
		D3DXQuaternionRotationYawPitchRoll(&m_quatQ, m_vAngle.y, m_vAngle.x, m_vAngle.z);	
		// DXQuaternionRotationAxis(&quat, &vAxis, *(((_float*)&m_vAngle) + _eDir));
		// �� �Լ��� ����ϰ��� �Ѵٸ�, x, y, z�� ���� ���ʹϾ��� ��� ���ѵ� ��� �����־�� �Ѵ�.
	else
	{
		//// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=spinx85&logNo=140120555548
		//_quat	qX, qY, qZ;

		//D3DXQuaternionRotationAxis(&qX	, &vec3.right	, m_vAngle.x);
		//D3DXQuaternionRotationAxis(&qY	, &vec3.up		, m_vAngle.y);
		//D3DXQuaternionRotationAxis(&qZ	, &vec3.forward	, m_vAngle.z);

		//m_quatQ = qY * qX * qZ;
		//
		//D3DXQuaternionNormalize(&m_quatQ, &m_quatQ);
	}

	Cal_WorldMat();				
}




void CTransform::Set_Pos(const _vec3 & _vPos)
{
	// ���� ���� _vPos�� �������� �����Ѵ�.

	memcpy(&m_matWorld.m[3][0]	, _vPos, sizeof(_vec3));
	memcpy(&m_vInfo[INFO_POS]	, _vPos, sizeof(_vec3));

	Cal_WorldMat();
}

void CTransform::Set_Rot(const _vec3& _vRot, const SPACEID _eSpace)
{
	if (LOCAL == _eSpace)
		D3DXQuaternionRotationYawPitchRoll(&m_quatQ, _vRot.y, _vRot.x, _vRot.z);

	Cal_WorldMat();

}

void CTransform::Set_Scale(const _vec3& _vPos)
{ 
	memcpy(&m_vScale, &_vPos, sizeof(_vec3));  Cal_WorldMat();  
	Cal_WorldMat();
}

void CTransform::Reverse()
{
	m_vScale.x *= -1;
	Cal_WorldMat();
}

void CTransform::Cal_WorldMat()
{
	// ����� ������ �������� ���� ��������� ����Ѵ�.

	_matrix matS, matR;

	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	
	D3DXMatrixRotationQuaternion(&matR, &m_quatQ);

	matS *= matR;

	if (nullptr != m_pOwnerObject && OBJ_TYPE::CAMERA != m_pOwnerObject->Get_Type() && OBJ_TYPE::TERRAIN != m_pOwnerObject->Get_Type())
	{
		_matrix matBill;
		matS *= CCameraMgr::GetInstance()->Get_Billboard_X();

		for (_int i = 0; i < INFO_POS; ++i)
			memcpy(&m_matWorld.m[i], &matS.m[i], sizeof(_vec3));

		// ������� ������ ���� ȸ���̹Ƿ� �������� ������ ��ġ�� �ȵȴ�. -> ���� ����� ������ �����ϸ� �ȵ�
	}
	else
	{
		for (_int i = 0; i < INFO_POS; ++i)
			memcpy(&m_matWorld.m[i], &matS.m[i], sizeof(_vec3));

		for (_int i = 0; i < INFO_POS; ++i)
			memcpy(&m_vInfo[i], &m_matWorld.m[i][0], sizeof(_vec3));
	}
	
}

HRESULT CTransform::Ready_Transform()
{
	// ��� Ʈ������ ������ �ʱ�ȭ�Ѵ�.

	ZeroMemory(&m_quatQ, sizeof(_quat));
	ZeroMemory(&m_vAngle, sizeof(_vec3));
	memcpy(&m_vScale, &vec3.one, sizeof(_vec3));
	D3DXMatrixIdentity(&m_matWorld);
	for (_int i = 0; i < INFO_END; ++i)
		memcpy(&m_vInfo[i], &m_matWorld.m[i][0], sizeof(_vec3));

	m_vDir = vec3.right;

	return S_OK;
}

_int CTransform::Update_Component(const _float& fTimeDelta)
{
	Cal_WorldMat();
	return 0;
}

CTransform * CTransform::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTransform*		pInstance = new CTransform(pGraphicDev);

	if (FAILED(pInstance->Ready_Transform()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Transform Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent * CTransform::Clone(CGameObject* _pOwnerObject)
{
	return new CTransform(*this, _pOwnerObject);
}

void CTransform::Free()
{
	CComponent::Free();
}
