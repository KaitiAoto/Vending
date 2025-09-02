//================================
//
// ���U���g����[result.h]
// Author:kaiti
//
//================================

// ��d�C���N���[�h�h�~
#ifndef _RESULT_H_
#define _RESULT_H_

//�C���N���[�h
#include "main.h"
#include "scene.h"
#include "object.h"
#include "score_manager.h"

// �}�N����`
#define RESULT_STAY (90)

// �O���錾
class CScene;
class CLoadStage;

// �}�l�[�W���[�N���X
class CResult:public CScene
{
public:
	// �����o�֐�
	CResult();
	~CResult();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	// �擾
	static CScoreMana* GetBreakCnt(void) { return m_pBreakCnt; }
	static CScoreMana* GetTotalScore(void) { return m_pTotalScore; }

private:

	// �����o�ϐ�
	int m_nCntStay;						// �ҋ@����

	// �ÓI�����o�ϐ�
	static CLoadStage* m_pStage;		// �ǂݍ��ރX�e�[�W�ւ̃|�C���^
	static CScoreMana* m_pBreakCnt;		// �j��X�R�A�}�l�[�W���[�ւ̃|�C���^
	static CScoreMana* m_pTotalScore;	// �g�[�^���X�R�A�}�l�[�W���[�ւ̃|�C���^
};

#endif