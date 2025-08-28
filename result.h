//================================
//
// ���U���g����[result.h]
// Author:kaiti
//
//================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "scene.h"
#include "object.h"
#include "score_manager.h"

////�}�N����`
#define RESULT_STAY (90)

class CScene;
class CLoadStage;

//�}�l�[�W���[�N���X
class CResult:public CScene
{
public:
	//�����o�֐�
	CResult();
	~CResult();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScoreMana* GetBreakCnt(void) { return m_pBreakCnt; }
	static CScoreMana* GetTotalScore(void) { return m_pTotalScore; }

private:
	static CLoadStage* m_pStage;
	static CScoreMana* m_pBreakCnt;				//�X�R�A�ւ̃|�C���^
	static CScoreMana* m_pTotalScore;			//�X�R�A�ւ̃|�C���^

	int m_nCntStay;
};

#endif