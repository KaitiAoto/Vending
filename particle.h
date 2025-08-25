//==============================
//
// パーティクル[particle.h]
// Author:kaiti
//
//==============================
#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "main.h"
#include "object.h"
#include "effect.h"

//オブジェクト2Dクラス
class CParticle:public CObject
{
public:
	//種類
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_SMOKE,
		TYPE_SPRAY,
		TYPE_MAX
	}TYPE;

	//メンバ関数
	CParticle();
	~CParticle();

	static CParticle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int nLife, float fRadius, TYPE type);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//取得処理
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	//設定処理


private:
	void SetElse(D3DXCOLOR col, int nLife, float fRadius);

	void None(void);
	void Smoke(void);
	void Spray(void);
	//メンバ変数

	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_rot;	//角度

	float m_fLength; //対角線の長さ
	float m_fAngle;  //対角線の角度

	D3DXCOLOR m_col;
	float m_fRadius;
	int m_nLife;

	bool m_bUse;

	TYPE m_type;
};

#endif