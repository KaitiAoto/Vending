//================================
//
// ���f���\������[objectX.cpp]
// Author : Kaiti Aoto
//
//================================
#include "objectX.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
//================
// �R���X�g���N�^
//================
CObjectX::CObjectX(int nPriority) :CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = {};

	m_pMesh = NULL; //���b�V��(���_���)�ւ̃|�C���^
	m_pBuffMat = NULL;//�}�e���A���ւ̃|�C���^
	m_dwNumMat = 0;//�}�e���A���̐�
	m_nIdxTex = 0;
}
//================
// �f�X�g���N�^
//================
CObjectX::~CObjectX()
{
}
//===========
// ��������
//===========
CObjectX* CObjectX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CObjectX* pObjectX;
	pObjectX = new CObjectX;
	//������
	pObjectX->Init(pos, rot);
	return pObjectX;
}
//================
//���f���̏�����
//================
HRESULT CObjectX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CTexture* pTex = CManager::GetTex();

	m_pos = pos;
	m_rot = rot;

	//X�t�@�C���̓ǂݍ���
	HRESULT hr = D3DXLoadMeshFromX("data\\MODEL\\shadowS00.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	if (FAILED(hr))
	{
		// �G���[����
		return hr;
	}

	//�K�v���̃e�N�X�`���ւ�Index�̃|�C���^�𓮓I�m��
	m_nIdxTex = new int[m_dwNumMat];

	D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			int nIdx = pTex->Register(pMat[nCntMat].pTextureFilename);
			m_nIdxTex[nCntMat] = nIdx;  // �C���f�b�N�X��ۑ�
		}
	}

	return S_OK;
}
//==================
//���f���̏I������
//==================
void CObjectX::Uninit(void)
{
	//���b�V���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	//�}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
	if (m_nIdxTex != NULL)
	{
		delete[] m_nIdxTex;
		m_nIdxTex = nullptr;
	}
}
//=================
//���f���̍X�V����
//=================
void CObjectX::Update(void)
{

}
//==============
//���f���̕`��
//===============
void CObjectX::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�e�N�X�`���擾
	CTexture* pTex = CManager::GetTex();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;
	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽓]
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//�e�N�X�`���̐ݒ�
		if (m_nIdxTex[nCntMat] >= 0)
		{
			pDevice->SetTexture(0, pTex->GetAddress(m_nIdxTex[nCntMat]));
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}
		//���f���̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	pDevice->SetMaterial(&matDef);
}
//
//
//
void CObjectX::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_rot = rot;
}