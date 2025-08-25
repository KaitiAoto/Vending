//==============================
//
// 自販機[vender.cpp]
// Author:kaiti
//
//==============================
#include "vender.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "restock.h"
//==================
// コンストラクタ
//==================
CVender::CVender(int nPriority):CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_mtxWorld = {};

	m_pModel = NULL;

	m_bUse = true;
	m_bUseRestock = true;

	m_nPriority = nPriority;

	m_nRestock = 0;
	m_nCntReuse = 0;

	m_type = CBullet::TYPE_CAN;
	m_pCylinder = nullptr;
	m_pRestock = nullptr;
}
//================
// デストラクタ
//================
CVender::~CVender()
{

}
//===========
// 生成処理
//===========
CVender* CVender::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CBullet::TYPE type)
{
	CVender* pVender = new CVender;
	if (!pVender)
		return nullptr;

	if (FAILED(pVender->Init(pos, rot, type)))
	{
		delete pVender;
		return nullptr;
	}

	return pVender;
}
//===============
// 初期化処理
//===============
HRESULT CVender::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, CBullet::TYPE type)
{
	m_pos = pos;
	m_rot = rot;
	m_bUse = true;

	m_nRestock = MAX_RESTOCK;
	m_nCntReuse = NUM_REUSETIME;
	m_bUseRestock = true;
	m_type = type;

	//モデル生成
	const char* pFilename = SetModelName();

	m_pModel = CModel::Create(pFilename, m_pos, m_rot);
	m_size = m_pModel->SetSize();

	//オブジェクトの種類設定
	SetObjType(TYPE_VENDER);

	if (CManager::GetScene()->GetMode() == CScene::MODE_GAME)
	{
		float radius = max(m_size.x, max(m_size.y, m_size.z)) * 0.5f;
		m_pCylinder = CMeshCylinder::Create("data\\TEXTURE\\gauge00.jpeg", D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_rot, radius / 4, 100, D3DXCOLOR(1.0, 1.0, 0.0, 0.75), CMeshCylinder::TYPE_BOTHSIDES);
		m_pRestock = CRestock::Create("data\\TEXTURE\\restock01.png", D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f), RESTOCK_SIZE, RESTOCK_SIZE / 2);
	}
	return S_OK;
}
//============
// 終了処理
//============
void CVender::Uninit(void)
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
void CVender::Update(void)
{
	if (m_bUse == true)
	{
		if (m_bUseRestock == true)
		{

		}
		else if (m_bUseRestock == false)
		{
			m_nCntReuse--;
			if (m_nCntReuse <= 0)
			{
				m_nCntReuse = NUM_REUSETIME;
				m_bUseRestock = true;
			}
			m_pCylinder->SetUse(m_bUseRestock);
		}
	}
	else if (m_bUse == false)
	{//使っていないなら
		Uninit();
	}
}
//============
// 描画処理
//============
void CVender::Draw(void)
{
	if (m_bUse == true)
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

		//モデル描画
		m_pModel->Draw();
	}
}
//======================================
// 種類ごとのモデル名
//======================================
const char* CVender::SetModelName(void)
{
	const char* pFilename = "data\\MODEL\\vending_machine00.x";

	switch (m_type)
	{
	case CBullet::TYPE_CAN:
		pFilename = "data\\MODEL\\vending_machine00.x";
		break;
	case CBullet::TYPE_ICE:
		pFilename = "data\\MODEL\\vending_machine03.x";
		break;
	case CBullet::TYPE_CAPSULE:
		pFilename = "data\\MODEL\\vending_machine02.x";
		break;
	case CBullet::TYPE_PETBOTTLE:
		pFilename = "data\\MODEL\\vending_machine04.x";
		break;
	case CBullet::TYPE_DUST:
		pFilename = "data\\MODEL\\dustbox00.x";
		break;
	case CBullet::TYPE_SNACK:
		pFilename = "data\\MODEL\\vending_machine05.x";
		break;
	case CBullet::TYPE_CIGARET:
		pFilename = "data\\MODEL\\vending_machine01.x";
		break;
	case CBullet::TYPE_CARD:
		pFilename = "data\\MODEL\\vending_machine06.x";
		break;
	case CBullet::TYPE_BOTTLE:
		pFilename = "data\\MODEL\\vending_machine07.x";
		break;

	default:
		break;
	}

	return pFilename;
}
//=====================
// モデル名ごとの種類
//=====================
CBullet::TYPE CVender::SetType(const char* pFileName)
{
	CBullet::TYPE type = CBullet::TYPE_CAN;

	if (strcmp(pFileName, "data\\MODEL\\vending_machine00.x") == 0)
	{
		type = CBullet::TYPE_CAN;
	}
	else if (strcmp(pFileName, "data\\MODEL\\vending_machine03.x") == 0)
	{
		type = CBullet::TYPE_ICE;
	}
	else if (strcmp(pFileName, "data\\MODEL\\vending_machine02.x") == 0)
	{
		type = CBullet::TYPE_CAPSULE;
	}
	else if (strcmp(pFileName, "data\\MODEL\\vending_machine04.x") == 0)
	{
		type = CBullet::TYPE_PETBOTTLE;
	}
	else if (strcmp(pFileName, "data\\MODEL\\dustbox00.x") == 0)
	{
		type = CBullet::TYPE_DUST;
	}
	else if (strcmp(pFileName, "data\\MODEL\\vending_machine05.x") == 0)
	{
		type = CBullet::TYPE_SNACK;
	}
	else if (strcmp(pFileName, "data\\MODEL\\vending_machine01.x") == 0)
	{
		type = CBullet::TYPE_CIGARET;
	}
	else if (strcmp(pFileName, "data\\MODEL\\vending_machine06.x") == 0)
	{
		type = CBullet::TYPE_CARD;
	}
	else if (strcmp(pFileName, "data\\MODEL\\vending_machine07.x") == 0)
	{
		type = CBullet::TYPE_BOTTLE;
	}

	return type;
}
