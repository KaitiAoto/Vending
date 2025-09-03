//==============================
//
// 補充処理[restock.cpp]
// Author : Kaiti Aoto
//
//==============================
#include "map_player.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "player.h"
#include "debugproc.h"

//==================
// コンストラクタ
//==================
CMapPlayer::CMapPlayer(int nPriority):CObject2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nIdxTex = 0;
	m_bUse = true;
}
//================
// デストラクタ
//================
CMapPlayer::~CMapPlayer()
{
}
//===========
// 生成処理
//===========
CMapPlayer* CMapPlayer::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CMapPlayer* pObject2D;
	pObject2D = new CMapPlayer;
	//初期化
	pObject2D->Init(pos, fWidth, fHeight);
	return pObject2D;
}
//===============
// 初期化処理
//===============
HRESULT CMapPlayer::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//値を代入
	m_pos = pos;
	m_bUse = true;

	CObject2D::Init("data\\TEXTURE\\build007.png", pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), fWidth, fHeight);


	//オブジェクトの種類設定
	SetObjType(TYPE_UI);

	return S_OK;
}
//============
// 終了処理
//============
void CMapPlayer::Uninit(void)
{
	CObject2D::Uninit();
}
//============
// 更新処理
//============
void CMapPlayer::Update(void)
{
	//プレイヤー情報取得
	CPlayer* pPlayer = CGame::GetPlayer();

	// ワールド座標を取得
	D3DXVECTOR3 playerPos = pPlayer->GetPos();

	// ミニマップの情報
	const float miniMapCenterX = CGame::GetMap()->GetPos().x;
	const float miniMapCenterY = CGame::GetMap()->GetPos().y;
	const float miniMapW = CGame::GetMap()->GetWidth();   // 200
	const float miniMapH = CGame::GetMap()->GetHeight();  // 200

	// ワールド座標を正規化 (-950～+950 → 0.0～1.0)
	const float worldSizeX = 1900.0f;
	const float worldSizeZ = 1900.0f;

	float normX = (playerPos.x + worldSizeX / 2.0f) / worldSizeX;  // 0.0～1.0
	float normZ = (playerPos.z + worldSizeZ / 2.0f) / worldSizeZ;  // 0.0～1.0

	// 中心を基準に描画
	float iconX = miniMapCenterX - miniMapW / 2.0f + normX * miniMapW;
	float iconY = miniMapCenterY - miniMapH / 2.0f + (1.0f - normZ) * miniMapH;

	m_pos = D3DXVECTOR3(iconX, iconY, 0.0f);

	CObject2D::SetPos(m_pos);
}
//============
// 描画処理
//============
void CMapPlayer::Draw(void)
{
	if (m_bUse == true)
	{
		CObject2D::Draw();
	}
}
