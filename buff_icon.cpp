//==============================
//
// バフアイコン[buff_icon.h]
// Author : Kaiti Aoto
//
//==============================

// インクルード
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
	// 値をクリア
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
	// 生成
	CBuffIcon* pBuffIcon = new CBuffIcon;
	//初期化
	if (FAILED(pBuffIcon->Init(pos, fWidth, fHeight)))
	{// NULLチェック
		delete pBuffIcon;
		return nullptr;
	}
	return pBuffIcon;	// ポインタを返す
}
//===============
// 初期化処理
//===============
HRESULT CBuffIcon::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//値を代入
	m_posStay = pos;
	m_posOut = pos + D3DXVECTOR3(-fWidth, 0.0f, 0.0f);
	m_pos = m_posOut;

	m_state = STATE_SLIDEIN;	// 状態をスライドインに
	m_bUse = true;				// 使用する状態に
	m_bClear = false;			// クリアしていない状態に

	// テクスチャ名
	const char* apFileName[CBuff::TYPE_MAX] =
	{
		"data\\TEXTURE\\speedUP00.png",
	};

	for (int nCnt = 0; nCnt < CBuff::TYPE_MAX; nCnt++)
	{// テクスチャ名を登録
		m_apFileName[nCnt] = apFileName[nCnt];
	}

	// オブジェクト2Dの初期化
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
	// オブジェクト2Dの終了処理
	CObject2D::Uninit();
}
//============
// 更新処理
//============
void CBuffIcon::Update(void)
{
	const float fSpeed = 8.0f;	// スライドスピード

	// 状態
	switch (m_state)
	{
	// 待機
	case STATE_STAY:
	{
		CBuff::TYPE type = CGame::GetBuff()->GetType();	// 現在のバフの種類を取得

		if (type == CBuff::TYPE_NONE)
		{// 何もバフがかかっていなければ
			m_bClear = true;	// すり足ている状態にする
		}
		if (m_bClear == true)
		{// クリアしていれば
			m_state = STATE_SLIDEOUT;	// 状態をスライドアウトに
		}
		break;
	}
	// スライドイン
	case STATE_SLIDEIN:
		if (m_bUse == true)
		{// 使用していれば
			// 移動
			m_pos.x += fSpeed;
			
			if (m_pos.x >= m_posStay.x)
			{// 現在の位置が待機位置以上なら
				m_state = STATE_STAY;	// 状態を待機に
				m_pos = m_posStay;		// 現在の位置を待機位置に
			}
		}
		break;
	// スライドアウト
	case STATE_SLIDEOUT:
		if (m_bUse == true)
		{// 使用していれば
			// 移動
			m_pos.x -= fSpeed;
			
			if (m_pos.x <= m_posOut.x)
			{// 現在の位置が画面外位置以下なら
				m_pos = m_posOut;	// 現在の位置を画面外位置に
				m_bClear = false;	// クリアしていない状態に
				m_bUse = false;		// 使用していない状態に
			}
		}
		break;
	default:
		break;
	}

	// オブジェクト2Dの位置を設定
	CObject2D::SetPos(m_pos);

	if (m_bUse == false)
	{// 使用していなければ
		// 終了処理
		Uninit();
	}
}
//============
// 描画処理
//============
void CBuffIcon::Draw(void)
{
	if (m_bUse == true)
	{// 使用して入れば
		// オブジェクト2Dの描画
		CObject2D::Draw();
	}
}