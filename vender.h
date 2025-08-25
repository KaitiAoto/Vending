//==============================
//
// 自販機[vender.h]
// Author:kaiti
//
//==============================
#ifndef VENDER_H_
#define VENDER_H_

#include "main.h"
#include "object.h"
#include "model.h"
#include "bullet.h"
#include "meshcylinder.h"

class CRestock;

#define MAX_RESTOCK (50)
#define NUM_REUSETIME (600)

//クラス
class CVender:public CObject
{
public:
	//メンバ関数
	CVender(int nPriority = PRIORITY_VENDER);
	~CVender();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CBullet::TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CVender* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, CBullet::TYPE type);

	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	int GetRestock(void) { return m_nRestock; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	CBullet::TYPE GetType(void) { return m_type; }
	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }
	bool GetUse(void) { return m_bUseRestock; }
	CRestock* GetpRestock(void) { return m_pRestock; }

	void SetUseRestock(bool bUse) { m_bUseRestock = bUse; }
	static CBullet::TYPE SetType(const char* pFileName);

private:
	const char* SetModelName(void);

	//メンバ変数
	D3DXVECTOR3 m_pos;			//位置(オフセット)
	D3DXVECTOR3 m_rot;			//向き
	D3DXVECTOR3 m_size;			//サイズ

	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス

	CModel* m_pModel;			//モデルへのポインタ
	int m_nPriority;
	bool m_bUse;				//使用しているか
	bool m_bUseRestock;			//補充できるか
	int m_nCntReuse;			//再使用できるまでの時間
	int m_nRestock;				//補充数

	CBullet::TYPE m_type;		//補充する中身の種類

	CMeshCylinder* m_pCylinder;
	CRestock* m_pRestock;
};

#endif