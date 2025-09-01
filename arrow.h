//===================
//
// タイマー[timer.h]
// Author:kaiti
//
//===================
#ifndef _ARROW_H_
#define _ARROW_H_

#include "main.h"
#include "object3D.h"

class CArrow :public CObject3D
{
public:

	//メンバ関数
	CArrow(int nPriority = 9);
	~CArrow();

	static CArrow* Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//取得処理

	//設定処理
	void SetUse(bool bUse) { m_bUse = bUse; }
private:
	//メンバ変数
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_TargetPos;
	bool m_bUse;
};

#endif