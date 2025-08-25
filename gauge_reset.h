//==============================
//
//  HPゲージ処理[Gauge_hp.h]
//  Author:kaiti
//
//==============================
#ifndef _GAUGE_RESET_H_
#define _GAUGE_RESET_H_

#include "main.h"
#include "gauge.h"
#include "object2D.h"

//オブジェクト2Dクラス
class CResetGauge :CObject
{
public:

	//メンバ関数
	CResetGauge(int nPriority = 6);
	~CResetGauge();
	HRESULT Init(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResetGauge* Create(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);

private:
	//メンバ変数
	D3DXVECTOR3 m_pos;
	D3DXCOLOR m_col;
	float m_Base;
	float m_fHeight;

	CGauge* m_pGauge;
	bool m_bUse;
	int m_nCntReset;

	CObject2D* m_pObj2D;
};
#endif
