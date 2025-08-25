//========================================
//
// �X�R�A�}�l�[�W���[[score_manager.h]
// Author:kaiti
//
//========================================
#include "score_manager.h"
#include "renderer.h"
#include "manager.h"
//�ÓI�����o�ϐ�
int CScoreMana::m_nScore = 0;
int CScoreMana::m_nDigit = 0;
CScore* CScoreMana::m_pScore[MAX_SCORE] = {};

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
		m_pScore[nCnt] = CScore::Create(D3DXVECTOR3(pos.x + (nCnt * fWidth * 2.5f), pos.y, 0.0f), fWidth, fHeight);
	}

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
	//for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	//{
	//	if (m_pScore[nCnt] != nullptr)
	//	{
	//		m_pScore[nCnt]->Uninit();
	//	}
	//}
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
		{//�I�u�W�F�N�g���G�Ȃ�
			CNumber* pNumber = m_pScore[nCnt]->GetNumber();

			aPosTexU[nCnt] = m_nScore % nData / nData2;
			nData /= 10;
			nData2 /= 10;

			pNumber->SetTex((aPosTexU[nCnt] * 0.1f), (aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f, 1.0f);
		}
	}
}
