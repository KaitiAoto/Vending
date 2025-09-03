//=============================
//
// �^�C�}�[[timer.h]
// Author : Kaiti Aoto
//
//=============================

// ��d�C���N���[�h�h�~
#ifndef _TIMER_H_
#define _TIMER_H_

// �C���N���[�h
#include "main.h"
#include "number.h"
#include "object.h"

// �}�N����`
#define TIMER_SIZE (25)

// �^�C�}�[�N���X
class CTimer:public CObject
{
public:

	// �����o�֐�
	CTimer(int nPriority = 7);
	~CTimer();
	
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �擾
	CNumber* GetNumber(void){return m_pNumber;}

	// �ÓI�����o�֐�
	static CTimer* Create(D3DXVECTOR3 pos);
private:
	// �����o�ϐ�
	CNumber* m_pNumber;		// �����ւ̃|�C���^
};

#endif