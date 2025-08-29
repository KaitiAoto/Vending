//==============================
//
// 弾[bullet.h]
// Author:kaiti
//
//==============================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "object.h"
#include "model.h"
#include "player.h"

#define ITEM_LIFE (1200)
#define ITEM_HEAL (PLAYER_LIFE / 4)
#define ITEM_BULLET (10)
//オブジェクト2Dクラス
class CItem:public CObject
{
public:
	//種類
	typedef enum
	{
		TYPE_BULLET = 0,
		TYPE_LIFE,
		TYPE_MAX
	}TYPE;

	//メンバ関数
	CItem(int nPriority = PRIORITY_ITEM);
	~CItem();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CItem* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, TYPE type);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	TYPE GetType(void) { return m_type; }
	void SetUse(bool bUse) { m_bUse = bUse; }
	bool GetUse(void) { return m_bUse; }
	void Bonus(void);

private:
	void Move(void);

	//メンバ変数
	D3DXVECTOR3 m_pos;					//位置(オフセット)
	D3DXVECTOR3 m_rot;					//向き
	D3DXVECTOR3 m_move;					//移動量
	D3DXMATRIX m_mtxWorld;				//ワールドマトリックス
	D3DXVECTOR3 m_rotDest;				//目標の向き
	D3DXVECTOR3 m_size;					//サイズ

	CModel* m_pModel;	//モデルへのポインタ

	int m_nLife;			//寿命
	TYPE m_type;			//種類
	bool m_bUse;			//使用しているか

	float m_fFloatTime;
};

#endif