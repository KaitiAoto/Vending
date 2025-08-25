//========================================
//
// スコアマネージャー[score_manager.h]
// Author:kaiti
//
//========================================
#include "score_manager.h"
#include "renderer.h"
#include "manager.h"
//静的メンバ変数
int CScoreMana::m_nScore = 0;
int CScoreMana::m_nDigit = 0;
CScore* CScoreMana::m_pScore[MAX_SCORE] = {};

//==================
// コンストラクタ
//==================
CScoreMana::CScoreMana()
{
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
// 初期化処理
//===============
HRESULT CScoreMana::Init(void)
{
	//初期化
	
	return S_OK;
}
//============
// 終了処理
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
	m_nScore += nAdd;
	ChangeTex();
}

void CScoreMana::ChangeTex(void)
{
	int aPosTexU[MAX_SCORE]; //桁数分	
	if (m_nScore <= 0)
	{
		m_nScore = 0;
	}

	int nData = SCOREDATA * 10;
	int nData2 = SCOREDATA;
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_pScore[nCnt] != nullptr)
		{//オブジェクトが敵なら
			CNumber* pNumber = m_pScore[nCnt]->GetNumber();

			aPosTexU[nCnt] = m_nScore % nData / nData2;
			nData /= 10;
			nData2 /= 10;

			pNumber->SetTex((aPosTexU[nCnt] * 0.1f), (aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f, 1.0f);
		}
	}
}
