//==============================
//
// 影[shadow.h]
// Author:kaiti
//
//==============================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
#include "object3D.h"

//オブジェクト2Dクラス
class CShadow:public CObject3D
{
public:

	//メンバ関数
	CShadow(int nPriority = 2);
	~CShadow();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CShadow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);
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
};

#endif