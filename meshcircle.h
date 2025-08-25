//==============================================
//
// メッシュ円柱表示処理[MeshCIRCLE.h]
// Author:kaiti
//
//==============================================
#ifndef _MESHCIRCLE_H_
#define _MESHCIRCLE_H_

#include "main.h"
#include "object.h"

//マクロ定義
#define MESHCIRCLEVTX_X (15)//横
#define MESHCIRCLEVTX_Z (2)//縦

#define MAXCIRCLE_VTX ((MESHCIRCLEVTX_X + 1) * (MESHCIRCLEVTX_Z + 1))//頂点数

#define CIRCLEPOLYGON_NO (MESHCIRCLEVTX_X * MESHCIRCLEVTX_Z * 2 + (MESHCIRCLEVTX_Z - 1) * 4)//ポリゴン数
#define CIRCLEINDEX_NO ((MESHCIRCLEVTX_X + 1) * 2 * MESHCIRCLEVTX_Z + (MESHCIRCLEVTX_Z - 1) * 2)//インデックス数

#define MESHCIRCLE_SIZE (150.0f)

class CMeshCircle :public CObject
{
public:
	//種類
	typedef enum
	{
		TYPE_IN = 0,
		TYPE_OUT,
		TYPE_BOTHSIDES,
		TYPE_MAX
	}TYPE;


	CMeshCircle(int nPriority = 4);
	~CMeshCircle();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, D3DXCOLOR col, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeshCircle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, D3DXCOLOR col, TYPE type);
	void SetUse(bool bUse) { m_bUse = bUse; }

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	int m_nIdxTex;

	//インデックスバッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;

	D3DXVECTOR3 m_pos;//位置
	D3DXVECTOR3 m_rot;//向き
	D3DXMATRIX m_mtxWorld;//ワールドマトリックス

	TYPE m_type;
	bool m_bUse;
};

#endif