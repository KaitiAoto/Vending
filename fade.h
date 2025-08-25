//================================
//
// タイトル処理[title.h]
// Author:kaiti
//
//================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "scene.h"
#include "object.h"
#include "object2D.h"

////マクロ定義
//#define GRAVITY (0.2f)

class CScene;

//マネージャークラス
class CFade
{
public:
	//フェードの状態
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX,
	}FADE;

	//メンバ関数
	CFade();
	~CFade();
	void Init(CScene::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFade* Create(CScene::MODE modeNext);

	FADE GetFade(void) { return m_fade; }

	void Set(CScene::MODE modeNext);
	void SetColor(D3DXCOLOR col);
private:
	FADE m_fade;
	D3DXCOLOR m_col;
	CScene::MODE m_modeNext;

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点情報

};

#endif