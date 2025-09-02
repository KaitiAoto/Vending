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
#include "debugproc.h"
//静的メンバ変数
int CTimerMana::m_nTimer = 0;
CTimer* CTimerMana::m_pSecond[TIME_DIGIT] = {};
CTimer* CTimerMana::m_pMinute[TIME_DIGIT] = {};
int CTimerMana::m_nCntTime = 0;
int CTimerMana::m_nDrawSecond = 0;
int CTimerMana::m_nDrawMinute = 0;

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

	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		m_pMinute[nCnt] = CTimer::Create(D3DXVECTOR3(pos.x + (nCnt * TIMER_SIZE * 2.5f), pos.y, 0.0f));
	}

	CObject2D::Create("data\\TEXTURE\\colon00.png", D3DXVECTOR3(SCREEN_WIDTH / 2, pos.y, 0.0f), { 0.0f,0.0f,0.0f }, TIMER_SIZE * 1.5f, TIMER_SIZE * 1.5f, 7);

	pos.x += (2.5 * TIMER_SIZE * 2.5f);

	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		m_pSecond[nCnt] = CTimer::Create(D3DXVECTOR3(pos.x + (nCnt * TIMER_SIZE * 2.5f), pos.y, 0.0f));
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
		CGame::SetMode(CGame::MODE_FIN);
	}

	CDebugProc* pDegub = CManager::GetDebug();
	pDegub->Print("分：秒＝%d,%d", m_nDrawMinute, m_nDrawSecond);

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

	if (m_nTimer <= 0)
	{
		m_nTimer = 0;
	}

	m_nDrawMinute = m_nTimer / 60;
	m_nDrawSecond = m_nTimer % 60;

	Second();
	Minute();
}
//==============================
// 秒単位のテクスチャ切り替え
//==============================
void CTimerMana::Second(void)
{
	int aPosTexU[TIME_DIGIT]; //桁数分

	int nData = TIMERDATA * 10;
	int nData2 = TIMERDATA;
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		if (m_pSecond[nCnt] != nullptr)
		{
			CNumber* pNumber = m_pSecond[nCnt]->GetNumber();

			aPosTexU[nCnt] = m_nDrawSecond % nData / nData2;
			nData /= 10;
			nData2 /= 10;

			pNumber->SetTex((aPosTexU[nCnt] * 0.1f), (aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f, 1.0f);
		}
	}
}
//==============================
// 分単位のテクスチャ切り替え
//==============================
void CTimerMana::Minute(void)
{
	int aPosTexU[TIME_DIGIT]; //桁数分

	int nData = TIMERDATA * 10;
	int nData2 = TIMERDATA;
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		if (m_pMinute[nCnt] != nullptr)
		{
			CNumber* pNumber = m_pMinute[nCnt]->GetNumber();

			aPosTexU[nCnt] = m_nDrawMinute % nData / nData2;
			nData /= 10;
			nData2 /= 10;

			pNumber->SetTex((aPosTexU[nCnt] * 0.1f), (aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f, 1.0f);
		}
	}
}
