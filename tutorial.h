//==============================
//
// 補充処理[restock.h]
// Author:kaiti
//
//==============================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "object2D.h"

#define TUTORIAL_SIZE (200)

//オブジェクト2Dクラス
class CTutorial:public CObject2D
{
public:
	//種類
	typedef enum
	{
		TYPE_MOVE = 0,
		TYPE_CAMERA,
		//TYPE_JUMP,
		TYPE_BULLET,
		TYPE_RESTOCK,
		TYPE_MATCHUP,
		TYPE_MAX
	}TYPE;
	//状態
	typedef enum
	{
		STATE_STAY = 0,
		STATE_SLIDEIN,
		STATE_SLIDEOUT,
		STATE_MAX
	}STATE;


	//メンバ関数
	CTutorial(int nPriority = 7);
	~CTutorial();

	static CTutorial* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
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

	void CheckClear(void);

	//メンバ変数
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_posStay;	//位置
	D3DXVECTOR3 m_posOut;	//位置

	D3DXVECTOR3 m_rot;	//角度

	bool m_bUse;
	bool m_bClear;
	int m_nIdxTex;

	TYPE m_type;
	const char* m_apFileName[TYPE_MAX];

	int m_nTime;

	STATE m_state;
};

#endif