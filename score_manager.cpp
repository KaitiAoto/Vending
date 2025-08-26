//========================================
//
// �X�R�A�}�l�[�W���[[score_manager.h]
// Author:kaiti
//
//========================================
#include "score_manager.h"
#include "renderer.h"
#include "manager.h"

//==================
// �R���X�g���N�^
//==================
CScoreMana::CScoreMana()
{
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
CScoreMana* CScoreMana::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CScoreMana* pScoreMana = new CScoreMana;

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		pScoreMana->m_pScore[nCnt] = CScore::Create(D3DXVECTOR3(pos.x + (nCnt * fWidth * 2.5f), pos.y, 0.0f), fWidth, fHeight);
	}
	pScoreMana->m_fWidth = fWidth;

	pScoreMana->Init();

	return pScoreMana;
}
//===============
// ����������
//===============
HRESULT CScoreMana::Init(void)
{
	//������
	
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
	m_nScore += nAdd;
	ChangeTex();
}
//================
// �ʒu�ݒ�
//================
void CScoreMana::SetPos(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_pScore[nCnt]->GetNumber()->SetPos({ pos.x + +(nCnt * m_fWidth * 2.5f), pos.y, pos.z });
	}
}
void CScoreMana::SetColor(D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_pScore[nCnt]->GetNumber()->SetColor(col);
	}
}

void CScoreMana::ChangeTex(void)
{
	int aPosTexU[MAX_SCORE]; //������	
	if (m_nScore <= 0)
	{
		m_nScore = 0;
	}

	int nData = SCOREDATA * 10;
	int nData2 = SCOREDATA;
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_pScore[nCnt] != nullptr)
		{
			CNumber* pNumber = m_pScore[nCnt]->GetNumber();

			aPosTexU[nCnt] = m_nScore % nData / nData2;
			nData /= 10;
			nData2 /= 10;

			pNumber->SetTex((aPosTexU[nCnt] * 0.1f), (aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f, 1.0f);
		}
	}
}
