//==============================
//
// 弾[bullet.cpp]
// Author:kaiti
//
//==============================
#include "bullet.h"
#include "renderer.h"
#include "manager.h"
#include "explosion.h"
#include "enemy.h"
#include "particle.h"
#include "player.h"
#include "debugproc.h"
#include "collision.h"
#include "easing.h"
//==================
// コンストラクタ
//==================
CBullet::CBullet(int nPriority):CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = {};

	m_pModel = NULL;

	m_nLife = 0;

	m_type = TYPE_CAN;
	m_user = USER_PLAYER;

	m_bUse = true;

	m_nPriority = nPriority;

	m_nAttack = 0;
}
//================
// デストラクタ
//================
CBullet::~CBullet()
{

}
//===========
// 生成処理
//===========
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, USER user)
{
	CBullet* pBullet = new CBullet;
	if (!pBullet)
		return nullptr;

	if (FAILED(pBullet->Init(pos, rot, user)))
	{
		delete pBullet;
		return nullptr;
	}

	return pBullet;
}
//===============
// 初期化処理
//===============
HRESULT CBullet::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, USER user)
{
	m_pos = pos;
	m_rot = rot;
	m_bUse = true;
	m_user = user;
	m_nAttack = 1;

	//モデル生成
	const char* pFilename = "data\\MODEL\\can00.x";
	if (m_user == USER_PLAYER)
	{
		pFilename = SetPlayerBullet();
		m_move = D3DXVECTOR3(sinf(m_rot.y - D3DX_PI) * BULLET_SPEED, 5.0f, cosf(m_rot.y - D3DX_PI) * BULLET_SPEED);
		m_nLife = BULLET_LIFE;
	}
	else if (m_user == USER_ENEMY)
	{
		pFilename = SetPlayerBullet();
		m_move = D3DXVECTOR3(sinf(m_rot.y - D3DX_PI) * BULLET_SPEED, 0.0f, cosf(m_rot.y - D3DX_PI) * BULLET_SPEED);
		m_nLife = BULLET_LIFE / 7;
	}

	m_pModel = CModel::Create(pFilename, m_pos, m_rot);
	m_size = m_pModel->SetSize() * 2;

	//オブジェクトの種類設定
	SetObjType(TYPE_BULLET);
	
	return S_OK;
}
//============
// 終了処理
//============
void CBullet::Uninit(void)
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
void CBullet::Update(void)
{
	if (m_bUse == true)
	{
		if (m_user == USER_PLAYER)
		{
			//移動
			MoveBounce();
			CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 1.0f, m_pos.z), m_rot, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(1, 127, 255, 255), 60, EFFECT_SIZE);
		}
		else if(m_user == USER_ENEMY)
		{
			Move();
		}

		Collision();
		//寿命
		m_nLife--;
		if (m_nLife <= 0)
		{
			m_bUse = false;
		}
	}
	else if (m_bUse == false)
	{//使っていないなら
		Uninit();
		return;
	}
}
//============
// 描画処理
//============
void CBullet::Draw(void)
{
	if (m_bUse == true)
	{
		//デバイスの取得
		CRenderer* pRenderer = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		//計算用マトリックス
		D3DXMATRIX mtxTrans;
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		if (m_user == USER_PLAYER)
		{
			//モデル描画
			m_pModel->Draw();
		}
	}
}
//===========
// 移動処理
//===========
void CBullet::Move(void)
{
	m_pos += m_move;

	m_pModel->Set(m_pos, m_rot);
}
//
//
//
void CBullet::MoveBounce(void)
{
	const float restitution = 0.8f; // 反発係数（0.0～1.0）
	const float groundY = 0.0f;

	m_move.y -= GRAVITY; //重力加算

	m_pos += m_move;

	// 地面との衝突（バウンド処理）
	if (m_pos.y < groundY)
	{
		m_pos.y = groundY;

		// Y速度の反転（バウンド）
		m_move.y *= -restitution;

		// 跳ね返りが小さくなったら止める
		if (fabs(m_move.y) < 0.2f)
		{
			m_move.y = 0.0f;
		}
	}

	m_pModel->Set(m_pos, m_rot);
}
//====================
// 敵との当たり判定
//====================
bool CBullet::Collision(void)
{
	//当たり判定のポインタ取得
	CCollision* pColl = CGame::GetColl();

	D3DXVECTOR3 contactNormal;

	bool bCollEnemy = false;
	bool bCollVender = false;
	bool bCollStage = false;
	bool bCollPlayer = false;

	if (m_user == USER_PLAYER)
	{
		//敵サイドとの判定
		bCollEnemy = pColl->ToEnemy(m_pos, m_rot, m_size, TYPE_BULLET, contactNormal);
		//自販機との判定
		bCollVender = pColl->ToVender(m_pos, m_rot, m_size, TYPE_BULLET, contactNormal);
		//
		bCollStage = pColl->ToStage(m_pos, m_rot, m_size, contactNormal);
	}
	else if (m_user == USER_ENEMY)
	{
		bCollPlayer = pColl->EnemyBullet(m_pos, m_size);
	}

	if (bCollEnemy == true || bCollVender == true || bCollStage == true || bCollPlayer == true)
	{
		Uninit();
	}

	return bCollEnemy;
}
//======================================
// プレイヤーの弾の種類ごとのモデル名
//======================================
const char* CBullet::SetPlayerBullet(void)
{
	//プレイヤー情報取得
	CPlayer* pPlayer = CGame::GetPlayer();

	const char* pFilename = "data\\MODEL\\can00.x";

	m_type = pPlayer->GetMyBullet();

	switch (m_type)
	{
	case TYPE_CAN:
		pFilename = "data\\MODEL\\can00.x";
		break;
	case TYPE_ICE:
		pFilename = "data\\MODEL\\ice00.x";
		break;
	case TYPE_CAPSULE:
		pFilename = "data\\MODEL\\capsule00.x";
		break;
	case TYPE_PETBOTTLE:
		pFilename = "data\\MODEL\\pet_bottle00.x";
		break;
	case TYPE_DUST:
		pFilename = "data\\MODEL\\can01.x";
		break;
	case TYPE_SNACK:
		pFilename = "data\\MODEL\\snack00.x";
		break;
	case TYPE_CIGARET:
		pFilename = "data\\MODEL\\cigarette00.x";
		break;
	case TYPE_CARD:
		pFilename = "data\\MODEL\\card00.x";
		break;
	case TYPE_BOTTLE:
		pFilename = "data\\MODEL\\bottle00.x";
		break;

	default:
		break;
	}
	
	return pFilename;
}