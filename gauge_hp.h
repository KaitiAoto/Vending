//==============================
//
//  HPゲージ処理[Gauge_hp.h]
//  Author:kaiti
//
//==============================
#ifndef _GAUGE_HP_H_
#define _GAUGE_HP_H_

#include"main.h"
#include "gauge.h"

//オブジェクト2Dクラス
class CHpGauge :CObject
{
public:

	//メンバ関数
	CHpGauge(int nPriority = 7);
	~CHpGauge();
	HRESULT Init(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CHpGauge* Create(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);

private:
	//メンバ変数
	D3DXVECTOR3 m_pos;
	D3DXCOLOR m_col;
	float m_Base;
	float m_fHeight;
	float m_rate;

	CGauge* m_pGauge;
};
#endif
