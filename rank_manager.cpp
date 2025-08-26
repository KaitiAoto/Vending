//========================================
//
// スコアマネージャー[score_manager.h]
// Author:kaiti
//
//========================================
#include "rank_manager.h"
#include "renderer.h"
#include "manager.h"
#include "easing.h"
//静的メンバ変数
CScoreMana* CRankMana::m_pScore[MAX_RANK] = {};
int CRankMana::m_nScore[MAX_RANK] = {};
D3DXVECTOR3 CRankMana::m_posOffset = {};
D3DXVECTOR3 CRankMana::m_pos = {};
float CRankMana::m_fSize = NULL;
//==================
// コンストラクタ
//==================
CRankMana::CRankMana()
{
}
//================
// デストラクタ
//================
CRankMana::~CRankMana()
{
}
//===========
// 生成処理
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
	// ランキングファイルを読み込んで m_nScore に格納
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
		// ファイルが存在しない場合は全て 0 で初期化
		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			m_nScore[nCnt] = 0;
		}
	}
}
//===============
// 初期化処理
//===============
HRESULT CRankMana::Init(D3DXVECTOR3 pos)
{
	Reset();

	//順位テクスチャ
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

	//初期化
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		m_pScore[nCnt] = CScoreMana::Create(D3DXVECTOR3(0.0f, pos.y + (nCnt * fSize * 3.0f), 0.0f), fSize, fSize);
		m_pScore[nCnt]->Set(m_nScore[nCnt]);

		CObject2D::Create(apFileName[nCnt], D3DXVECTOR3(pos.x - (fSize * 4.0f), pos.y + (nCnt * fSize * 3.0f), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), fSize * 2.0f, fSize * 2.0f, 7);
	}

	return S_OK;
}
//============
// 終了処理
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
// 更新処理
//============
void CRankMana::Update(void)
{	
	const float MoveDuration = 120.0f;  //1つのスコアが滑り込むフレーム数
	const float Stagger = 10.0f;        //順番にずらすフレーム差
	const float startX = -500.0f;		//開始時のX座標

	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		//各スコア用のカウンター
		static float AnimCnt[MAX_RANK] = { 0 };

		if (AnimCnt[nCnt] < MoveDuration)
		{
			AnimCnt[nCnt] += 1.0f;
		}

		//遅延
		float t = (AnimCnt[nCnt] - nCnt * Stagger) / MoveDuration;
		if (t < 0.0f) t = 0.0f;
		if (t > 1.0f) t = 1.0f;

		// 弾性イージング
		float ease = CEasing::OutElastic(t);

		m_pos.x = startX + (m_posOffset.x - startX) * ease;

		//位置更新
		m_pScore[nCnt]->SetPos(D3DXVECTOR3(m_pos.x, m_posOffset.y + (nCnt * m_fSize * 3.0f), 0.0f));
	}
}
//============
// 描画処理
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
	// ファイルから既存スコアを読み込む
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

	//ソート
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
	//上位を保存
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		m_nScore[nCnt] = tempScore[nCnt];
		if (m_pScore[nCnt] != nullptr)
		{
			m_pScore[nCnt]->Set(m_nScore[nCnt]);
		}
	}

	//ファイルに書き込む
	pFile = fopen("data\\TEXT\\ranking.txt", "w");
	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{//最大ランク分書き込む
			fprintf(pFile, "%d\n", m_nScore[nCnt]);
		}
		//閉じる
		fclose(pFile);
	}
	else
	{//エラーチェック
	}
}
