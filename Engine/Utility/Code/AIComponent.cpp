#include "..\..\Header\AIComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include <ctime>

CAIComponent::CAIComponent()
{
}

CAIComponent::CAIComponent(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev, COMPONENT_TYPE::AICOM)
{
}

CAIComponent::CAIComponent(const CAIComponent& rhs, CGameObject* _pOwnerObject)
	: CComponent(rhs, _pOwnerObject)
{
}

CAIComponent::~CAIComponent()
{
}

HRESULT CAIComponent::Ready_AICom()
{
	 
	return S_OK;
}

_int CAIComponent::Update_Component(const _float& fTimeDelta)
{
	return 0;
}


void CAIComponent::Random_Move( const _float& fTimeDelta, const _float& fSpeed)
{
	_int RandomDir;

	

	RandomDir = rand() % 5 + 1;


	switch (RandomDir)
	{
	case 1:
		m_pOwnerObject->Get_Transform()->Set_Dir(vec3.right);
		break;
	case 2:
		m_pOwnerObject->Get_Transform()->Set_Dir(vec3.left);
		break;
	case 3:
		m_pOwnerObject->Get_Transform()->Set_Dir(vec3.forward);
		break;
	case 4:
		m_pOwnerObject->Get_Transform()->Set_Dir(vec3.back);
		break;
	case 5:
		m_pOwnerObject->Get_Transform()->Set_Dir(vec3.zero);  // ����
	case 6:
		m_pOwnerObject->Get_Transform()->Set_Dir({1.f,0.f,1.f}); // ���� �밢 ��
		break;
	case 7:
		m_pOwnerObject->Get_Transform()->Set_Dir({ -1.f,0.f,1.f }); // �� �밢 ��
		break;
	case 8:
		m_pOwnerObject->Get_Transform()->Set_Dir({ 1.f,0.f,-1.f }); // ���� �밢 �Ʒ�
		break;
	case 9:
		m_pOwnerObject->Get_Transform()->Set_Dir({-1.f, 0.f, -1.f}); // �� �밢 �Ʒ� 
		break;
	default:
		m_pOwnerObject->Get_Transform()->Set_Dir(vec3.zero);
		break;
	}
	


};




void CAIComponent::Chase_Target(const _vec3* pTargetPos, const _float& fTimeDelta, const _float& fSpeed)
{

	_vec3 OwnerPos;
	OwnerPos = CComponent::Get_OwnerObject()->Get_Transform()->Get_Info(INFO_POS);

	_vec3 vDir = *pTargetPos - OwnerPos;

	OwnerPos += *D3DXVec3Normalize(&vDir, &vDir) * fTimeDelta * fSpeed;

	_matrix		matRot = *Compute_LookAtTarget(pTargetPos);
	_matrix		matScale, matTrans;

	_vec3	OwnerScale;
	OwnerScale = CComponent::Get_OwnerObject()->Get_Transform()->Get_Scale();
	D3DXMatrixScaling(&matScale, OwnerScale.x, OwnerScale.y, OwnerScale.z);
	
	D3DXMatrixTranslation(&matTrans, OwnerPos.x, OwnerPos.y, OwnerPos.z);


	_matrix		m_matWorld = CComponent::Get_OwnerObject()->Get_Transform()->Get_WorldMat();

	m_matWorld = matScale * matRot * matTrans;

	CComponent::Get_OwnerObject()->Get_Transform()->Set_Pos({ m_matWorld._41, m_matWorld._42, m_matWorld._43 });

}
const _matrix* CAIComponent::Compute_LookAtTarget(const _vec3* pTargetPos)
{
	
	_vec3 OwnerPos;
	OwnerPos = CComponent::Get_OwnerObject()->Get_Transform()->Get_Info(INFO_POS);

	_vec3 OwnerLook;
	OwnerLook = CComponent::Get_OwnerObject()->Get_Transform()->Get_Info(INFO_LOOK);
	
	_vec3 OwnerUp;
	OwnerUp = CComponent::Get_OwnerObject()->Get_Transform()->Get_Info(INFO_UP);

	_vec3 vDir = *pTargetPos - OwnerPos;

	_matrix		matRot;
	_vec3		vAxis;

	

	D3DXMatrixLookAtLH(&matRot, &OwnerPos, pTargetPos, &OwnerUp);

	return D3DXMatrixRotationAxis(
									&matRot,
									D3DXVec3Cross(&vAxis, &OwnerUp, &vDir),
									acosf(D3DXVec3Dot(D3DXVec3Normalize(&vDir, &vDir),
									D3DXVec3Normalize(&OwnerUp, &OwnerUp))));
	
	

}

CAIComponent* CAIComponent::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CAIComponent* pInstance = new CAIComponent(pGraphicDev);

	if (FAILED(pInstance->Ready_AICom()))
	{
		Safe_Release(pInstance);

		MSG_BOX("AIComponent Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent* CAIComponent::Clone(CGameObject* _pOwnerObject)
{
	return new CAIComponent(*this, _pOwnerObject);
}

void CAIComponent::Free()
{
	CComponent::Free();
}
