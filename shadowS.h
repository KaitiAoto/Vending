//==============================
//
// 影[shadow.h]
// Author:kaiti
//
//==============================
#ifndef _SHADOWS_H_
#define _SHADOWS_H_

#include "main.h"
#include "objectX.h"
#include "object2D.h"

//オブジェクト2Dクラス
class CShadowS:public CObjectX
{
public:

	//メンバ関数
	CShadowS(int nPriority = 4);
	~CShadowS();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CShadowS* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot) { m_pos = pos; m_rot = rot; }
private:

	//メンバ変数
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_rot;		//角度
	float m_fLength;		//対角線の長さ
	//float m_fAngle;			//対角線の角度
	float m_fRadius;
	bool m_bUse;			//使用しているか
	D3DXMATRIX m_mtxWorld;//ワールドマトリックス
	int m_nIdxTex;
	D3DXCOLOR m_col;

	CObject2D* m_pObj2D;
};

#endif