//===========================================
//
// �^�C�}�[�}�l�[�W���[[timer_manager.h]
// Author:kaiti
//
//===========================================
#ifndef TIMER_MANAGER_H_
#define TIMER_MANAGER_H_

#include "main.h"
#include "timer.h"

#define TIMERDATA (10)
#define TIME_DIGIT (2)

//�I�u�W�F�N�g2D�N���X
class CTimerMana
{
public:

	//�����o�֐�
	CTimerMana();
	~CTimerMana();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTimerMana* Create(D3DXVECTOR3 pos);
	static void AddTime(int nAdd);
private:
	static void Second(void);
	static void Minute(void);

	//�����o�ϐ�
	//static CTimerMana* m_pTimer[MAX_TIMER];	//�I�u�W�F�N�g�ւ̃|�C���^

	static int m_nTimer;
	static int m_nCntTime;
	static CTimer* m_pSecond[TIME_DIGIT];
	static CTimer* m_pMinute[TIME_DIGIT];

	static int m_nDrawSecond;
	static int m_nDrawMinute;
};

#endif