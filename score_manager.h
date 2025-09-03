//========================================
//
// �X�R�A�}�l�[�W���[[score_manager.cpp]
// Author:kaiti
//
//========================================

// ��d�C���N���[�h�h�~
#ifndef SCORE_MANAGER_H_
#define SCORE_MANAGER_H_

// �C���N���[�h
#include "main.h"
#include "score.h"

// �}�N����`
#define MAX_SCORE (10)
#define SCOREDATA (10)

// �X�R�A�}�l�[�W���[�N���X
class CScoreMana
{
public:

	// �����o�֐�
	CScoreMana();
	~CScoreMana();
	HRESULT Init(int MaxScore);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddScore(int nAdd);
	
	// �ݒ�
	void Set(int nScore) { m_nScore = nScore; ChangeTex();};
	void SetPos(D3DXVECTOR3 pos);
	void SetAlpha(float fAlpha);
	// �擾
	int GetScore(void) { return m_nScore; }

	// �ÓI�����o�֐�
	static CScoreMana* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col, int MaxScore);

private:
	void ChangeTex(void);

	// �����o�ϐ�
	D3DXCOLOR m_col;				// �F
	CScore* m_pScore[MAX_SCORE];	// �X�R�A�ւ̃|�C���^
	int m_nScore;					// ���݂̃X�R�A
	int m_nCntUp;					// �J�E���g�A�b�v�ŕ\������X�R�A
	int m_MaxScore;					// �X�R�A�̍ő包��
	int m_ScoreData;				// �\���e�N�X�`���v�Z�p
	float m_fWidth;					// ����

};

#endif