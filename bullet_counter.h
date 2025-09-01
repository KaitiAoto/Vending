//=====================================
//
// 弾数カウンター[bullet_counter.h]
// Author:kaiti
//
//=====================================
#ifndef _BULLET_COUNTER_H_
#define _BULLET_COUNTER_H_

#include "main.h"
#include "number.h"
#include "object.h"

#define BULLET_COUNT_SIZE (30)

// 弾数カウンタークラス
class CBullerCounter :public CObject
{
public:

	// メンバ関数
	CBullerCounter(int nPriority = 7);
	~CBullerCounter();
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBullerCounter* Create(D3DXVECTOR3 pos);
	CNumber* GetNumber(void) { return m_pNumber; }
private:
	// メンバ変数
	CNumber* m_pNumber; // 数字へのポインタ
};

#endif