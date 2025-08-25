//===========================================
//
// タイマーマネージャー[timer_manager.cpp]
// Author:kaiti
//
//===========================================
#include "timer_manager.h"
#include "renderer.h"
#include "manager.h"
#include "object.h"
//静的メンバ変数
int CTimerMana::m_nTimer = 0;
CTimer* CTimerMana::m_pTimer[MAX_TIMER] = {};
int CTimerMana::m_nCntTime = 0;

//==================
// コンストラクタ
//==================
CTimerMana::CTimerMana()
{

}
//================
// デストラクタ
//================
CTimerMana::~CTimerMana()
{
}
//===========
// 生成処理
//===========
CTimerMana* CTimerMana::Create(D3DXVECTOR3 pos)
{
	CTimerMana* pTimerMane = new CTimerMana;

	for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		m_pTimer[nCnt] = CTimer::Create(D3DXVECTOR3(pos.x + (nCnt * TIMER_SIZE * 2.5f), pos.y, 0.0f));
	}

	pTimerMane->Init();

	return pTimerMane;
}
//===============
// 初期化処理
//===============
HRESULT CTimerMana::Init(void)
{
	//初期化
	m_nTimer = 0;
	CTimerMana::AddTime(GAME_TIME);
	return S_OK;
}
//============
// 終了処理
//============
void CTimerMana::Uninit(void)
{
	//for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	//{
	//	if (m_pTimer[nCnt] != nullptr)
	//	{
	//		m_pTimer[nCnt]->Uninit();
	//	}
	//}
}
//============
// 更新処理
//============
void CTimerMana::Update(void)
{
	m_nCntTime++;
	if (m_nCntTime >= 60)
	{
		m_nCntTime = 0;
		CTimerMana::AddTime(-1);
	}
	if (m_nTimer <= 0)
	{
		m_nTimer = 0;
		//CTimerMana::AddTime(60);

		CGame::SetMode(CGame::MODE_FIN);
	}
}
//============
// 描画処理
//============
void CTimerMana::Draw(void)
{
}
//==============
// スコア加算
//==============
void CTimerMana::AddTime(int nAdd)
{
	m_nTimer += nAdd;

	int aPosTexU[MAX_TIMER]; //桁数分
	if (m_nTimer <= 0)
	{
		m_nTimer = 0;
	}

	int nData = TIMERDATA * 10;
	int nData2 = TIMERDATA;
	for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		if (m_pTimer[nCnt] != nullptr)
		{
			CNumber* pNumber = m_pTimer[nCnt]->GetNumber();

			aPosTexU[nCnt] = m_nTimer % nData / nData2;
			nData /= 10;
			nData2 /= 10;

			pNumber->SetTex((aPosTexU[nCnt] * 0.1f), (aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f, 1.0f);
		}
	}
}
