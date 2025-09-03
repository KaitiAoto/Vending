//==============================
//
// 敵拠点[enemy_base.cpp]
// Author : Kaiti Aoto
//
//==============================
#include "enemy_base.h"
#include "renderer.h"
#include "manager.h"
#include "score_manager.h"
#include "debugproc.h"
#include "particle.h"

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

	m_nCntSpan = 0;
	m_nRespawn = 0;

	m_bRespawn = false;
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
	m_nCntSpan = 0;
	m_nRespawn = 0;
	//モデル生成
	m_pModel = CModel::Create("data\\MODEL\\convenience_store00.x", m_pos, m_rot);
	m_size = m_pModel->SetSize();
	m_pBreakModel = CModel::Create("data\\MODEL\\convenience_store01.x", m_pos, m_rot);
	//オブジェクトの種類設定
	SetObjType(TYPE_ENEMY_BASE);
	
	float GeuseBase = m_nLife / 10.0f;
	m_pGauge = CEnemyGauge::Create(D3DXVECTOR3(m_pos.x, m_pos.y + (m_size.y / 1.5f), m_pos.z), GeuseBase, 10.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	if (CManager::GetScene()->GetMode() == CScene::MODE_GAME)
	{
		m_pMapIcon = CMapEnemyBase::Create(m_pos, 25.0f, 25.0f);
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

	CObject::Release();
}
//============
// 更新処理
//============
void CEnemyBase::Update(void)
{
	CScoreMana* pBreakScore = CGame::GetBreakCnt();
	CScoreMana* pTotalScore = CGame::GetTotalScore();
	CDebugProc* pDegub = CManager::GetDebug();

	if (m_bUse == true)
	{
		float rate = (float)m_nLife / (float)ENEMY_BASE_LIFE;
		rate = max(0.0f, min(rate, 1.0f));

		m_pGauge->SetDraw(m_bRespawn);
		m_pGauge->SetRate(rate);
		
		if (m_nLife <= 0)
		{
			CGame::GetBuff()->AddSpeed(3.0f, 5.0f);

			CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y + (m_size.y / 1.5f), m_pos.z), m_rot, D3DCOLOR_RGBA(255, 1, 1, 255), 30, 8.0f, CParticle::TYPE_NONE);

			m_bUse = false;

			pBreakScore->AddScore(1);
			pTotalScore->AddScore(10000);

			CSound* pSound = CManager::GetSound();
			pSound->PlaySound(CSound::SOUND_LABEL_BREAK);
		}
		if (m_bRespawn == true)
		{
			pDegub->Print("スポーン");

			//敵生成
			m_nCntSpan--;
			if (m_nCntSpan <= 0)
			{
				m_nCntSpan = ENEMY_SPAN;
				CreateEnemy();
			}
		}
	}
	else if (m_bUse == false)
	{//使っていないなら
		m_nRespawn++;

		if (m_nRespawn <= ENEMYBASE_RESPAWN / 10)
		{
			CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_rot, D3DCOLOR_RGBA(127, 127, 127, 255), 1, 15.0f, CParticle::TYPE_SMOKE);
		}

		if (m_nRespawn >= ENEMYBASE_RESPAWN)
		{
			m_nRespawn = 0;
			m_nLife = ENEMY_BASE_LIFE;
			m_bUse = true;
		}
		m_bRespawn = false;
	}

	if (m_pMapIcon != nullptr)
	{
		m_pMapIcon->SetUse(m_bUse);
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
void CEnemyBase::Hit(const int nDamage)
{
	m_nLife -= nDamage;

	//if (m_nLife > 0)
	//{
	//	State(STATE_HIT);
	//}
	//if (m_nLife == 0)
	//{
	//	State(STATE_DEAD);
	//}
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
	//CEnemy::Create(m_pos, m_rot, CEnemy::TYPE_MAGNET);

	//int nType = 0;
	//srand((unsigned int)time(NULL));
	//nType = rand() % CEnemy::TYPE_MAX;

	//CEnemy::Create(m_pos, m_rot, (CEnemy::TYPE)nType);
}