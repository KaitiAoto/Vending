//========================================
//
// �X�R�A�}�l�[�W���[[score_manager.h]
// Author:kaiti
//
//========================================
#include "rank_manager.h"
#include "renderer.h"
#include "manager.h"
//�ÓI�����o�ϐ�
CScoreMana* CRankMana::m_pScore[MAX_RANK] = {};
int CRankMana::m_nScore[MAX_RANK] = {};
D3DXVECTOR3 CRankMana::m_posOffset = {};
D3DXVECTOR3 CRankMana::m_pos = {};
float CRankMana::m_fSize = NULL;
//==================
// �R���X�g���N�^
//==================
CRankMana::CRankMana()
{
}
//================
// �f�X�g���N�^
//================
CRankMana::~CRankMana()
{
}
//===========
// ��������
//===========
CRankMana* CRankMana::Create(D3DXVECTOR3 pos)
{
	CRankMana* pScoreMana = new CRankMana;

	pScoreMana->Init(pos);

	return pScoreMana;
}
void CRankMana::Reset(void)
{
	FILE* pFile;
	// �����L���O�t�@�C����ǂݍ���� m_nScore �Ɋi�[
	pFile = fopen("data\\TEXT\\ranking.txt", "r");
	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fscanf(pFile, "%d", &m_nScore[nCnt]);
		}
		fclose(pFile);
	}
	else
	{
		// �t�@�C�������݂��Ȃ��ꍇ�͑S�� 0 �ŏ�����
		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			m_nScore[nCnt] = 0;
		}
	}
}
//===============
// ����������
//===============
HRESULT CRankMana::Init(D3DXVECTOR3 pos)
{
	Reset();

	const char* apFileName[MAX_RANK] =
	{
		"data\\TEXTURE\\rank01.png",
		"data\\TEXTURE\\rank02.png",
		"data\\TEXTURE\\rank03.png",
		"data\\TEXTURE\\rank04.png",
		"data\\TEXTURE\\rank05.png",
	};

	float fSize = SCORE_SIZE * 1.5f;
	m_posOffset = pos;
	m_fSize = fSize;

	//������
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		m_pScore[nCnt] = CScoreMana::Create(D3DXVECTOR3(0.0f, pos.y + (nCnt * fSize * 3.0f), 0.0f), fSize, fSize);
		m_pScore[nCnt]->Set(m_nScore[nCnt]);

		CObject2D::Create(apFileName[nCnt], D3DXVECTOR3(pos.x - (fSize * 4.0f), pos.y + (nCnt * fSize * 3.0f), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), fSize * 2.0f, fSize * 2.0f, 7);
	}

	return S_OK;
}
//============
// �I������
//============
void CRankMana::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		if (m_pScore[nCnt] != nullptr)
		{
			m_pScore[nCnt]->Uninit();
			delete m_pScore[nCnt];
			m_pScore[nCnt] = nullptr;
		}
	}
}
//============
// �X�V����
//============
void CRankMana::Update(void)
{
	m_pos.x += 10.0f;

	if (m_pos.x >= m_posOffset.x)
	{
		m_pos.x = m_posOffset.x;
	}

	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		m_pScore[nCnt]->GetpScore()->GetNumber()->SetPos({ m_pos.x, m_posOffset.y + (nCnt * m_fSize * 3.0f), 0.0f });
	}
}
//============
// �`�揈��
//============
void CRankMana::Draw(void)
{
}
//
//
//
void CRankMana::Set(int nScore)
{
	FILE* pFile;
	// �t�@�C����������X�R�A��ǂݍ���
	pFile = fopen("data\\TEXT\\ranking.txt", "r");
	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fscanf(pFile, "%d\n", &m_nScore[nCnt]);
		}
		fclose(pFile);
	}

	int tempScore[MAX_RANK + 1];
	for (int i = 0; i < MAX_RANK; i++)
	{
		tempScore[i] = m_nScore[i];
	}
	tempScore[MAX_RANK] = nScore;

	//�\�[�g
	for (int i = 0; i < MAX_RANK; i++)
	{
		for (int j = 0; j < MAX_RANK - i; j++)
		{
			if (tempScore[j] < tempScore[j + 1])
			{
				int tmp = tempScore[j];
				tempScore[j] = tempScore[j + 1];
				tempScore[j + 1] = tmp;
			}
		}
	}
	//��ʂ�ۑ�
	for (int i = 0; i < MAX_RANK; i++)
	{
		m_nScore[i] = tempScore[i];
		if (m_pScore[i] != nullptr)
		{
			m_pScore[i]->Set(m_nScore[i]);
		}
	}

	//�t�@�C���ɏ�������
	pFile = fopen("data\\TEXT\\ranking.txt", "w");
	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{//�ő僉���N����������
			fprintf(pFile, "%d\n", m_nScore[nCnt]);
		}
		//����
		fclose(pFile);
	}
	else
	{//�G���[�`�F�b�N
	}
}
