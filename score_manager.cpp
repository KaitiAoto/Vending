//========================================
//
// �X�R�A�}�l�[�W���[[score_manager.h]
// Author : Kaiti Aoto
//
//========================================
#include "score_manager.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"

//==================
// �R���X�g���N�^
//==================
CScoreMana::CScoreMana()
{
	m_MaxScore = 0;
	m_ScoreData = 0;
}
//================
// �f�X�g���N�^
//================
CScoreMana::~CScoreMana()
{
}
//===========
// ��������
//===========
CScoreMana* CScoreMana::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col, int MaxScore)
{
	CScoreMana* pScoreMana = new CScoreMana;

	for (int nCnt = 0; nCnt < MaxScore; nCnt++)
	{
		pScoreMana->m_pScore[nCnt] = CScore::Create(D3DXVECTOR3(pos.x + (nCnt * fWidth * 2.5f), pos.y, 0.0f), fWidth, fHeight);
		pScoreMana->m_pScore[nCnt]->SetColor(col);
		pScoreMana->m_col = col;
	}
	pScoreMana->m_fWidth = fWidth;

	pScoreMana->Init(MaxScore);

	return pScoreMana;
}
//===============
// ����������
//===============
HRESULT CScoreMana::Init(int MaxScore)
{
	//������
	m_nScore = 0;
	m_nCntUp = 0;
	
	m_MaxScore = MaxScore;

	m_ScoreData = 1;
	for (int nCnt = 0; nCnt < m_MaxScore - 1; nCnt++)
	{
		m_ScoreData *= 10;
	}

	return S_OK;
}
//============
// �I������
//============
void CScoreMana::Uninit(void)
{
	m_nScore = 0;
}
//============
// �X�V����
//============
void CScoreMana::Update(void)
{
	if (m_nCntUp < m_nScore)
	{
		//�ڕW�̃X�R�A�ƕ\���̃X�R�A�̍������v�Z
		int nDiff = m_nScore - m_nCntUp;

		//������10���̂P�̒l�𑫂�
		int nAdd = max(1, nDiff / 10);//�����l���v�Z
		m_nCntUp += nAdd;//���Z

		if (m_nCntUp >= m_nScore)
		{//�ڕW�̒l�𒴂��Ȃ��悤�ɂ���
			m_nCntUp = m_nScore;
		}

		//�����؂�ւ�
		ChangeTex();
	}
}
//============
// �`�揈��
//============
void CScoreMana::Draw(void)
{
}
//==============
// �X�R�A���Z
//==============
void CScoreMana::AddScore(int nAdd)
{
	if (CGame::GetMode() == CGame::MODE_PLAY)
	{
		m_nScore += nAdd;
	}
}
//================
// �ʒu�ݒ�
//================
void CScoreMana::SetPos(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < m_MaxScore; nCnt++)
	{
		m_pScore[nCnt]->GetNumber()->SetPos({ pos.x + (nCnt * m_fWidth * 2.5f), pos.y, pos.z });
	}
}
//============
// �F�ݒ�
//============
void CScoreMana::SetAlpha(float fAlpha)
{
	m_col.a = fAlpha;

	for (int nCnt = 0; nCnt < m_MaxScore; nCnt++)
	{
		m_pScore[nCnt]->GetNumber()->SetColor((m_col));
	}
}
//===================
// �����؂�ւ�
//===================
void CScoreMana::ChangeTex(void)
{
	int aPosTexU;
	if (m_nCntUp <= 0)
	{
		m_nCntUp = 0;
	}

	int nData = m_ScoreData * 10;
	int nData2 = m_ScoreData;
	for (int nCnt = 0; nCnt < m_MaxScore; nCnt++)
	{
		if (m_pScore[nCnt] != nullptr)
		{
			CNumber* pNumber = m_pScore[nCnt]->GetNumber();

			aPosTexU = m_nCntUp % nData / nData2;
			nData /= 10;
			nData2 /= 10;
			if (pNumber != nullptr)
			{
				pNumber->SetTex((aPosTexU * 0.1f), (aPosTexU * 0.1f) + 0.1f, 0.0f, 1.0f);
			}
		}
	}
}
