//================================
//
// マネージャー処理[manager.h]
// Author:kaiti
//
//================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "scene.h"
#include "game.h"
#include "fade.h"
#include "result.h"
#include "ranking.h"

//マクロ定義
#define GRAVITY (0.7f)

//前方宣言
class CRenderer;
class CInputKey;
class CInputMouse;
class CInputPad;
class CCamera;
class CTexture;
class CSound;
class CLight;
class CDebugProc;
class CScene;

//マネージャークラス
class CManager
{
public:

	//メンバ関数
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//静的メンバ関数
	static CRenderer* GetRenderer(void) { return m_pRenderer; }
	static CInputKey* GetInputKey(void) { return m_pInputKey; }
	static CInputMouse* GetInputMouse(void) { return m_pInputMouse; }
	static CInputPad* GetInputPad(void) { return m_pInputPad; }

	static CCamera* GetCamera(void) { return m_pCamera; }
	static CLight* GetLight(void) { return m_pLight; }
	static CTexture* GetTex(void) { return m_pTex; }
	static CSound* GetSound(void) { return m_pSound; }
	static CDebugProc* GetDebug(void) { return m_pDebug; }
	static CFade* GetFade(void) { return m_pFade; }
	static CScene* GetScene(void) { return m_pScene; }



	static void SetMode(CScene::MODE mode);
	static CScene::MODE GetMode(void) { return m_pScene->GetMode(); };

	static void SetPause(bool bPause) { m_bPause = bPause; }
	static bool GetPause(void) { return m_bPause; }

	//void SetFPS(int nFPS) { m_nFPS = nFPS; }
private:
	//メンバ関数
	HRESULT CreatePointa(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void ReleasePointa(void);

	//void CalculateFPS(); // FPS計算関数
	//void DrawFPS();      // FPS表示用関数

	//静的メンバ変数
	static CRenderer* m_pRenderer;				//レンダラーへのポインタ
	static CInputKey* m_pInputKey;				//キー入力へのポインタ
	static CInputMouse* m_pInputMouse;				//キー入力へのポインタ
	static CInputPad* m_pInputPad;				//キー入力へのポインタ
	static CTexture* m_pTex;					//テクスチャへのポインタ
	static CCamera* m_pCamera;					//カメラへのポインタ
	static CLight* m_pLight;					//ライトへのポインタ
	static CSound* m_pSound;					//サウンドへのポインタ
	static CDebugProc* m_pDebug;				//デバッグへのポインタ
	static CFade* m_pFade;				//デバッグへのポインタ

	static CScene* m_pScene;
	static bool m_bPause;

};

#endif