//================================================================
//
// 弾数カウンターマネージャー[bullet_counter_manager.cpp]
// Author : Kaiti Aoto
//
//================================================================

// インクルード
#include "bullet_counter_manager.h"
#include "renderer.h"
#include "manager.h"
#include "object.h"
#include "player.h"

// 静的メンバ変数
int CBulletCntMana::m_nCount = 0;
CBullerCounter* CBulletCntMana::m_pCounter[MAX_BULLETCNT] = {};
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
	// 生成
	CBulletCntMana* pBulletCntMana = new CBulletCntMana;
	// 初期化
	if (FAILED(pBulletCntMana->Init(pos)))
	{// NULLチェック
		delete pBulletCntMana;
		return nullptr;
	}
	return pBulletCntMana;	// ポインタを返す
}
//===============
// 初期化処理
//===============
HRESULT CBulletCntMana::Init(D3DXVECTOR3 pos)
{
	// 弾アイコン生成
	m_pIcon = CBulletIcon::Create(D3DXVECTOR3(pos.x - (BULLET_COUNT_SIZE * 4.5f), pos.y, 0.0f), BULLETICON_SIZE, BULLETICON_SIZE);

	// ×生成
	CObject2D::Create("data\\TEXTURE\\multiply00.png", D3DXVECTOR3(pos.x - (BULLET_COUNT_SIZE * 2.0f), pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLETICON_SIZE, BULLETICON_SIZE, 8);

	// 桁数分カウンター生成
	for (int nCnt = 0; nCnt < MAX_BULLETCNT; nCnt++)
	{
		m_pCounter[nCnt] = CBullerCounter::Create(D3DXVECTOR3(pos.x + (nCnt * BULLET_COUNT_SIZE * 2.5f), pos.y, 0.0f));
	}

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
	// プレイヤー情報取得
	CPlayer* pPlayer = CGame::GetPlayer();

	// 現在の所持数を取得
	m_nCount = pPlayer->GetContents();
	
	// カウンター更新
	UpdateCounter();
}
//============
// 描画処理
//============
void CBulletCntMana::Draw(void)
{
}
//===================
// カウンター更新
//===================
void CBulletCntMana::UpdateCounter(void)
{	
	int aPosTexU[MAX_BULLETCNT] = {};	// 各桁の値格納用変数
	// 各桁の値計算用基準値変数
	int nData = BULLETCNTDATA * 10;
	int nData2 = BULLETCNTDATA;

	// 中身が０なら
	if (m_nCount <= 0)
	{
		m_nCount = 0;	// ０に設定
	}

	// テクスチャ切り替え
	for (int nCnt = 0; nCnt < MAX_BULLETCNT; nCnt++)
	{
		if (m_pCounter[nCnt] != nullptr)
		{// NULLチェック
			// 数字のポインタ取得
			CNumber* pNumber = m_pCounter[nCnt]->GetNumber();

			// 桁１つ分の値を計算
			aPosTexU[nCnt] = m_nCount % nData / nData2;

			// 次の桁用に基準値を1/10する
			nData /= 10;
			nData2 /= 10;

			// テクスチャ切り替え
			pNumber->SetTex((aPosTexU[nCnt] * 0.1f), (aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f, 1.0f);
		}
	}
}