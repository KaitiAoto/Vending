//=============================
//
//　カメラ処理[camera.cpp]
//　Author:kaiti
//
//=============================
#include "camera.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "player.h"
//================
// コンストラクタ
//================
CCamera::CCamera(void)
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDistance = 0.0f;

	m_posVOffSet = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxProjection = {};
	m_mtxView = {};
}
//================
// デストラクタ
//================
CCamera::~CCamera()
{
}
//=================
// カメラの初期化
//=================
HRESULT CCamera::Init(void)
{
	//視点・注視点・上方向を設定する
	m_posV = D3DXVECTOR3(-1500.0f, 300.0f, -1200.0f);
	m_posVOffSet = m_posV;
	m_posR = D3DXVECTOR3(-1500.0f, 0.0f, -880.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//角度

	m_fDistance = sqrtf(((m_posV.x - m_posR.x) * (m_posV.x - m_posR.x))
					  + ((m_posV.y - m_posR.y) * (m_posV.y - m_posR.y))
					  + ((m_posV.z - m_posR.z) * (m_posV.z - m_posR.z)));	//視点と注視点の距離

	return S_OK;
}
//===================
// カメラの終了処理
//===================
void CCamera::Uninit(void)
{

}
//====================
// カメラの更新処理
//====================
void CCamera::Update(void)
{
	//キー取得
	CInputKey* pInputKey = CManager::GetInputKey();
	//マウス取得
	CInputMouse* pInputMouse = CManager::GetInputMouse();
	//パッド
	CInputPad* pInputPad = CManager::GetInputPad();

	CDebugProc* pDegub = CManager::GetDebug();

	//プレイヤー情報取得
	CPlayer* pPlayer = CGame::GetPlayer();
	if (pPlayer != nullptr)
	{
		D3DXVECTOR3 pos = pPlayer->GetPos();
		D3DXVECTOR3 rot = pPlayer->GetRot();

		//追従
		m_posRDest.x = pos.x + sinf(rot.x) * (pos.x - m_posR.x);
		//m_posRDest.y = pos.y;
		m_posRDest.z = pos.z + cosf(rot.z) * (pos.z - m_posR.z);

		m_posVDest.x = pos.x + sinf(m_rot.y - D3DX_PI) * m_fDistance;
		m_posVDest.z = pos.z + cosf(m_rot.y - D3DX_PI) * m_fDistance;

		m_posR.x += (m_posRDest.x - m_posR.x) * 0.08f;
		//m_posR.y += (m_posRDest.y - m_posR.y) * 1.0f;
		m_posR.z += (m_posRDest.z - m_posR.z) * 0.08f;

		m_posV.x += (m_posVDest.x - m_posV.x) * 0.08f;
		m_posV.z += (m_posVDest.z - m_posV.z) * 0.08f;
	}

	//カメラアップ
	if (pInputPad->GetTrigger(CInputPad::JOYKEY_R3) == true || pInputMouse->GetTrigger(2) == true)
	{
		m_fDistance -= 100.0f;
		m_posV.y -= 80.0f;
		if (m_posV.y <= 40.0f)
		{
			m_posV.y = 40.0f;
		}

		//一定距離で元に戻す
		if (m_fDistance <= 100.0f)
		{
			m_posV.y = m_posVOffSet.y;

			m_fDistance = sqrtf(((m_posV.x - m_posR.x) * (m_posV.x - m_posR.x))
							  + ((m_posV.y - m_posR.y) * (m_posV.y - m_posR.y))
							  + ((m_posV.z - m_posR.z) * (m_posV.z - m_posR.z)));	//視点と注視点の距離
		}
	}


	//マウスの左右移動で視点旋回（感度は適宜調整）
	if (pInputMouse != nullptr)
	{
		int mouseMoveX = pInputMouse->GetRelX();

		const float sensitivity = 0.0005f; // 感度調整用

		m_rot.y += mouseMoveX * sensitivity;

		int mouseMoveY = pInputMouse->GetRelY();

		const float sensitivityY = 0.05f; // 感度調整用

		m_posV.y += mouseMoveY * sensitivityY;

		if (m_posV.y <= 40.0f)
		{
			m_posV.y = 40.0f;
		}
		else if (m_posV.y >= 700.0f)
		{
			m_posV.y = 700.0f;
		}
	}

	if (pInputPad != nullptr)
	{
		const float sensitivity = 0.05f; // 感度調整用

		const float sensitivityY = 1.0f; // 感度調整用

		float rx = pInputPad->GetRightStickX(); // 横
		float ry = pInputPad->GetRightStickY(); // 縦

		// デッドゾーン処理（わずかな傾きによる誤動作防止）
		const float deadZone = 0.2f;
		if (fabsf(rx) > deadZone)
		{
			m_rot.y += rx * sensitivity;
		}
		if (fabsf(ry) > deadZone)
		{
			m_posV.y += ry * sensitivityY;
			
			if (m_posV.y <= 40.0f)
			{
				m_posV.y = 40.0f;
			}
			else if (m_posV.y >= 700.0f)
			{
				m_posV.y = 700.0f;
			}
		}
	}

#ifdef _DEBUG

	//視点の旋回
	if (pInputKey->GetPress(DIK_Q) == true)
	{
		m_rot.y += 0.05f;
	}
	else if (pInputKey->GetPress(DIK_E) == true)
	{
		m_rot.y -= 0.05f;
	}
	//視点の上下
	if (pInputKey->GetPress(DIK_Y) == true)
	{//上
		if (m_posV.y <= 500)
		{
			m_posV.y += 3;
		}
	}
	if (pInputKey->GetPress(DIK_N) == true)
	{//下
		if (m_posV.y >= -500)
		{
			m_posV.y -= 3;
		}
	}
#endif // DEBUG

	//角度の正規化
	if (m_rot.y >= D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}

	m_posV.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
	m_posV.z = m_posR.z - cosf(m_rot.y) * m_fDistance;


	pDegub->Print("カメラの角度：(%.1f, %.1f, %.1f)", m_rot.x, m_rot.y, m_rot.z);
	pDegub->Print("カメラの視点：(%.1f, %.1f, %.1f)", m_posV.x, m_posV.y, m_posV.z);
	pDegub->Print("視点と注視点の距離：%.1f", m_fDistance);
}
//
//
//
void CCamera::UpdateMenu(void)
{
	m_fDistance = 800.0f;//

	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posV.y = 200.0f;

	//回転
	m_rot.y += 0.003f;

	//角度の正規化
	if (m_rot.y >= D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}

	m_posV.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
	m_posV.z = m_posR.z - cosf(m_rot.y) * m_fDistance;


	CDebugProc* pDegub = CManager::GetDebug();

	pDegub->Print("カメラの角度：(%.1f, %.1f, %.1f)", m_rot.x, m_rot.y, m_rot.z);
	pDegub->Print("カメラの視点：(%.1f, %.1f, %.1f)", m_posV.x, m_posV.y, m_posV.z);
	pDegub->Print("視点と注視点の距離：%.1f", m_fDistance);
}
//================
// カメラの設定
//================
void CCamera::Set(void)
{
	//デバイスの取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
					   &m_posV,
					   &m_posR,
					   &m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f), //視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, //アスペクト比
		10.0f,
		5000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}
