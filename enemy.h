//==============================
//
// 敵[enemy.h]
// Author:kaiti
//
//==============================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "object.h"
#include "model.h"
#include "gauge_enemy.h"

#define ENEMY_LIFE (30)
#define ENEMY_ACTIONSTATE (300)
#define ENEMY_SPEED (1.3f)

//敵クラス
class CEnemy :public CObject
{
public:
	//種類
	typedef enum
	{
		TYPE_LIGHTER = 0,
		TYPE_MONEY0,
		TYPE_MONEY1,
		TYPE_MAGNET,
		TYPE_TORNADO,
		TYPE_SPRAY,
		TYPE_EXT,
		TYPE_KETTLE,
		TYPE_RANGE,
		TYPE_MAX
	}TYPE;
	//状態
	typedef enum
	{
		STATE_NONE = 0,
		STATE_STAY,
		STATE_MOVE,
		STATE_HIT,
		STATE_ACTION,
		STATE_DEAD,
		STATE_MAX
	}STATE;

	//メンバ関数
	CEnemy(int nPriority = PRIORITY_ENEMY);
	~CEnemy();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemy* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, TYPE type);

	void SetType(TYPE type) { m_type = type; };
	TYPE GetType(void) { return m_type; }

	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void Hit(const int nDamage);
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void MovePos(D3DXVECTOR3 move) { m_pos += move; }

private:
	void Move(void);
	void Move_Normal(void);
	void Move_Charge(void);
	void Move_Jump(void);
	void Move_Shot(void);

	void State(STATE state);
	bool Collision(void);
	const char* SetModelName(void);
	void ItemSet();

	//メンバ変数
	D3DXVECTOR3 m_pos;					//位置(オフセット)
	D3DXVECTOR3 m_posOld;				//前回の位置
	D3DXVECTOR3 m_posHalf;				//
	D3DXVECTOR3 m_rot;					//向き
	D3DXVECTOR3 m_move;					//移動量
	D3DXMATRIX m_mtxWorld;				//ワールドマトリックス
	D3DXVECTOR3 m_rotDest;				//目標の向き
	D3DXVECTOR3 m_size;					//サイズ

	CModel* m_pModel;	//モデルへのポインタ

	int m_nLife;			//寿命
	TYPE m_type;			//種類
	bool m_bUse;			//使用しているか
	int m_nCntState;					//状態カウンター
	int m_nPriority;
	STATE m_State;						//状態

	int m_nStayCounter;        //滞在状態のカウント
	float m_fRandomAngle;      //ランダム方向の角度

	CEnemyGauge* m_pGauge;
};

#endif