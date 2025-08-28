//========================================
//
// スコアマネージャー[score_manager.h]
// Author:kaiti
//
//========================================
#include "score_manager.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"

//==================
// コンストラクタ
//==================
CScoreMana::CScoreMana()
{
	m_MaxScore = 0;
	m_ScoreData = 0;
}
//================
// デストラクタ
//================
CScoreMana::~CScoreMana()
{
}
//===========
// 生成処理
//===========
CScoreMana* CScoreMana::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int MaxScore)
{
	CScoreMana* pScoreMana = new CScoreMana;

	for (int nCnt = 0; nCnt < MaxScore; nCnt++)
	{
		pScoreMana->m_pScore[nCnt] = CScore::Create(D3DXVECTOR3(pos.x + (nCnt * fWidth * 2.5f), pos.y, 0.0f), fWidth, fHeight);
	}
	pScoreMana->m_fWidth = fWidth;

	pScoreMana->Init(MaxScore);

	return pScoreMana;
}
//===============
// 初期化処理
//===============
HRESULT CScoreMana::Init(int MaxScore)
{
	//初期化
	m_nScore = 0;
	
	m_MaxScore = MaxScore;

	m_ScoreData = 1;
	for (int nCnt = 0; nCnt < m_MaxScore - 1; nCnt++)
	{
		m_ScoreData *= 10;
	}

	return S_OK;
}
//============
// 終了処理
//============
void CScoreMana::Uninit(void)
{
	m_nScore = 0;
}
//============
// 更新処理
//============
void CScoreMana::Update(void)
{

}
//============
// 描画処理
//============
void CScoreMana::Draw(void)
{
}
//==============
// スコア加算
//==============
void CScoreMana::AddScore(int nAdd)
{
	if (CGame::GetMode() == CGame::MODE_PLAY)
	{
		m_nScore += nAdd;
		ChangeTex();
	}
}
//================
// 位置設定
//================
void CScoreMana::SetPos(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < m_MaxScore; nCnt++)
	{
		m_pScore[nCnt]->GetNumber()->SetPos({ pos.x + (nCnt * m_fWidth * 2.5f), pos.y, pos.z });
	}
}
//============
// 色設定
//============
void CScoreMana::SetColor(D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < m_MaxScore; nCnt++)
	{
		m_pScore[nCnt]->GetNumber()->SetColor(col);
	}
}
//===================
// 数字切り替え
//===================
void CScoreMana::ChangeTex(void)
{
	int aPosTexU;
	if (m_nScore <= 0)
	{
		m_nScore = 0;
	}

	int nData = m_ScoreData * 10;
	int nData2 = m_ScoreData;
	for (int nCnt = 0; nCnt < m_MaxScore; nCnt++)
	{
		if (m_pScore[nCnt] != nullptr)
		{
			CNumber* pNumber = m_pScore[nCnt]->GetNumber();

			aPosTexU = m_nScore % nData / nData2;
			nData /= 10;
			nData2 /= 10;

			pNumber->SetTex((aPosTexU * 0.1f), (aPosTexU * 0.1f) + 0.1f, 0.0f, 1.0f);
		}
	}
}
