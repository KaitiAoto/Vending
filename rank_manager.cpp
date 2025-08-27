//========================================
//
// �X�R�A�}�l�[�W���[[score_manager.h]
// Author:kaiti
//
//========================================
#include "rank_manager.h"
#include "renderer.h"
#include "manager.h"
#include "easing.h"
#include "debugproc.h"
//==================
// �R���X�g���N�^
//==================
CRankMana::CRankMana()
{
	m_nRankIn = -1;
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		m_AnimCnt[nCnt] = 0.0f;
	}
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

	//���ʃe�N�X�`��
	const char* apFileName[MAX_RANK] =
	{
		"data\\TEXTURE\\rank01.png",
		"data\\TEXTURE\\rank02.png",
		"data\\TEXTURE\\rank03.png",
		"data\\TEXTURE\\rank04.png",
		"data\\TEXTURE\\rank05.png",
	};

	float fSize = RANKSCORE_SIZE * 1.5f;
	m_posOffset = pos;
	m_fSize = fSize;

	//������
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		m_pScore[nCnt] = CScoreMana::Create(D3DXVECTOR3(0.0f, pos.y + (nCnt * fSize * RANK_Y), 0.0f), fSize, fSize);
		m_pScore[nCnt]->Set(m_nScore[nCnt]);

		CObject2D::Create(apFileName[nCnt], D3DXVECTOR3(pos.x - (fSize * 4.0f), pos.y + (nCnt * fSize * RANK_Y), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), fSize * 2.0f, fSize * 2.0f, 7);
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
	Move();

	if (m_nRankIn != -1)
	{
		Blink();
	}
	else
	{
		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			m_pScore[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}
//===========
// �ړ�
//===========
void CRankMana::Move(void)
{
	const float MoveDuration = 120.0f;  //1�̃X�R�A�����荞�ރt���[����
	const float Stagger = 10.0f;        //���Ԃɂ��炷�t���[����
	const float startX = -500.0f;		//�J�n����X���W

	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		if (m_AnimCnt[nCnt] < MoveDuration + nCnt * Stagger)
		{
			m_AnimCnt[nCnt] += 1.0f;
		}

		//�x��
		float t = (m_AnimCnt[nCnt] - nCnt * Stagger) / MoveDuration;
		if (t < 0.0f) t = 0.0f;

		float posX;
		if (t >= 1.0f)
		{
			posX = m_posOffset.x;
		}
		else
		{
			// �e���C�[�W���O
			float ease = CEasing::OutElastic(t);
			posX = startX + (m_posOffset.x - startX) * ease;
		}

		CDebugProc* pDegub = CManager::GetDebug();
		pDegub->Print("�ʒu�F%.1f", posX);

		//�ʒu�X�V
		m_pScore[nCnt]->SetPos(D3DXVECTOR3(posX, m_posOffset.y + (nCnt * m_fSize * RANK_Y), 0.0f));
	}
}
//============
// �_��
//============
void CRankMana::Blink(void)
{
	const int nBlinkFrame = 20;//�_�Ńt���[����
	const int nBlinkTime = 60;
	const D3DXCOLOR BaseCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	const D3DXCOLOR BlinkCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	m_BlinkTime++;

	if ((m_BlinkTime / nBlinkFrame) % 2 == 0)
	{//�_���[�W�F�ɂ���
		if (m_pScore[m_nRankIn] != NULL)
		{
			m_pScore[m_nRankIn]->SetColor(BlinkCol);
		}
	}
	else
	{//�ʏ�F�ɖ߂�
		if (m_pScore[m_nRankIn] != NULL)
		{
			m_pScore[m_nRankIn]->SetColor(BaseCol);
		}
	}
	if (m_BlinkTime >= nBlinkTime)
	{
		m_BlinkTime = 0;
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
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		tempScore[nCnt] = m_nScore[nCnt];
	}
	tempScore[MAX_RANK] = nScore;

	//�\�[�g
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		for (int j = 0; j < MAX_RANK - nCnt; j++)
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
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		m_nScore[nCnt] = tempScore[nCnt];
		if (m_pScore[nCnt] != nullptr)
		{
			m_pScore[nCnt]->Set(m_nScore[nCnt]);
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

void CRankMana::SetRankIn(int nScore)
{
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		if (m_nScore[nCnt] == nScore)
		{
			m_nRankIn = nCnt;
			break;
		}
	}
}

