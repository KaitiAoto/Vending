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

#define MAX_TIMER (3)
#define TIMERDATA (100)

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
	//�����o�ϐ�
	//static CTimerMana* m_pTimer[MAX_TIMER];	//�I�u�W�F�N�g�ւ̃|�C���^

	static int m_nTimer;
	static int m_nCntTime;
	static CTimer* m_pTimer[MAX_TIMER];
};

#endif