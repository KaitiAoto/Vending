//==============================
//
// パーティクル[particle.h]
// Author:kaiti
//
//==============================
#ifndef _EFFECT_CIRCLE_H_
#define _EFFECT_CIRCLE_H_

#include "main.h"
#include "object.h"
#include "meshcircle.h"


//オブジェクト2Dクラス
class CEffectCircle:public CObject
{
public:
	//種類
	typedef enum
	{
		TYPE_UPDOWN = 0,
		TYPE_MAX
	}TYPE;

	//メンバ関数
	CEffectCircle(int nPriority = 4);
	~CEffectCircle();

	static CEffectCircle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, D3DXCOLOR col, CMeshCircle::TYPE circle, TYPE type);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, D3DXCOLOR col, CMeshCircle::TYPE circle, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//取得処理
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	//設定処理


private:

	void UpDown(void);
	//メンバ変数

	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_posOff;	//位置
	D3DXVECTOR3 m_rot;	//角度
	D3DXCOLOR m_col;
	float m_fRadius;
	int m_nLife;

	bool m_bUse;

	TYPE m_type;

	CMeshCircle* m_pCircle;

	bool m_bUp;
};

#endif