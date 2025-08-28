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
#define RANK_STAY (90)
#define RANKSCORE_SIZE (15)
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

	static CRankMana* GetBreakRankMana(void) { return m_pBreakRank; }
	static CRankMana* GetTotalRankMana(void) { return m_pTotalRank; }

	static void SetNowScore(int nBreakScore, int nTotalScore);
private:
	static CLoadStage* m_pStage;
	static CRankMana* m_pBreakRank;
	static CRankMana* m_pTotalRank;

	int m_nCntStay;
};

#endif