//========================================
//
// スコアマネージャー[score_manager.cpp]
// Author:kaiti
//
//========================================
#ifndef RANK_MANAGER_H_
#define RANK_MANAGER_H_

#include "main.h"
#include "score_manager.h"

#define MAX_RANK (5)

//オブジェクト2Dクラス
class CRankMana
{
public:

	//メンバ関数
	CRankMana();
	~CRankMana();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRankMana* Create(D3DXVECTOR3 pos);

	static void Reset(void);

	static void Set(int nScore);
private:
	//メンバ変数
	static CScoreMana* m_pScore[MAX_RANK];	//オブジェクトへのポインタ

	static int m_nScore[MAX_RANK];

	static D3DXVECTOR3 m_posOffset;
	static D3DXVECTOR3 m_pos;
	static float m_fSize;
};

#endif