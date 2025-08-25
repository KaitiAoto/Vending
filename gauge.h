//==============================
//
//  ゲージ処理[Gauge.h]
//  Author:kaiti
//
//==============================
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include"main.h"
#include "object.h"

#define GAUGE_X (20)
#define GAUGE_Y (20)

//オブジェクト2Dクラス
class CGauge
{
public:

	//メンバ関数
	CGauge();
	~CGauge();
	HRESULT Init(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGauge* Create(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);

	void SetBase(float base) { m_Base = base; }
	void SetRate(float rate) { m_rate = rate; }
	void SetColor(D3DXCOLOR col) { m_col = col; }
	void Set();
private:
	//メンバ変数
	int m_nIdxTex;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	D3DXCOLOR m_col;
	float m_Base;
	float m_fHeight;
	float m_rate;

};
#endif
