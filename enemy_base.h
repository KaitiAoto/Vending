//==============================
//
// 敵拠点[enemy_base.h]
// Author:kaiti
//
//==============================
#ifndef _ENEMY_BASE_H_
#define _ENEMY_BASE_H_

#include "main.h"
#include "object.h"
#include "model.h"
#include "enemy_manager.h"
#include "meshcylinder.h"
#include "gauge_enemy.h"
#include "map_enemybase.h"

#define ENEMY_BASE_LIFE (120)
#define ENEMY_SPAN (240)
#define ENEMYBASE_RESPAWN (3600)

//オブジェクト2Dクラス
class CEnemyBase:public CObject
{
public:
	typedef enum
	{
		TYPE_A = 0,
		TYPE_B,

		TYPE_MAX
	}TYPE;

	//メンバ関数
	CEnemyBase(int nPriority = PRIORITY_ENEMYBASE);
	~CEnemyBase();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemyBase* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void Hit(const int nDamage);
	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	bool GetUse(void) { return m_bUse; }
	void SetRespawn(bool bUse) { m_bRespawn = bUse; }

private:
	void CreateEnemy(void);

	//メンバ変数
	D3DXVECTOR3 m_pos;					//位置(オフセット)
	D3DXVECTOR3 m_rot;					//向き
	D3DXVECTOR3 m_size;					//サイズ

	D3DXMATRIX m_mtxWorld;				//ワールドマトリックス

	CModel* m_pModel;	//モデルへのポインタ
	CModel* m_pBreakModel;	//モデルへのポインタ

	int m_nLife;			//寿命
	TYPE m_type;			//種類
	bool m_bUse;			//使用しているか
	int m_nPriority;
	int m_nCntSpan;
	int m_nRespawn;
	bool m_bRespawn;

	CEnemyGauge* m_pGauge;

	CMapEnemyBase* m_pMapIcon;
};

#endif