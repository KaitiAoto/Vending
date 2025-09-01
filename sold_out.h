//==============================
//
// 補充処理[restock.h]
// Author:kaiti
//
//==============================
#ifndef _SOLD_OUT_H_
#define _SOLD_OUT_H_

#include "main.h"
#include "object2D.h"

//オブジェクト2Dクラス
class CSoldOut:public CObject2D
{
public:

	//メンバ関数
	CSoldOut(int nPriority = 9);
	~CSoldOut();

	static CSoldOut* Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//取得処理
	static bool GetUse(void) { return m_bUse; }

	//設定処理
	void SetColor(D3DXCOLOR col) { m_col = col; m_bUse = true; }
private:

	//メンバ変数
	static bool m_bUse;
	D3DXCOLOR m_col;
};

#endif