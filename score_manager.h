//========================================
//
// �X�R�A�}�l�[�W���[[score_manager.cpp]
// Author:kaiti
//
//========================================
#ifndef SCORE_MANAGER_H_
#define SCORE_MANAGER_H_

#include "main.h"
#include "score.h"

#define MAX_SCORE (2)
#define SCOREDATA (10)

//�I�u�W�F�N�g2D�N���X
class CScoreMana
{
public:

	//�����o�֐�
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
	//�����o�ϐ�
	static CScore* m_pScore[MAX_SCORE];	//�I�u�W�F�N�g�ւ̃|�C���^

	static int m_nScore;
	static int m_nDigit;
};

#endif