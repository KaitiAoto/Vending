//================================
//
// フェード[fade.h]
// Author:kaiti
//
//================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "scene.h"
#include "object.h"
#include "object2D.h"

// 前方宣言
class CScene;

// フェードクラス
class CFade
{
public:
	// 状態
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX,
	}FADE;

	// メンバ関数
	CFade();
	~CFade();
	void Init(CScene::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFade* Create(CScene::MODE modeNext);

	// 取得
	FADE GetFade(void) { return m_fade; }

	// 設定
	void Set(CScene::MODE modeNext);
	void SetColor(D3DXCOLOR col);
private:
	// メンバ変数
	FADE m_fade;						// 状態
	D3DXCOLOR m_col;					// 色
	CScene::MODE m_modeNext;			// 次のシーン
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点情報
};

#endif