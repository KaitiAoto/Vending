//========================================
//
// スコアマネージャー[score_manager.cpp]
// Author:kaiti
//
//========================================

// 二重インクルード防止
#ifndef SCORE_MANAGER_H_
#define SCORE_MANAGER_H_

// インクルード
#include "main.h"
#include "score.h"

// マクロ定義
#define MAX_SCORE (10)
#define SCOREDATA (10)

// スコアマネージャークラス
class CScoreMana
{
public:

	// メンバ関数
	CScoreMana();
	~CScoreMana();
	HRESULT Init(int MaxScore);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddScore(int nAdd);
	
	// 設定
	void Set(int nScore) { m_nScore = nScore; ChangeTex();};
	void SetPos(D3DXVECTOR3 pos);
	void SetAlpha(float fAlpha);
	// 取得
	int GetScore(void) { return m_nScore; }

	// 静的メンバ関数
	static CScoreMana* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col, int MaxScore);

private:
	void ChangeTex(void);

	// メンバ変数
	D3DXCOLOR m_col;				// 色
	CScore* m_pScore[MAX_SCORE];	// スコアへのポインタ
	int m_nScore;					// 現在のスコア
	int m_nCntUp;					// カウントアップで表示するスコア
	int m_MaxScore;					// スコアの最大桁数
	int m_ScoreData;				// 表示テクスチャ計算用
	float m_fWidth;					// 横幅

};

#endif