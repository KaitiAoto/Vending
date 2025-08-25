//===========================================
//
// タイマーマネージャー[timer_manager.h]
// Author:kaiti
//
//===========================================
#ifndef TIMER_MANAGER_H_
#define TIMER_MANAGER_H_

#include "main.h"
#include "timer.h"

#define MAX_TIMER (3)
#define TIMERDATA (100)

//オブジェクト2Dクラス
class CTimerMana
{
public:

	//メンバ関数
	CTimerMana();
	~CTimerMana();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTimerMana* Create(D3DXVECTOR3 pos);
	static void AddTime(int nAdd);
private:
	//メンバ変数
	//static CTimerMana* m_pTimer[MAX_TIMER];	//オブジェクトへのポインタ

	static int m_nTimer;
	static int m_nCntTime;
	static CTimer* m_pTimer[MAX_TIMER];
};

#endif