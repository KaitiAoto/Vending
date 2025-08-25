//================================
//
// リザルト処理[result.h]
// Author:kaiti
//
//================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "scene.h"
#include "object.h"
#include "score_manager.h"

////マクロ定義
#define RESULT_STAY (90)

class CScene;
class CLoadStage;

//マネージャークラス
class CResult:public CScene
{
public:
	//メンバ関数
	CResult();
	~CResult();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScoreMana* GetScoreMana(void) { return m_pScore; }

private:
	static CLoadStage* m_pStage;
	static CScoreMana* m_pScore;				//スコアへのポインタ

	int m_nCntStay;
};

#endif