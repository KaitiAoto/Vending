//================================
//
// ���U���g����[result.h]
// Author:kaiti
//
//================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "scene.h"
#include "object.h"
#include "rank_manager.h"

//�}�N����`
#define RESULT_STAY (90)

class CScene;
class CLoadStage;

//�}�l�[�W���[�N���X
class CRanking:public CScene
{
public:
	//�����o�֐�
	CRanking();
	~CRanking();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRankMana* GetRankMana(void) { return m_pRankMana; }

	static void SetPendingScore(int score) { m_nPendingScore = score; }
    static int GetPendingScore() { return m_nPendingScore; }

private:
	static CLoadStage* m_pStage;
	static CRankMana* m_pRankMana;

	int m_nCntStay;

	static int m_nPendingScore;
};

#endif