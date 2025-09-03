//==============================
//
// 敵拠点[enemy_base.h]
// Author : Kaiti Aoto
//
//==============================

// 二重インクルード防止
#ifndef _ENEMY_BASE_H_
#define _ENEMY_BASE_H_

// インクルード
#include "main.h"
#include "object.h"
#include "model.h"
#include "enemy_manager.h"
#include "meshcylinder.h"
#include "gauge_enemy.h"
#include "map_enemybase.h"

// マクロ定義
#define ENEMY_BASE_LIFE (120)
#define ENEMY_SPAN (300)
#define ENEMYBASE_RESPAWN (2400)

// 敵拠点クラス
class CEnemyBase:public CObject
{
public:
	// メンバ関数
	CEnemyBase(int nPriority = PRIORITY_ENEMYBASE);
	~CEnemyBase();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(const int nDamage);	

	// 設定
	void SetRespawn(bool bUse) { m_bRespawn = bUse; }
	// 取得
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	bool GetUse(void) { return m_bUse; }

	// 静的メンバ関数
	static CEnemyBase* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

private:
	void CreateEnemy(void);

	// メンバ変数
	D3DXVECTOR3 m_pos;			// 位置
	D3DXVECTOR3 m_rot;			// 向き
	D3DXVECTOR3 m_size;			// サイズ

	D3DXMATRIX m_mtxWorld;		// ワールドマトリックス
	CModel* m_pModel;			// 通常時のモデルへのポインタ
	CModel* m_pBreakModel;		// 破壊時のモデルへのポインタ
	int m_nLife;				// 寿命
	int m_nCntSpan;				// 敵生成時間カウント
	int m_nRespawn;				// 復活までの時間
	bool m_bUse;				// 使用しているか
	bool m_bRespawn;			// 復活できるか
	CEnemyGauge* m_pGauge;		// ゲージへのポインタ
	CMapEnemyBase* m_pMapIcon;	// マップアイコンへのポインタ
};

#endif