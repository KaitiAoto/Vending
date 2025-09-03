//==============================
//
// 補充処理[restock.cpp]
// Author : Kaiti Aoto
//
//==============================
#include "restock.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "player.h"
#include "debugproc.h"
#include "input.h"

//==================
// コンストラクタ
//==================
CRestock::CRestock(int nPriority):CObject2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nIdxTex = 0;
	m_bUse = false;
}
//================
// デストラクタ
//================
CRestock::~CRestock()
{
}
//===========
// 生成処理
//===========
CRestock* CRestock::Create(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CRestock* pObject2D;
	pObject2D = new CRestock;
	//初期化
	pObject2D->Init(pTexName, pos, fWidth, fHeight);
	return pObject2D;
}
//===============
// 初期化処理
//===============
HRESULT CRestock::Init(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//値を代入
	m_pos = pos;
	m_bUse = false;

	CObject2D::Init(pTexName, pos, m_rot, fWidth, fHeight);

	//テクスチャ割り当て
	CTexture* pTex = CManager::GetTex();
	m_nIdxTex = pTex->Register(pTexName);

	//オブジェクトの種類設定
	SetObjType(TYPE_RESTOCK);

	return S_OK;
}
//============
// 終了処理
//============
void CRestock::Uninit(void)
{
	CObject2D::Uninit();
}
//============
// 更新処理
//============
void CRestock::Update(void)
{

}
//============
// 描画処理
//============
void CRestock::Draw(void)
{
	if (m_bUse == true)
	{
		CObject2D::Draw();
	}
}
//=============
// 設定処理
//=============
void CRestock::Set(int nRestock, CBullet::TYPE type, CVender* pVender)
{
	CDebugProc* pDegub = CManager::GetDebug();

	//キー取得
	CInputKey* pInputKey = CManager::GetInputKey();
	//パッド
	CInputPad* pInputPad = CManager::GetInputPad();

	//プレイヤー情報取得
	CPlayer* pPlayer = CGame::GetPlayer();

	CScoreMana* pTotalScore = CGame::GetTotalScore();

	pDegub->Print("補充可能");
	m_bUse = true;
	if (pInputKey->GetTrigger(DIK_F) == true || pInputPad->GetTrigger(CInputPad::JOYKEY_Y) == true)
	{
		//中身補充
		pPlayer->AddContents(nRestock);
		//種類設定
		pPlayer->SetBulletType(type);

		pVender->SetUseRestock(false);
		m_bUse = false;

		CGame::GetFlash()->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f));

		CSound* pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_RESTOCK);

		pTotalScore->AddScore(50);

		//チュートリアルクリア判定
		if (CGame::GetMode() == CGame::MODE_TUTORIAL)
		{
			CTutorial* pTutorial = CGame::GetTutorial();
			if (pTutorial != nullptr)
			{
				if (pTutorial->GetType() == CTutorial::TYPE_RESTOCK)
				{
					CGame::GetTutorial()->SetClear(true);
				}
			}
		}
	}
}