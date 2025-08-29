//========================================
//
// �X�R�A�}�l�[�W���[[score_manager.cpp]
// Author:kaiti
//
//========================================
#ifndef RANK_MANAGER_H_
#define RANK_MANAGER_H_

#include "main.h"
#include "score_manager.h"

#define MAX_RANK (5)
#define RANK_Y (4)

//�I�u�W�F�N�g2D�N���X
class CRankMana
{
public:

	//�����o�֐�
	CRankMana();
	~CRankMana();
	HRESULT Init(D3DXVECTOR3 pos, const char* pTxtName, D3DXCOLOR col, int MaxScore);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRankMana* Create(D3DXVECTOR3 pos, const char* pTxtName, D3DXCOLOR col, int MaxScore);

	void Reset(void);

	void Set(int nScore);
	void SetRankIn(int nScore);
private:
	void Move(void);
	void Blink(void);

	//�����o�ϐ�
	CScoreMana* m_pScore[MAX_RANK];	//�I�u�W�F�N�g�ւ̃|�C���^

	int m_nScore[MAX_RANK];

	D3DXVECTOR3 m_posOffset;
	D3DXVECTOR3 m_pos;
	float m_fSize;

	float m_AnimCnt[MAX_RANK];

	int m_nRankIn;
	int m_BlinkTime;

	char m_pTxtName[64];
};

#endif