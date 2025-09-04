//=====================================
//
// �e���J�E���^�[[bullet_counter.h]
// Author : Kaiti Aoto
//
//=====================================

// ��d�C���N���[�h�h�~
#ifndef _BULLET_COUNTER_H_
#define _BULLET_COUNTER_H_

#include "main.h"
#include "number.h"
#include "object.h"

// �}�N����`
#define BULLET_COUNT_SIZE (30)

// �e���J�E���^�[�N���X
class CBullerCounter :public CObject
{
public:

	// �����o�֐�
	CBullerCounter(int nPriority = 8);
	~CBullerCounter();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CNumber* GetNumber(void) { return m_pNumber; }

	// �ÓI�����o�֐�
	static CBullerCounter* Create(D3DXVECTOR3 pos);

private:
	// �����o�ϐ�
	CNumber* m_pNumber; // �����ւ̃|�C���^
};

#endif