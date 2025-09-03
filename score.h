//========================
//
// �X�R�A[score.h]
// Author : Kaiti Aoto
//
//========================

// ��d�C���N���[�h�h�~
#ifndef _SCORE_H_
#define _SCORE_H_

// �C���N���[�h
#include "main.h"
#include "number.h"

// �}�N����`
#define SCORE_SIZE (20)

//�I�u�W�F�N�g2D�N���X
class CScore:public CObject
{
public:

	//�����o�֐�
	CScore(int nPriority = 7);
	~CScore();
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	static int GetPriority(void) { return m_nPriority; }
	CNumber* GetNumber(void) { return m_pNumber; }
	void SetColor(D3DXCOLOR col);
private:
	//�����o�ϐ�
	static int m_nPriority;
	int m_nIdxTex;
	CNumber* m_pNumber;
};

#endif