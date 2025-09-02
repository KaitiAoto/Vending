//==============================
//
// 補充処理[restock.cpp]
// Author:kaiti
//
//==============================
#include "buff_icon.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "debugproc.h"
#include "input.h"

//==================
// コンストラクタ
//==================
CBuffIcon::CBuffIcon(int nPriority):CObject2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = true;
	m_bClear = false;
	m_type = CBuff::TYPE_NONE;

	m_nIdxTex = 0;
}
//================
// デストラクタ
//================
CBuffIcon::~CBuffIcon()
{
}
//===========
// 生成処理
//===========
CBuffIcon* CBuffIcon::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CBuffIcon* pObject2D;
	pObject2D = new CBuffIcon;
	//初期化
	pObject2D->Init(pos, fWidth, fHeight);
	return pObject2D;
}
//===============
// 初期化処理
//===============
HRESULT CBuffIcon::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//値を代入
	m_posStay = pos;
	m_posOut = pos + D3DXVECTOR3(-fWidth, 0.0f, 0.0f);

	m_pos = m_posOut;

	m_state = STATE_SLIDEIN;

	m_bUse = true;
	m_bClear = false;

	const char* apFileName[CBuff::TYPE_MAX] =
	{
		"data\\TEXTURE\\speedUP00.png",
	};

	for (int nCnt = 0; nCnt < CBuff::TYPE_MAX; nCnt++)
	{
		m_apFileName[nCnt] = apFileName[nCnt];
	}

	CObject2D::Init(m_apFileName[m_type], pos, m_rot, fWidth, fHeight);

	//テクスチャ割り当て
	CTexture* pTex = CManager::GetTex();
	m_nIdxTex = pTex->Register(m_apFileName[m_type]);
	CObject2D::SetIdxTex(m_nIdxTex);

	//オブジェクトの種類設定
	SetObjType(TYPE_UI);

	return S_OK;
}
//============
// 終了処理
//============
void CBuffIcon::Uninit(void)
{
	CObject2D::Uninit();
}
//============
// 更新処理
//============
void CBuffIcon::Update(void)
{
	const float fSpeed = 8.0f;

	switch (m_state)
	{
	case STATE_STAY:
	{
		CBuff::TYPE type = CGame::GetBuff()->GetType();
		if (type == CBuff::TYPE_NONE)
		{
			m_bClear = true;
		}
		if (m_bClear == true)
		{
			m_state = STATE_SLIDEOUT;
		}
		break;
	}
	case STATE_SLIDEIN:
		if (m_bUse == true)
		{
			m_pos.x += fSpeed;
			if (m_pos.x >= m_posStay.x)
			{
				m_state = STATE_STAY;
				m_pos = m_posStay;
			}
		}
		break;
	case STATE_SLIDEOUT:
		m_pos.x -= fSpeed;
		if (m_pos.x <= m_posOut.x)
		{
			m_pos = m_posOut;
			m_bClear = false;
			m_bUse = false;
		}

		break;

	default:
		break;
	}

	CObject2D::SetPos(m_pos);

	if (m_bUse == false)
	{
		Uninit();
	}
}
//============
// 描画処理
//============
void CBuffIcon::Draw(void)
{
	if (m_bUse == true)
	{
		CObject2D::Draw();
	}
}

void CBuffIcon::Move(void)
{


}