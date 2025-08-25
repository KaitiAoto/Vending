//==============================================
//
// ���b�V���~���\������[MeshCircle.cpp]
// Author:kaiti
//
//==============================================
#include "meshcircle.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//==================
// �R���X�g���N�^
//==================
CMeshCircle::CMeshCircle(int nPriority):CObject(nPriority)
{
	m_pVtxBuff = nullptr;
	m_nIdxTex = 0;
	m_pIdxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = {};
	m_type = TYPE_IN;
	m_bUse = true;
}
//================
// �f�X�g���N�^
//================
CMeshCircle::~CMeshCircle()
{

}
//============
// ��������
//============
CMeshCircle* CMeshCircle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, D3DXCOLOR col, TYPE type)
{
	CMeshCircle* pMesh;
	pMesh = new CMeshCircle;
	//������
	pMesh->Init(pos, rot, fRadius, col, type);

	return pMesh;
}
//==================
// ����������
//==================
HRESULT CMeshCircle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, D3DXCOLOR col, TYPE type)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pos = pos;
	m_rot = rot;
	m_type = type;
	m_bUse = true;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAXCIRCLE_VTX,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &m_pVtxBuff,
		                        NULL);

	int stripCount = (MESHCIRCLEVTX_X + 1) * 2 + 2; // 1�X�g���b�v�̃C���f�b�N�X��
	int stripTotal = MESHCIRCLEVTX_X;              // �X�g���b�v���iZ�����j
	int nIndexCount = stripCount * stripTotal;

	if (type == TYPE_BOTHSIDES)
	{
		nIndexCount *= 2; // ���ʕ�
	}
	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * nIndexCount,
							   D3DUSAGE_WRITEONLY,
							   D3DFMT_INDEX16,
							   D3DPOOL_MANAGED,
							   &m_pIdxBuff,
							   NULL);

	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�~��
	int index = 0;
	float fAngle = (D3DX_PI * 2.0f) / MESHCIRCLEVTX_X;

	for (int nCntV = 0; nCntV < MESHCIRCLEVTX_Z + 1; nCntV++)
	{
		for (int nCntH = 0; nCntH < MESHCIRCLEVTX_X + 1; nCntH++)
		{
			//�p�x
			float Angle = fAngle * nCntH;

			//���_���W�̐ݒ�
			pVtx[index].pos = D3DXVECTOR3(cosf(Angle) * fRadius, 0.0f, sinf(Angle) * fRadius);
			
			D3DXVECTOR3 nor;//�ʒu
			nor = pVtx[index].pos - m_pos;

			//�@���x�N�g��
			D3DXVec3Normalize(&pVtx[index].nor,&nor);

			//���_�J���[�̐ݒ�
			pVtx[index].col = col;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[index].tex = D3DXVECTOR2((float)nCntH, (float)nCntV / 2);

			index++;
		}
	}

	//���_�o�b�t�@���A�����b�N�@
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	
	int nCntX;
	int idx = 0;
	for (int nCntZ = 0; nCntZ < MESHCIRCLEVTX_Z; nCntZ++)
	{
		for (nCntX = 0; nCntX <= MESHCIRCLEVTX_X; nCntX++)
		{
			int i0 = (WORD)nCntX + (nCntZ * (MESHCIRCLEVTX_X + 1));
			int i1 = nCntX + ((nCntZ + 1) * (MESHCIRCLEVTX_X + 1));

			if (type == TYPE_IN)
			{
				pIdx[idx++] = (WORD)i1;
				pIdx[idx++] = (WORD)i0;
			}
			else if (type == TYPE_OUT)
			{
				pIdx[idx++] = (WORD)i0;
				pIdx[idx++] = (WORD)i1;
			}
			else if (type == TYPE_BOTHSIDES)
			{
				// �O����
				pIdx[idx++] = (WORD)i0;
				pIdx[idx++] = (WORD)i1;
			}
		}

		// �f�B�O�i���g���C�A���O���i�f�K���|���S���j�ŃX�g���b�v����؂�
		if (nCntZ < MESHCIRCLEVTX_Z - 1)
		{
			int i = (nCntX - 1) + (nCntZ * (MESHCIRCLEVTX_X + 1));
			pIdx[idx++] = (WORD)i;
			pIdx[idx++] = (WORD)i;
		}
	}

	// ���ʕ`��̗��ʕ���ǉ��i���ԋt�ŃC���f�b�N�X�č\�z�j
	if (type == TYPE_BOTHSIDES)
	{
		for (int nCntZ = 0; nCntZ < MESHCIRCLEVTX_Z; nCntZ++)
		{
			for (nCntX = 0; nCntX <= MESHCIRCLEVTX_X; nCntX++)
			{
				int i0 = nCntX + (nCntZ * (MESHCIRCLEVTX_X + 1));
				int i1 = nCntX + ((nCntZ + 1) * (MESHCIRCLEVTX_X + 1));

				// �������i�t���j
				pIdx[idx++] = (WORD)i1;
				pIdx[idx++] = (WORD)i0;
			}

			if (nCntZ < MESHCIRCLEVTX_Z - 1)
			{
				int i = (nCntX - 1) + (nCntZ * (MESHCIRCLEVTX_X + 1));
				pIdx[idx++] = (WORD)i;
				pIdx[idx++] = (WORD)i;
			}
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}
//===============================
// ���b�V���~���̏I������
//===============================
void CMeshCircle::Uninit(void)
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
// ���b�V���~���̍X�V����
//===============================
void CMeshCircle::Update(void)
{

}
//===============================
// ���b�V���~���̕`�揈��
//===============================
void CMeshCircle::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	if (m_bUse == true)
	{
		//���C�g�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		//ALPHA�e�X�g�̐ݒ�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

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
		pDevice->SetTexture(0, NULL);

		DWORD oldCullMode;
		// ���݂̃J�����O�ݒ��ۑ�
		pDevice->GetRenderState(D3DRS_CULLMODE, &oldCullMode);

		// �^�C�v�ɉ����ăJ�����O�ݒ��؂�ւ�
		switch (m_type)
		{
		case TYPE_OUT:
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
			break;

		case TYPE_IN:
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			break;

		case TYPE_BOTHSIDES:
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			break;
		}
		//���b�V���~����`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN, 0, 0, MAXCIRCLE_VTX, 0, CIRCLEPOLYGON_NO);

		// �`���A���̃J�����O�ݒ�ɖ߂�
		pDevice->SetRenderState(D3DRS_CULLMODE, oldCullMode);

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		//���C�g��L���ɖ߂�
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}