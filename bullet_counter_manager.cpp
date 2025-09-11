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
CBulletCntMana* CBulletCntMana::Create(D3DXVECTOR3 pos, bool bSub)
{
	// 生成
	CBulletCntMana* pBulletCntMana = new CBulletCntMana;
	// 初期化
	if (FAILED(pBulletCntMana->Init(pos,bSub)))
	{// NULLチェック
		delete pBulletCntMana;
		return nullptr;
	}
	return pBulletCntMana;	// ポインタを返す
}
//===============
// 初期化処理
//===============
HRESULT CBulletCntMana::Init(D3DXVECTOR3 pos, bool bSub)
{
	const float fDiv = 1.75f;
	float fIconSize = BULLETICON_SIZE;
	float fCntSize = BULLET_COUNT_SIZE;
	if (bSub == true)
	{
		fIconSize /= fDiv;
		fCntSize /= fDiv;
	}

	// 弾アイコン生成
	m_pIcon = CBulletIcon::Create(D3DXVECTOR3(pos.x - (fCntSize * 4.5f), pos.y, 0.0f), fIconSize, fIconSize);

	// ×生成
	CObject2D::Create("data\\TEXTURE\\multiply00.png", D3DXVECTOR3(pos.x - (fCntSize * 2.0f), pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), fIconSize, fIconSize, 8);

	// 桁数分カウンター生成
	for (int nCnt = 0; nCnt < MAX_BULLETCNT; nCnt++)
	{
		m_pCounter[nCnt] = CBullerCounter::Create(D3DXVECTOR3(pos.x + (nCnt * fCntSize * 2.5f), pos.y, 0.0f), fCntSize, fCntSize);
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
	// カウンター更新
	UpdateCounter();

	m_pIcon->SetType(m_Bullet);
	m_pIcon->SetContens(m_nCount);
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