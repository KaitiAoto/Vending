//==============================
//
// 補充処理[restock.cpp]
// Author:kaiti
//
//==============================
#include "bullet_icon.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "player.h"
#include "debugproc.h"

//==================
// コンストラクタ
//==================
CBulletIcon::CBulletIcon(int nPriority):CObject2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = false;
}
//================
// デストラクタ
//================
CBulletIcon::~CBulletIcon()
{
}
//===========
// 生成処理
//===========
CBulletIcon* CBulletIcon::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CBulletIcon* pObject2D;
	pObject2D = new CBulletIcon;
	//初期化
	pObject2D->Init(pos, fWidth, fHeight);
	return pObject2D;
}
//===============
// 初期化処理
//===============
HRESULT CBulletIcon::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//値を代入
	m_pos = pos;
	m_bUse = false;

	CObject2D::Init("data\\TEXTURE\\bullet00.png", pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), fWidth, fHeight);

	ChangeIcon(CBullet::TYPE_CAN);

	//オブジェクトの種類設定
	SetObjType(TYPE_RESTOCK);

	return S_OK;
}
//============
// 終了処理
//============
void CBulletIcon::Uninit(void)
{
	CObject2D::Uninit();
}
//============
// 更新処理
//============
void CBulletIcon::Update(void)
{	
	//プレイヤー情報取得
	CPlayer* pPlayer = CGame::GetPlayer();
	int nCntContens = pPlayer->GetContents();

	if (nCntContens > 0)
	{
		m_bUse = true;

		m_type = pPlayer->GetMyBullet();

		ChangeIcon(m_type);
	}
	else if (nCntContens <= 0)
	{
		m_bUse = false;
	}
}
//============
// 描画処理
//============
void CBulletIcon::Draw(void)
{
	if (m_bUse == true)
	{
		CObject2D::Draw();
	}
}
//==================
// アイコン切り替え
//==================
void CBulletIcon::ChangeIcon(CBullet::TYPE type)
{
	const char* pTexName = {};
	//テクスチャ割り当て
	CTexture* pTex = CManager::GetTex();

	switch (type)
	{
	case CBullet::TYPE_CAN:
		pTexName = "data\\TEXTURE\\bullet00.png";
		break;
	case CBullet::TYPE_ICE:
		pTexName = "data\\TEXTURE\\bullet01.png";
		break;
	case CBullet::TYPE_CAPSULE:
		pTexName = "data\\TEXTURE\\bullet02.png";
		break;
	case CBullet::TYPE_PETBOTTLE:
		pTexName = "data\\TEXTURE\\bullet03.png";
		break;
	case CBullet::TYPE_DUST:
		pTexName = "data\\TEXTURE\\bullet04.png";
		break;
	case CBullet::TYPE_SNACK:
		pTexName = "data\\TEXTURE\\bullet05.png";
		break;
	case CBullet::TYPE_CIGARET:
		pTexName = "data\\TEXTURE\\bullet06.png";
		break;
	case CBullet::TYPE_CARD:
		pTexName = "data\\TEXTURE\\card00.jpg";
		break;
	case CBullet::TYPE_BOTTLE:
		pTexName = "data\\TEXTURE\\bullet08.png";
		break;
	default:
		break;
	}


	int nIdxTex = pTex->Register(pTexName);
	CObject2D::SetIdxTex(nIdxTex);
}
