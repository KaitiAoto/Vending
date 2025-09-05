//==============================
//
// 敵拠点[enemy_base.cpp]
// Author : Kaiti Aoto
//
//==============================

//
#include "enemy_base.h"
#include "renderer.h"
#include "manager.h"
#include "score_manager.h"
#include "debugproc.h"
#include "particle.h"

//静的メンバ変数
int CEnemyBase::m_nNum = 0;

//==================
// コンストラクタ
//==================
CEnemyBase::CEnemyBase(int nPriority):CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_mtxWorld = {};

	m_pModel = NULL;

	m_nLife = 0;

	m_bUse = true;

	//m_nCntSpan = 0;

	m_nNum++;

	m_bBlinkIcon = false;
}
//================
// デストラクタ
//================
CEnemyBase::~CEnemyBase()
{

}
//===========
// 生成処理
//===========
CEnemyBase* CEnemyBase::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemyBase* pEnemyBase = new CEnemyBase;
	if (!pEnemyBase)
		return nullptr;

	if (FAILED(pEnemyBase->Init(pos, rot)))
	{
		delete pEnemyBase;
		return nullptr;
	}

	return pEnemyBase;
}
//===============
// 初期化処理
//===============
HRESULT CEnemyBase::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_rot = rot;
	m_nLife = ENEMY_BASE_LIFE;
	m_bUse = true;
	//m_nCntSpan = 0;
	m_nDecreaseTime = 0;
	//モデル生成
	m_pModel = CModel::Create("data\\MODEL\\convenience_store00.x", m_pos, m_rot);
	m_size = m_pModel->SetSize();
	m_pBreakModel = CModel::Create("data\\MODEL\\convenience_store01.x", m_pos, m_rot);
	//オブジェクトの種類設定
	SetObjType(TYPE_ENEMY_BASE);
	

	if (CManager::GetScene()->GetMode() == CScene::MODE_GAME)
	{
		for (int nCnt = 0; nCnt < STOCK_TYPE; nCnt++)
		{
			float GauseY = m_pos.y + (m_size.y);
			D3DXVECTOR3 Pos = { m_pos.x, m_pos.y + GauseY - (nCnt * 20.0f), m_pos.z };

			m_nStock[nCnt] = MAX_STOCK;
			float GeuseBase = (float)m_nStock[nCnt] / 1.5f;
			m_pGauge[nCnt] = CEnemyBaseGauge::Create(Pos, GeuseBase, 10.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), (CEnemyBaseGauge::TYPE)nCnt, this);
		}

		m_pMapIcon = CMapEnemyBase::Create(m_pos, 25.0f, 25.0f);
	
		CScoreMana* pBreakScore = CGame::GetBreakCnt();
		pBreakScore->AddScore(1);
	}
	return S_OK;
}
//============
// 終了処理
//============
void CEnemyBase::Uninit(void)
{
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
		delete m_pModel;
		m_pModel = NULL;
	}
	if (m_pBreakModel != NULL)
	{
		m_pBreakModel->Uninit();
		delete m_pBreakModel;
		m_pBreakModel = NULL;
	}
	
	m_nNum = 0;

	CObject::Release();
}
//============
// 更新処理
//============
void CEnemyBase::Update(void)
{
	const int nDecreaseTime = 120;

	if (CManager::GetScene()->GetMode() == CScene::MODE_GAME)
	{
		if (CGame::GetMode() != CGame::MODE_TUTORIAL)
		{
			CScoreMana* pBreakScore = CGame::GetBreakCnt();

			if (m_bUse == true)
			{
				for (int nCnt = 0; nCnt < STOCK_TYPE; nCnt++)
				{
					float rate = (float)m_nStock[nCnt] / (float)MAX_STOCK;
					rate = max(0.0f, min(rate, 1.0f));

					m_pGauge[nCnt]->SetRate(rate);
					m_pGauge[nCnt]->SetDraw(m_bRespawn);
				}

				if (m_nLife <= 0)
				{
					CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y + (m_size.y / 1.5f), m_pos.z), m_rot, D3DCOLOR_RGBA(255, 1, 1, 255), 30, 8.0f, CParticle::TYPE_NONE);

					m_bUse = false;

					pBreakScore->AddScore(-1);

					CSound* pSound = CManager::GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_BREAK);

					m_nNum--;
					if (m_nNum <= 0)
					{
						CGame::SetMode(CGame::MODE_FIN);
					}
				}
			}
			else if (m_bUse == false)
			{//使っていないなら
				CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_rot, D3DCOLOR_RGBA(127, 127, 127, 255), 1, 15.0f, CParticle::TYPE_SMOKE);
			}
		}
		if (m_pMapIcon != nullptr)
		{
			m_pMapIcon->SetUse(m_bUse);
		}
	}
}
//============
// 描画処理
//============
void CEnemyBase::Draw(void)
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
	
	if (m_bUse == true)
	{
		//モデル描画
		m_pModel->Draw();
	}
	else
	{
		m_pBreakModel->Draw();
	}
}
//================
// ダメージ処理
//================
void CEnemyBase::Hit(const CBullet::TYPE type)
{
	for (int nCnt = 0; nCnt < STOCK_TYPE; nCnt++)
	{
		CEnemyBaseGauge::TYPE HitType = SearchHitType(type);

		if (HitType == m_pGauge[nCnt]->GetType())
		{
			m_nStock[nCnt]++;
			if (m_nStock[nCnt] >= MAX_STOCK)
			{
				m_nStock[nCnt] = MAX_STOCK;
			}
			break;
		}
	}
}
//
//
//
void CEnemyBase::SoldOut(void)
{
	int nType;
	nType = rand() % STOCK_TYPE;

	m_nDecreaseTime = 0;
	m_nStock[nType]--;
	if (m_nStock[nType] <= 0)
	{
		m_nStock[nType] = 0;
		m_nLife = 0;
	}
}
//
//
//
void CEnemyBase::BlinkIcon(float fRate)
{
	if (fRate > 0.7f)
	{
		m_pMapIcon->SetBlink(false);
	}
	else if (fRate > 0.4f)
	{
		m_pMapIcon->SetBlink(false);
	}
	else if (fRate > 0.05f)
	{
		m_pMapIcon->SetBlink(true);
	}

}

