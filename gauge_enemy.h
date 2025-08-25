//==============================
//
//  HPゲージ処理[Gauge_hp.h]
//  Author:kaiti
//
//==============================
#ifndef _GAUGE_ENEMY_H_
#define _GAUGE_ENEMY_H_

#include "main.h"
#include "gauge_billboard.h"

//オブジェクト2Dクラス
class CEnemyGauge :CObject
{
public:

	//メンバ関数
	CEnemyGauge(int nPriority = 6);
	~CEnemyGauge();
	HRESULT Init(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemyGauge* Create(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);
	void SetBase(float nBase) { m_Base = nBase; }

	void SetDraw(bool bDraw) { m_bDraw = bDraw; }

	void SetRate(float rate) { m_rate = rate; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
private:
	//メンバ変数
	D3DXVECTOR3 m_pos;
	D3DXCOLOR m_col;
	float m_Base;
	float m_fHeight;

	CGaugeBillboard* m_pGauge;

	bool m_bDraw;
	float m_rate;

};
#endif
