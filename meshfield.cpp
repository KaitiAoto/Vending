//==============================================
//
// ���b�V�����\������[meshfield.cpp]
// Author : Kaiti Aoto
//
//==============================================
#include "meshfield.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//=================
// �R���X�g���N�^
//=================
CMeshField::CMeshField()
{
	m_pVtxBuff = NULL;
	m_nIdxTex = 0;

	m_pIdxBuff = NULL;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = {};
}
//===============
// �f�X�g���N�^
//===============
CMeshField::~CMeshField()
{

}
//============
// ��������
//============
CMeshField* CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	CMeshField* pMeshField;
	pMeshField = new CMeshField;
	//������
	pMeshField->Init(pos, rot, fWidth, fHeight);

	//�e�N�X�`�����蓖��
	CTexture* pTex = CManager::GetTex();
	pMeshField->m_nIdxTex = pTex->Register("data\\TEXTURE\\isi.jpg");

	return pMeshField;
}
//==================
// ����������
//==================
HRESULT CMeshField::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pos = pos;
	m_rot = rot;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VTX,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &m_pVtxBuff,
		                        NULL);
	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEX_NO,
							   D3DUSAGE_WRITEONLY,
							   D3DFMT_INDEX16,
							   D3DPOOL_MANAGED,
							   &m_pIdxBuff,
							   NULL);
	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int n = 0;
	for (int nCntZ = 0; nCntZ <= MESHVTX_Z; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= MESHVTX_X; nCntX++)
		{
			//���_���W�̐ݒ�
			float cellWidth = (fWidth * 2.0f) / MESHVTX_X;
			float cellHeight = (fHeight * 2.0f) / MESHVTX_Z;

			pVtx[n].pos = D3DXVECTOR3(-fWidth + (cellWidth * nCntX), 0.0f, fHeight - (cellHeight * nCntZ));
			//�@���x�N�g���̐ݒ�
			pVtx[n].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//���_�J���[�̐ݒ�
			pVtx[n].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//�e�N�X�`�����W�̐ݒ�
			pVtx[n].tex = D3DXVECTOR2((1.0f / MESHVTX_X) * nCntX, (1.0f / MESHVTX_Z) * nCntZ);

			n++;
		}
	}

	//���_�o�b�t�@���A�����b�N�@
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	
	int index = 0;
	for (int z = 0; z < MESHVTX_Z; ++z)
	{
		if (z > 0)
		{
			// �f�W�F�l���[�g�i�ŏ���2�j
			pIdx[index++] = (WORD)(z * (MESHVTX_X + 1));
			pIdx[index++] = (WORD)(z * (MESHVTX_X + 1));
		}

		for (int x = 0; x <= MESHVTX_X; ++x)
		{
			pIdx[index++] = (WORD)((z + 1) * (MESHVTX_X + 1) + x);
			pIdx[index++] = (WORD)(z * (MESHVTX_X + 1) + x);
		}
	}
	m_pIdxBuff->Unlock();

	SetObjType(TYPE_FIELD);//�I�u�W�F�N�g�̃^�C�v

	return S_OK;
}
//===============================
// ���b�V�����̏I������
//===============================
void CMeshField::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
	CObject::Release();
}
//===============================
// ���b�V�����̍X�V����
//===============================
void CMeshField::Update(void)
{

}
//===============================
// ���b�V�����̕`�揈��
//===============================
void CMeshField::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�e�N�X�`�����蓖��
	CTexture* pTex = CManager::GetTex();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

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

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTex->GetAddress(m_nIdxTex));

	//���b�V������`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_VTX, 0, POLYGON_NO);
}