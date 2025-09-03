//===========================================
//
// �^�C�}�[�}�l�[�W���[[timer_manager.h]
// Author:kaiti
//
//===========================================

// ��d�C���N���[�h�h�~
#ifndef _TIMER_MANAGER_H_
#define _TIMER_MANAGER_H_

// �C���N���[�h
#include "main.h"
#include "timer.h"

// �}�N����`
#define TIMERDATA (10)
#define TIME_DIGIT (2)

// �^�C�}�[�}�l�[�W���[�N���X
class CTimerMana
{
public:

	// �����o�֐�
	CTimerMana();
	~CTimerMana();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CTimerMana* Create(D3DXVECTOR3 pos);
	static void AddTime(int nAdd);
private:
	static void Second(void);
	static void Minute(void);

	// �ÓI�����o�ϐ�
	static CTimer* m_pSecond[TIME_DIGIT];	// �b���ւ̃|�C���^
	static CTimer* m_pMinute[TIME_DIGIT];	// �����ւ̃|�C���^
	static int m_nTimer;					// ���݂̎���
	static int m_nCntTime;					// 1�b�v���p
	static int m_nDrawSecond;				// �`�悷��b��
	static int m_nDrawMinute;				// �`�悷�镪��
};

#endif