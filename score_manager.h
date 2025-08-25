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

#define MAX_SCORE (2)
#define SCOREDATA (10)

//オブジェクト2Dクラス
class CScoreMana
{
public:

	//メンバ関数
	CScoreMana();
	~CScoreMana();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScoreMana* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	static void AddScore(int nAdd);
	static void Set(int nScore) { m_nScore = nScore; ChangeTex();};

	static int GetScore(void) { return m_nScore; }
	static CScore* GetpScore(void) { return m_pScore[0]; }
private:
	static void ChangeTex(void);
	//メンバ変数
	static CScore* m_pScore[MAX_SCORE];	//オブジェクトへのポインタ

	static int m_nScore;
	static int m_nDigit;
};

#endif