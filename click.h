//==============================
//
// 補充処理[restock.h]
// Author:kaiti
//
//==============================
#ifndef _CLICK_H_
#define _CLICK_H_

#include "main.h"
#include "object2D.h"

#define CLICK_SIZE_X (250)
#define CLICK_SIZE_Y (50)

//オブジェクト2Dクラス
class CClick:public CObject2D
{
public:

	//メンバ関数
	CClick(int nPriority = 9);
	~CClick();

	static CClick* Create(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//取得処理
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	//設定処理
	void SetUse(bool bUse) { m_bUse = bUse; }
private:

	//メンバ変数
	D3DXVECTOR3 m_pos;	//位置

	bool m_bUse;
};

#endif