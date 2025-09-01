//==============================
//
// 敵拠点[enemy_base.h]
// Author:kaiti
//
//==============================
#ifndef _ENEMY_GROUP_H_
#define _ENEMY_GROUP_H_

#include "main.h"
#include "object.h"

#define ENEMYGROUP_RESPAWN (2400)

//オブジェクト2Dクラス
class CEnemyGroup:public CObject
{
public:
	//メンバ関数
	CEnemyGroup(int nPriority = PRIORITY_ENEMYBASE);
	~CEnemyGroup();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemyGroup* Create(const D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	bool GetUse(void) { return m_bUse; }
	void SetRespawn(bool bUse) { m_bRespawn = bUse; }

	void SubMyEnemy(void) { m_MyEnemy--; }
private:
	void CreateEnemy(void);

	//メンバ変数
	D3DXVECTOR3 m_pos;					//位置(オフセット)

	bool m_bUse;			//使用しているか
	int m_nRespawn;
	bool m_bRespawn;

	int m_MyEnemy;
};

#endif