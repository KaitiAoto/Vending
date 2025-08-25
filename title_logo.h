//==============================
//
// 補充処理[restock.h]
// Author:kaiti
//
//==============================
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_

#include "main.h"
#include "object2D.h"

#define LOGO_SIZE_X (450)
#define LOGO_SIZE_Y (300)

//オブジェクト2Dクラス
class CTitleLogo:public CObject2D
{
public:

	//メンバ関数
	CTitleLogo(int nPriority = 8);
	~CTitleLogo();

	static CTitleLogo* Create(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//取得処理
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	bool GetStop(void) { return m_bStop; }
	//設定処理

private:

	//メンバ変数
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_posStay;	//位置
	D3DXVECTOR3 m_rot;	//角度
	D3DXVECTOR3 m_move;					//移動量

	bool m_bUse;
	int m_nTime;

	int m_AnimCnt;

	bool m_bStop;
};

#endif