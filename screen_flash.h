//==============================
//
// 補充処理[restock.h]
// Author:kaiti
//
//==============================
#ifndef _SCREEN_FLASH_H_
#define _SCREEN_FLASH_H_

#include "main.h"
#include "object2D.h"

//オブジェクト2Dクラス
class CScreenFlash:public CObject2D
{
public:

	//メンバ関数
	CScreenFlash(int nPriority = 9);
	~CScreenFlash();

	static CScreenFlash* Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//取得処理
	
	//設定処理
	void SetColor(D3DXCOLOR col) { m_col = col; m_bUse = true; }
private:

	//メンバ変数
	bool m_bUse;
	D3DXCOLOR m_col;
};

#endif