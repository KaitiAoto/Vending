//====================================
//
// マップの敵拠点[map_enemybase.h]
// Author : Kaiti Aoto
//
//====================================

// 二重インクルード防止
#ifndef _MAP_ENEMYBASE_H_
#define _MAP_ENEMYBASE_H_

// インクルード
#include "main.h"
#include "object2D.h"
#include "bullet.h"

// マップの敵拠点クラス
class CMapEnemyBase:public CObject2D
{
public:

	// メンバ関数
	CMapEnemyBase(int nPriority = 8);
	~CMapEnemyBase();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 取得処理
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	bool GetUse(void){return m_bUse;}	
	// 設定処理
	void SetIdxTex(const int nIdxTex) { m_nIdxTex = nIdxTex; }
	void SetUse(bool bUse) { m_bUse = bUse; }
	void SetBlink(bool bBlink) { m_bBlink = bBlink; }
	// 静的メンバ変数
	static CMapEnemyBase* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	
	// メンバ変数
	D3DXVECTOR3 m_pos;	// 位置
	D3DXCOLOR m_col;	// 色
	int m_nIdxTex;		// テクスチャのインデックス番号
	int m_nCntTime;		// カウンター
	bool m_bUse;		// 使用しているか
	bool m_bBlink;		// 点滅するかどうか
};

#endif