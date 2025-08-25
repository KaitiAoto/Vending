//==============================
//
// エフェクト[effect.h]
// Author:kaiti
//
//==============================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "object.h"

#define EFFECT_SIZE (5)
#define EFFECT_LIFE (30)

//オブジェクト2Dクラス
class CEffect:public CObject
{
public:

	//メンバ関数
	CEffect(int nPriority = 6);
	~CEffect();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fRadius);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fRadius);
	static CEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fRadius, int nPriority);

private:
	void SetSize(float fRadius);
	void SetColor(D3DXCOLOR col);

	//メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;

	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_rot;		//角度
	D3DXVECTOR3 m_move;		//移動量
	float m_fLength;		//対角線の長さ
	float m_fAngle;			//対角線の角度
	float m_fRadius;
	bool m_bUse;			//使用しているか
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス
	int m_nIdxTex;
	D3DXCOLOR m_col;
	int m_nLife;
};

#endif