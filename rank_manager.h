//==============================================
//
// �����L���O�}�l�[�W���[[rank_manager.cpp]
// Author:kaiti
//
//==============================================

// ��d�C���N���[�h�h�~
#ifndef RANK_MANAGER_H_
#define RANK_MANAGER_H_

// �C���N���[�h
#include "main.h"
#include "score_manager.h"

// �}�N����`
#define MAX_RANK (5)
#define RANK_Y (4)

// �����L���O�}�l�[�W���[�N���X
class CRankMana
{
public:

	// �����o�֐�
	CRankMana();
	~CRankMana();
	HRESULT Init(D3DXVECTOR3 pos, const char* pTxtName, D3DXCOLOR col, int MaxScore);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Reset(void);

	// �ݒ�
	void Set(int nScore);
	void SetRankIn(int nScore);

	// �ÓI�����o�֐�
	static CRankMana* Create(D3DXVECTOR3 pos, const char* pTxtName, D3DXCOLOR col, int MaxScore);

private:
	void Move(void);
	void Blink(void);

	// �����o�ϐ�
	CScoreMana* m_pScore[MAX_RANK];	// �X�R�A�}�l�[�W���[�ւ̃|�C���^
	D3DXVECTOR3 m_posOffset;		// �ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 m_pos;				// �ʒu
	float m_fSize;					// �T�C�Y
	float m_AnimCnt[MAX_RANK];		// �A�j���J�E���g
	int m_nRankIn;					// �����N�C���ł�������
	int m_BlinkTime;				// �_�Ŏ���
	int m_nScore[MAX_RANK];			// �X�R�A
	char m_pTxtName[64];			// �e�L�X�g��
};

#endif