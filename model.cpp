//================================
//
// ���f���\������[objectX.cpp]
// Author:kaiti
//
//================================
#include "model.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "motion.h"
#include "debugproc.h"
//================
// �R���X�g���N�^
//================
CModel::CModel(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Offsetpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Offsetrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_mtxWorld = {};

	m_pMesh = NULL;		//���b�V��(���_���)�ւ̃|�C���^
	m_pBuffMat = NULL;	//�}�e���A���ւ̃|�C���^
	m_dwNumMat = 0;		//�}�e���A���̐�
	m_nIdxTex = 0;
	m_pParent = NULL;

	m_forcedColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bColorChange = false;
}
//================
// �f�X�g���N�^
//================
CModel::~CModel()
{
}
//===========
// ��������
//===========
CModel* CModel::Create(const char* pFilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CModel* pObjectX;
	pObjectX = new CModel;
	//������
	pObjectX->Init(pFilename, pos, rot);
	return pObjectX;
}
//================
//���f���̏�����
//================
HRESULT CModel::Init(const char* pFilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CTexture* pTex = CManager::GetTex();

	m_pos = pos;
	m_rot = rot;

	//X�t�@�C���̓ǂݍ���
	HRESULT hr = D3DXLoadMeshFromX(pFilename,
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
	for (DWORD i = 0; i < m_dwNumMat; i++) 
	{
		m_nIdxTex[i] = -1;  // ������
	}

	D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			int nIdx = pTex->Register(pMat[nCntMat].pTextureFilename);

			if (nIdx < 0)
			{//�G���[�`�F�b�N
				char msg[256];
				sprintf(msg, "�e�N�X�`���̓o�^�Ɏ��s���܂���: %s\n", pMat[nCntMat].pTextureFilename);
				OutputDebugStringA(msg);
				m_nIdxTex[nCntMat] = -1;
			}
			else
			{
				m_nIdxTex[nCntMat] = nIdx;  // �C���f�b�N�X��ۑ�
			}
		}
	}

	return S_OK;
}
//==================
//���f���̏I������
//==================
void CModel::Uninit(void)
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
		m_nIdxTex = NULL;
	}
}
//=================
//���f���̍X�V����
//=================
void CModel::Update(void)
{

}
//==============
//���f���̕`��
//===============
void CModel::Draw(void)
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
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y + m_Offsetrot.y, m_rot.x + m_Offsetrot.x, m_rot.z + m_Offsetrot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x + m_Offsetpos.x, m_pos.y + m_Offsetpos.y, m_pos.z + m_Offsetpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�e�̃}�g���b�N�X�Ɗ|�����킹��
	D3DXMATRIX mtxParent;
	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// �F��ς���
	D3DMATERIAL9 forcedMat = pMat[0].MatD3D;  // �����̃}�e���A�����R�s�[
	forcedMat.Diffuse = m_forcedColor;
	forcedMat.Ambient = forcedMat.Diffuse;


	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		LPDIRECT3DTEXTURE9 tex = nullptr;
		if (m_nIdxTex && m_nIdxTex[nCntMat] >= 0)
		{
			tex = pTex->GetAddress(m_nIdxTex[nCntMat]);
		}

		if (m_bColorChange == true)
		{
			// �}�e���A���������I�ɐݒ�
			pDevice->SetMaterial(&forcedMat);
		}
		else if(m_bColorChange == false)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		}
		pDevice->SetTexture(0, tex);

		//���f���̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	pDevice->SetMaterial(&matDef);
}
void CModel::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_rot = rot;
}
D3DXVECTOR3 CModel::SetSize(void)
{
	int nNumVtx;   //���_��
	DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���f���̍ŏ��l
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���f���̍ő�l

	//���_���擾
	nNumVtx = m_pMesh->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y�擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());
	//���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//���_���W���r���ăv���C���[�̍ŏ��l�A�ő�l���擾
		//�ŏ��l
		if (vtx.x < vtxMin.x)
		{
			vtxMin.x = vtx.x;
		}
		if (vtx.y < vtxMin.y)
		{
			vtxMin.y = vtx.y;
		}
		if (vtx.z < vtxMin.z)
		{
			vtxMin.z = vtx.z;
		}
		//�ő�l
		if (vtx.x > vtxMax.x)
		{
			vtxMax.x = vtx.x;
		}
		if (vtx.y > vtxMax.y)
		{
			vtxMax.y = vtx.y;
		}
		if (vtx.z > vtxMax.z)
		{
			vtxMax.z = vtx.z;
		}
		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	D3DXVECTOR3 size = D3DXVECTOR3(vtxMax.x - vtxMin.x, vtxMax.y - vtxMin.y, vtxMax.z - vtxMin.z);

	return size;
}
//=================
// ���f���ǂݍ���
//=================
void CModel::Load(const char* pFilename, CModel** model, int& outNumModel)
{
	D3DXVECTOR3 pos[NUM_MODEL];
	D3DXVECTOR3 rot[NUM_MODEL];

	for (int n = 0; n < NUM_MODEL; n++) {
		pos[n] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rot[n] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	int nNumModel = 0;
	int Index = 0;
	int nNum_Parts = 0;
	int nCntModel = 0;
	int nParent = 0;

	FILE* pFile = fopen(pFilename, "r");
	if (!pFile) return;

	char aString[MAX_WORD];
	fscanf(pFile, "%s", &aString[0]);

	if (strcmp(aString, "SCRIPT") == 0)
	{
		while (1)
		{
			fscanf(pFile, "%s", &aString[0]);
			if (aString[0] == '#') { fgets(aString, MAX_WORD, pFile); continue; }

			if (strcmp(aString, "NUM_MODEL") == 0)
			{
				fscanf(pFile, "%d", &nNumModel);
				outNumModel = nNumModel;
			}
			else if (strcmp(aString, "MODEL_FILENAME") == 0)
			{
				fscanf(pFile, "%s", &aString[0]);
				model[nCntModel] = CModel::Create(aString, pos[nCntModel], rot[nCntModel]);
				nCntModel++;
			}
			else if (strcmp(aString, "CHARACTERSET") == 0)
			{
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);
					if (aString[0] == '#') { fgets(aString, MAX_WORD, pFile); continue; }

					if (strcmp(aString, "NUM_PARTS") == 0)
					{
						fscanf(pFile, "%d", &nNum_Parts);
					}
					else if (strcmp(aString, "PARTSSET") == 0)
					{
						while (1)
						{
							fscanf(pFile, "%s", &aString[0]);
							if (aString[0] == '#') { fgets(aString, MAX_WORD, pFile); continue; }

							if (strcmp(aString, "INDEX") == 0)
							{
								fscanf(pFile, "%d", &Index);
							}
							else if (strcmp(aString, "PARENT") == 0)
							{
								fscanf(pFile, "%d", &nParent);
								model[Index]->SetParent(model[nParent]);
							}
							else if (strcmp(aString, "POS") == 0)
							{
								fscanf(pFile, "%f", &pos[Index].x);
								fscanf(pFile, "%f", &pos[Index].y);
								fscanf(pFile, "%f", &pos[Index].z);
							}
							else if (strcmp(aString, "ROT") == 0)
							{
								fscanf(pFile, "%f", &rot[Index].x);
								fscanf(pFile, "%f", &rot[Index].y);
								fscanf(pFile, "%f", &rot[Index].z);
							}
							else if (strcmp(aString, "END_PARTSSET") == 0)
							{
								model[Index]->SetOffSet(pos[Index], rot[Index]);
								break;
							}
						}
					}
					else if (strcmp(aString, "END_CHARACTERSET") == 0)
					{
						break;
					}
				}
			}
			else if (strcmp(aString, "END_SCRIPT") == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);
}