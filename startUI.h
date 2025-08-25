//==============================
//
// 補充処理[restock.h]
// Author:kaiti
//
//==============================
#ifndef _STARTUI_H_
#define _STARTUI_H_

#include "main.h"
#include "object2D.h"

#define STARTUI_SIZE_X (600)
#define STARTUI_SIZE_Y (300)

//オブジェクト2Dクラス
class CStartUI:public CObject2D
{
public:

	//メンバ関数
	CStartUI(int nPriority = 7);
	~CStartUI();

	static CStartUI* Create(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//取得処理
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	//設定処理

private:
	void Move(void);

	//メンバ変数
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_posStay;	//位置
	D3DXVECTOR3 m_rot;	//角度

	bool m_bStop;
	bool m_bUse;
	int m_nTime;
};

#endif