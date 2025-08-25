//==================================
//
//�@�E�C���h�E�\������[light.cpp]
//�@Author:kaiti
//
//==================================
#include "light.h"
#include "renderer.h"
#include "manager.h"
//================
// �R���X�g���N�^
//================
CLight::CLight(void)
{
	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		m_light[nCnt] = {}; //���C�g���
	}
}
//================
// �f�X�g���N�^
//================
CLight::~CLight()
{
}
//==================
// ���C�g�̏�����
//==================
HRESULT CLight::Init(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXVECTOR3 vecDir[MAX_LIGHT];

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//���C�g���N���A����
		ZeroMemory(&m_light, sizeof(m_light));

		//���C�g�̎�ނ�ݒ�
		m_light[nCnt].Type = D3DLIGHT_DIRECTIONAL;//���s����

		//���C�g�̊g�U����ݒ�
		m_light[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//���C�g�̐F

		//���C�g�̕�����ݒ�
 		vecDir[0] = D3DXVECTOR3(-0.52f, -0.59f, 0.62f);
		vecDir[1] = D3DXVECTOR3(0.37f, -0.63f, -0.68f);
		vecDir[2] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);

		//���K������i�傫���P�̃x�N�g���ɂ���j
		D3DXVec3Normalize(&vecDir[nCnt], &vecDir[nCnt]);
		m_light[nCnt].Direction = vecDir[nCnt];

		//���C�g��ݒ�
		pDevice->SetLight(nCnt, &m_light[nCnt]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCnt, TRUE);
	}	

	return S_OK;
}
//====================
// ���C�g�̏I������
//====================
void CLight::Uninit(void)
{

}
//====================
// ���C�g�̍X�V����
//====================
void CLight::Update(void)
{

}

void CLight::SetColor(D3DXCOLOR col)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXVECTOR3 vecDir[MAX_LIGHT];

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//���C�g���N���A����
		ZeroMemory(&m_light, sizeof(m_light));

		//���C�g�̎�ނ�ݒ�
		m_light[nCnt].Type = D3DLIGHT_DIRECTIONAL;//���s����

		m_light[nCnt].Diffuse = col;//���C�g�̐F

		//���C�g�̕�����ݒ�
		vecDir[0] = D3DXVECTOR3(-0.52f, -0.59f, 0.62f);
		vecDir[1] = D3DXVECTOR3(0.37f, -0.63f, -0.68f);
		vecDir[2] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);

		//���K������i�傫���P�̃x�N�g���ɂ���j
		D3DXVec3Normalize(&vecDir[nCnt], &vecDir[nCnt]);
		m_light[nCnt].Direction = vecDir[nCnt];

		//���C�g��ݒ�
		pDevice->SetLight(nCnt, &m_light[nCnt]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCnt, TRUE);
	}
}
