//==============================
//
//  ゲージ処理[Gauge.h]
//  Author:kaiti
//
//==============================
#ifndef _GAUGE_BILLBOARD_H_
#define _GAUGE_BILLBOARD_H_

#include"main.h"
#include "object.h"

//クラス
class CGaugeBillboard
{
public:

	//メンバ関数
	CGaugeBillboard();
	~CGaugeBillboard();
	HRESULT Init(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGaugeBillboard* Create(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);

	void Set();

	void SetBase(float base) { m_Base = base; }
	void SetRate(float rate) { m_rate = rate; }
	void SetColor(D3DXCOLOR col) { m_col = col; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
private:
	//メンバ変数
	int m_nIdxTex;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	D3DXMATRIX m_mtxWorld;//ワールドマトリックス
	D3DXCOLOR m_col;
	float m_Base;
	float m_fHeight;
	float m_fWidth;
	float m_rate;
};
#endif
