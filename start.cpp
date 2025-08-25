//==============================
//
// 自販機[vender.cpp]
// Author:kaiti
//
//==============================
#include "start.h"
#include "renderer.h"
#include "manager.h"
#include "collision.h"
#include "startUI.h"
//==================
// コンストラクタ
//==================
CStart::CStart(int nPriority):CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_mtxWorld = {};

	m_pModel = NULL;

	m_bDraw = true;
}
//================
// デストラクタ
//================
CStart::~CStart()
{

}
//===========
// 生成処理
//===========
CStart* CStart::Create(const char* pFilename, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CStart* pBullet = new CStart;
	if (!pBullet)
		return nullptr;

	if (FAILED(pBullet->Init(pFilename, pos, rot)))
	{
		delete pBullet;
		return nullptr;
	}

	return pBullet;
}
//===============
// 初期化処理
//===============
HRESULT CStart::Init(const char* pFilename, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_rot = rot;

	m_pos.x -= 40.0f;

	//モデル生成
	m_pModel = CModel::Create(pFilename, m_pos, m_rot);
	m_size = m_pModel->SetSize();

	m_bDraw = true;

	//オブジェクトの種類設定
	SetObjType(TYPE_START);

	return S_OK;
}
//============
// 終了処理
//============
void CStart::Uninit(void)
{
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
		delete m_pModel;
		m_pModel = NULL;
	}
	CObject::Release();
}
//============
// 更新処理
//============
void CStart::Update(void)
{
	if (m_bDraw == true)
	{
		SetObjType(TYPE_STAGE);
	}
	else if (m_bDraw == false)
	{
		SetObjType(TYPE_START);

		//当たり判定のポインタ取得
		CCollision* pColl = CGame::GetColl();

		bool bColl = pColl->ToStart(m_pos, TYPE_START);

		if (bColl == true)
		{
			m_bDraw = true;
			m_pos.x -= 40.0f;
			SetObjType(TYPE_STAGE);

			CStartUI::Create("data\\TEXTURE\\game_start00.png", D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), STARTUI_SIZE_X, STARTUI_SIZE_Y);

			CSound* pSound = CManager::GetSound();
			pSound->PlaySound(CSound::SOUND_LABEL_START);

			CGame::SetMode(CGame::MODE_PLAY);
		}
	}
}
//============
// 描画処理
//============
void CStart::Draw(void)
{
	//デバイスの取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	if (m_bDraw == true)
	{
		m_pModel->SetPos(m_pos);
		//モデル描画
		m_pModel->Draw();
	}
}