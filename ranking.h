//================================
//
// �����L���O[ranking.h]
// Author:kaiti
//
//================================

// ��d�C���N���[�h�h�~
#ifndef _RANKING_H_
#define _RANKING_H_

// �C���N���[�h
#include "main.h"
#include "scene.h"
#include "object.h"
#include "rank_manager.h"

// �}�N����`
#define RANK_STAY (90)
#define RANKSCORE_SIZE (15)

// �O���錾
class CScene;
class CLoadStage;

// �����L���O�N���X
class CRanking:public CScene
{
public:
	// �����o�֐�
	CRanking();
	~CRanking();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	// �擾
	static CRankMana* GetBreakRankMana(void) { return m_pBreakRank; }
	static CRankMana* GetTotalRankMana(void) { return m_pTotalRank; }
	// �ݒ�
	static void SetNowScore(int nBreakScore, int nTotalScore);
private:
	// �����o�ϐ�
	int m_nCntStay;					// �ҋ@����

	// �ÓI�����o�ϐ�
	static CLoadStage* m_pStage;	// �ǂݍ��ރX�e�[�W�ւ̃|�C���^
	static CRankMana* m_pBreakRank;	// �j�󃉃��L���O�}�l�[�W���[�ւ̃|�C���^
	static CRankMana* m_pTotalRank;	// �g�[�^�������L���O�}�l�[�W���[�ւ̃|�C���^

};

#endif