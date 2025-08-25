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

//�I�u�W�F�N�g2D�N���X
class CRankMana
{
public:

	//�����o�֐�
	CRankMana();
	~CRankMana();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRankMana* Create(D3DXVECTOR3 pos);

	static void Reset(void);

	static void Set(int nScore);
private:
	//�����o�ϐ�
	static CScoreMana* m_pScore[MAX_RANK];	//�I�u�W�F�N�g�ւ̃|�C���^

	static int m_nScore[MAX_RANK];

	static D3DXVECTOR3 m_posOffset;
	static D3DXVECTOR3 m_pos;
	static float m_fSize;
};

#endif