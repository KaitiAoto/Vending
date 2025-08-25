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

	static CScoreMana* GetScoreMana(void) { return m_pScore; }

private:
	static CLoadStage* m_pStage;
	static CScoreMana* m_pScore;				//�X�R�A�ւ̃|�C���^

	int m_nCntStay;
};

#endif