//================================
//
// リザルト処理[result.cpp]
// Author:kaiti
//
//================================
#include "ranking.h"
#include "manager.h"
#include "object2D.h"
#include "click.h"
//
CLoadStage* CRanking::m_pStage = NULL;
CRankMana* CRanking::m_pRankMana = NULL;
int CRanking::m_nPendingScore = 0;
//==================
// コンストラクタ
//==================
CRanking::CRanking():CScene(CScene::MODE_RANKING)
{
	m_nCntStay = 0;
}
//================
// デストラクタ
//================
CRanking::~CRanking()
{
}
//=======================
// 初期化
//=======================
void CRanking::Init(void)
{
	m_nCntStay = RESULT_STAY;

	m_pRankMana = CRankMana::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 4.0f, 0.0f));

	CClick::Create("data\\TEXTURE\\next00.png", D3DXVECTOR3(SCREEN_WIDTH - (CLICK_SIZE_X / 1.5f), SCREEN_HEIGHT - (CLICK_SIZE_Y / 1.5f), 0.0f), CLICK_SIZE_X, CLICK_SIZE_Y);

	if (m_pStage == NULL)
	{
		m_pStage = new CLoadStage;

		m_pStage->Load("data\\STAGE\\model01.txt");
	}
	CObject3D::Create("data\\TEXTURE\\field00.jpeg", D3DXVECTOR3(0.0f, -0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3000, 3000, CObject3D::TYPE_FIELD);
	CMeshCylinder::Create("data\\TEXTURE\\city01.png", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2900, 200, D3DXCOLOR(1.0, 1.0, 1.0, 1.0), CMeshCylinder::TYPE_IN);
	CMeshSphere::Create("data\\TEXTURE\\sky002.jpg", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3000, 3000, D3DXCOLOR(1.0, 1.0, 1.0, 1.0), CMeshSphere::TYPE_HALF_TOP);
}
//=============
// 終了処理
//=============
void CRanking::Uninit(void)
{
	if (m_pStage != NULL)
	{
		m_pStage->Unload();
		delete m_pStage;
		m_pStage = nullptr;
	}
	if (m_pRankMana != NULL)
	{
		m_pRankMana->Uninit();
		delete m_pRankMana;
		m_pRankMana = nullptr;
	}

	CObject::Release();
}
//=======================
// 更新
//=======================
void CRanking::Update(void)
{
	m_pRankMana->Update();

	m_nCntStay--;
	if (m_nCntStay <= 0)
	{
		m_nCntStay = 0;
		//マウス取得
		CInputMouse* pInputMouse = CManager::GetInputMouse();
		//パッド
		CInputPad* pPad = CManager::GetInputPad();

		if (pInputMouse->GetTrigger(0) == true || pPad->GetTrigger(CInputPad::JOYKEY_A) == true)
		{
			CFade* pFade = CManager::GetFade();

			pFade->Set(CScene::MODE_TITLE);
		}
	}
}
//=======================
// 描画
//=======================
void CRanking::Draw(void)
{

}