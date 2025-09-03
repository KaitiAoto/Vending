////=======================
//
// タイマー[timer.cpp]
// Author : Kaiti Aoto
//
//=======================
#include "bullet_counter.h"
#include "renderer.h"
#include "manager.h"
#include "timer_manager.h"

//==================
// コンストラクタ
//==================
CBullerCounter::CBullerCounter(int nPriority) :CObject(nPriority)
{
	m_pNumber = nullptr;
}
//================
// デストラクタ
//================
CBullerCounter::~CBullerCounter()
{
}
//===========
// 生成処理
//===========
CBullerCounter* CBullerCounter::Create(D3DXVECTOR3 pos)
{
	CBullerCounter* pScore = new CBullerCounter;
	//初期化
	pScore->Init(pos, BULLET_COUNT_SIZE, BULLET_COUNT_SIZE);

	return pScore;
}
//===============
// 初期化処理
//===============
HRESULT CBullerCounter::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//初期化
	m_pNumber = CNumber::Create("data\\TEXTURE\\number002.png", pos, fWidth, fHeight);

	SetObjType(TYPE_BULLETCNT);

	return S_OK;
}
//============
// 終了処理
//============
void CBullerCounter::Uninit(void)
{
	if (m_pNumber != nullptr)
	{
		m_pNumber->Uninit();
		delete m_pNumber;
		m_pNumber = nullptr;
	}
	CObject::Release();
}
//============
// 更新処理
//============
void CBullerCounter::Update(void)
{
}
//============
// 描画処理
//============
void CBullerCounter::Draw(void)
{
	if (m_pNumber != nullptr)
	{
		m_pNumber->Draw();
	}
}