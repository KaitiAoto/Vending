//===========================================
//
// タイマーマネージャー[timer_manager.cpp]
// Author : Kaiti Aoto
//
//===========================================
#include "bullet_counter_manager.h"
#include "renderer.h"
#include "manager.h"
#include "object.h"
#include "player.h"
//静的メンバ変数
int CBulletCntMana::m_nCount = 0;
CBullerCounter* CBulletCntMana::m_pTimer[MAX_BULLETCNT] = {};
CBulletIcon* CBulletCntMana::m_pIcon = NULL;
//==================
// コンストラクタ
//==================
CBulletCntMana::CBulletCntMana()
{

}
//================
// デストラクタ
//================
CBulletCntMana::~CBulletCntMana()
{
}
//===========
// 生成処理
//===========
CBulletCntMana* CBulletCntMana::Create(D3DXVECTOR3 pos)
{
	CBulletCntMana* pTimerMane = new CBulletCntMana;

	m_pIcon = CBulletIcon::Create(D3DXVECTOR3(pos.x - (BULLET_COUNT_SIZE * 4.5f), pos.y, 0.0f), BULLETICON_SIZE, BULLETICON_SIZE);
	CObject2D::Create("data\\TEXTURE\\multiply00.png",D3DXVECTOR3(pos.x - (BULLET_COUNT_SIZE * 2.0f), pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLETICON_SIZE, BULLETICON_SIZE, 7);

	for (int nCnt = 0; nCnt < MAX_BULLETCNT; nCnt++)
	{
		m_pTimer[nCnt] = CBullerCounter::Create(D3DXVECTOR3(pos.x + (nCnt * BULLET_COUNT_SIZE * 2.5f), pos.y, 0.0f));
	}

	pTimerMane->Init();

	return pTimerMane;
}
//===============
// 初期化処理
//===============
HRESULT CBulletCntMana::Init(void)
{
	//初期化

	return S_OK;
}
//============
// 終了処理
//============
void CBulletCntMana::Uninit(void)
{

}
//============
// 更新処理
//============
void CBulletCntMana::Update(void)
{
	//プレイヤー情報取得
	CPlayer* pPlayer = CGame::GetPlayer();
	m_nCount = pPlayer->GetContents();
	SetBulletCount();
}
//============
// 描画処理
//============
void CBulletCntMana::Draw(void)
{
}
//==============
// スコア加算
//==============
void CBulletCntMana::SetBulletCount(void)
{
	int aPosTexU[MAX_BULLETCNT] = {}; //桁数分
	if (m_nCount <= 0)
	{
		m_nCount = 0;
	}

	int nData = BULLETCNTDATA * 10;
	int nData2 = BULLETCNTDATA;
	for (int nCnt = 0; nCnt < MAX_BULLETCNT; nCnt++)
	{
		if (m_pTimer[nCnt] != nullptr)
		{
			CNumber* pNumber = m_pTimer[nCnt]->GetNumber();

			aPosTexU[nCnt] = m_nCount % nData / nData2;
			nData /= 10;
			nData2 /= 10;

			pNumber->SetTex((aPosTexU[nCnt] * 0.1f), (aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f, 1.0f);
		}
	}
}