//==============================
//
// ���̋@[vender.cpp]
// Author : Kaiti Aoto
//
//==============================
#include "stage.h"
#include "renderer.h"
#include "manager.h"
//==================
// �R���X�g���N�^
//==================
CStage::CStage(int nPriority):CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_mtxWorld = {};

	m_pModel = NULL;
}
//================
// �f�X�g���N�^
//================
CStage::~CStage()
{

}
//===========
// ��������
//===========
CStage* CStage::Create(const char* pFilename, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CStage* pBullet = new CStage;
	if (!pBullet)
		return nullptr;

	if (FAILED(pBullet->Init(pFilename, pos, rot)))
	{
		delete pBullet;
		return nullptr;
	}

	return pBullet;
}
//===============
// ����������
//===============
HRESULT CStage::Init(const char* pFilename, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_rot = rot;

	//���f������
	m_pModel = CModel::Create(pFilename, m_pos, m_rot);
	m_size = m_pModel->SetSize();

	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_STAGE);

	return S_OK;
}
//============
// �I������
//============
void CStage::Uninit(void)
{
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
		delete m_pModel;
		m_pModel = NULL;
	}
	CObject::Release();
}
//============
// �X�V����
//============
void CStage::Update(void)
{

}
//============
// �`�揈��
//============
void CStage::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���f���`��
	m_pModel->Draw();
}