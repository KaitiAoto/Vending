//========================================
//
// スコアマネージャー[score_manager.cpp]
// Author:kaiti
//
//========================================
#ifndef SCORE_MANAGER_H_
#define SCORE_MANAGER_H_

#include "main.h"
#include "score.h"

#define MAX_SCORE (10)
#define SCOREDATA (10)

//オブジェクト2Dクラス
class CScoreMana
{
public:

	//メンバ関数
	CScoreMana();
	~CScoreMana();
	HRESULT Init(int MaxScore);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScoreMana* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col, int MaxScore);
	void AddScore(int nAdd);
	void Set(int nScore) { m_nScore = nScore; ChangeTex();};

	int GetScore(void) { return m_nScore; }
	void SetPos(D3DXVECTOR3 pos);
	void SetAlpha(float fAlpha);
private:
	void ChangeTex(void);
	//メンバ変数
	CScore* m_pScore[MAX_SCORE];	//オブジェクトへのポインタ

	int m_nScore;
	int m_nCntUp;
	int m_nDigit;

	float m_fWidth;

	int m_MaxScore;
	int m_ScoreData;

	D3DXCOLOR m_col;
};

#endif