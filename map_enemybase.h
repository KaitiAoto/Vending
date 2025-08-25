//==============================
//
// 補充処理[restock.h]
// Author:kaiti
//
//==============================
#ifndef _MAP_ENEMYBASE_H_
#define _MAP_ENEMYBASE_H_

#include "main.h"
#include "object2D.h"
#include "bullet.h"



//オブジェクト2Dクラス
class CMapEnemyBase:public CObject2D
{
public:

	//メンバ関数
	CMapEnemyBase(int nPriority = 8);
	~CMapEnemyBase();

	static CMapEnemyBase* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//取得処理
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	bool GetUse(void){return m_bUse;}
	//設定処理

	void SetIdxTex(const int nIdxTex) { m_nIdxTex = nIdxTex; }
	void SetUse(bool bUse) { m_bUse = bUse; }
private:
	
	//メンバ変数
	D3DXVECTOR3 m_pos;	//位置

	int m_nIdxTex;
	bool m_bUse;
};

#endif