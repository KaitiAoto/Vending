//==============================
//
// 影[shadow.h]
// Author:kaiti
//
//==============================

// 二重インクルード防止
#ifndef _SHADOW_H_
#define _SHADOW_H_

// インクルード
#include "main.h"
#include "object3D.h"

// 影クラス
class CShadow:public CObject3D
{
public:

	// メンバ関数
	CShadow(int nPriority = 2);
	~CShadow();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CShadow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);
private:

	// メンバ変数
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_rot;		// 角度
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
	D3DXCOLOR m_col;		// 色
	bool m_bUse;			// 使用しているか
	float m_fLength;		// 対角線の長さ
	float m_fRadius;		// 半径
	int m_nIdxTex;			// テクスチャのインデックス番号
};

#endif