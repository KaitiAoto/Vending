//===================
//
// スコア[score.h]
// Author:kaiti
//
//===================
#ifndef SCORE_H_
#define SCORE_H_

#include "main.h"
#include "number.h"

#define SCORE_SIZE (25)

//オブジェクト2Dクラス
class CScore:public CObject
{
public:

	//メンバ関数
	CScore(int nPriority = 7);
	~CScore();
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	static int GetPriority(void) { return m_nPriority; }
	CNumber* GetNumber(void) { return m_pNumber; }

private:
	//メンバ変数
	static int m_nPriority;
	int m_nIdxTex;
	CNumber* m_pNumber;
};

#endif