//=============
// 敵生成処理
//=============
void CEnemyBase::CreateEnemy(void)
{
	auto now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	size_t seed = static_cast<size_t>(now) ^ reinterpret_cast<size_t>(this);

	std::mt19937 mt((unsigned int)seed);
	std::uniform_int_distribution<int> dist(0, CEnemy::TYPE_MAX - 1);

	int nType = dist(mt);
	CEnemy::Create(m_pos, m_rot, (CEnemy::TYPE)nType);
}

CEnemyBaseGauge::TYPE CEnemyBase::SearchHitType(CBullet::TYPE type)
{
	CEnemyBaseGauge::TYPE HitType = CEnemyBaseGauge::TYPE_DRINK;

	switch (type)
	{
		case CBullet::TYPE_CAN:
			HitType = CEnemyBaseGauge::TYPE_DRINK;
			break;
		case CBullet::TYPE_CAPSULE:
			HitType = CEnemyBaseGauge::TYPE_GENERAL;
			break;
		case CBullet::TYPE_ICE:
			HitType = CEnemyBaseGauge::TYPE_FOOD;
			break;
		case CBullet::TYPE_PETBOTTLE:
			HitType = CEnemyBaseGauge::TYPE_DRINK;
			break;
		case CBullet::TYPE_DUST:
			HitType = CEnemyBaseGauge::TYPE_MAX;
			break;
		case CBullet::TYPE_SNACK:
			HitType = CEnemyBaseGauge::TYPE_FOOD;
			break;
		case CBullet::TYPE_CIGARET:
			HitType = CEnemyBaseGauge::TYPE_GENERAL;
			break;
		case CBullet::TYPE_CARD:
			HitType = CEnemyBaseGauge::TYPE_GENERAL;
			break;
		case CBullet::TYPE_BOTTLE:
			HitType = CEnemyBaseGauge::TYPE_DRINK;
			break;
		default:
		break;
	}

	return HitType;
}