//==============================
//
// 補充処理[restock.h]
// Author:kaiti
//
//==============================
#ifndef _BUFF_ICON_H_
#define _BUFF_ICON_H_

#include "main.h"
#include "object2D.h"
#include "buff.h"

#define BUFF_X (200)
#define BUFF_Y (50)

//オブジェクト2Dクラス
class CBuffIcon:public CObject2D
{
public:
	//状態
	typedef enum
	{
		STATE_STAY = 0,
		STATE_SLIDEIN,
		STATE_SLIDEOUT,
		STATE_MAX
	}STATE;


	//メンバ関数
	CBuffIcon(int nPriority = 7);
	~CBuffIcon();

	static CBuffIcon* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//取得処理
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	bool GetUse(void){return m_bUse;}
	//設定処理

	void SetUse(bool bUse) { m_bUse = bUse; }
private:
	void Move(void);

	//メンバ変数
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_posStay;	//位置
	D3DXVECTOR3 m_posOut;	//位置

	D3DXVECTOR3 m_rot;	//角度

	bool m_bUse;
	bool m_bClear;
	int m_nIdxTex;

	CBuff::TYPE m_type;
	const char* m_apFileName[CBuff::TYPE_MAX];

	int m_nTime;

	STATE m_state;
};

#endif