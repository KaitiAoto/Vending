//==============================
//
// 自販機[vender.h]
// Author:kaiti
//
//==============================
#ifndef START_H_
#define START_H_

#include "main.h"
#include "object.h"
#include "model.h"
//クラス
class CStart:public CObject
{
public:
	//種類
	typedef enum
	{
		TYPE_MODEL = 0,
		TYPE_VENDER,
		TYPE_ENEMY_BASE,
		TYPE_GIMMICK,
		TYPE_MAX
	}TYPE;

	//メンバ関数
	CStart(int nPriority = PRIORITY_START);
	~CStart();
	HRESULT Init(const char* pFilename, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CStart* Create(const char* pFilename, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }
	bool GetStart(void) { return m_bDraw; }

	void SetDraw(bool bDraw) { m_bDraw = bDraw; }
private:
	//メンバ変数
	D3DXVECTOR3 m_pos;			//位置(オフセット)
	D3DXVECTOR3 m_rot;			//向き
	D3DXVECTOR3 m_size;			//サイズ

	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス

	CModel* m_pModel;			//モデルへのポインタ

	bool m_bDraw;
};

#endif