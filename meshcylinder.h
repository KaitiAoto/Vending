//==============================================
//
// メッシュ円柱表示処理[MeshCylinder.h]
// Author:kaiti
//
//==============================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

#include "main.h"
#include "object.h"

//マクロ定義
#define MESHCYLINDERVTX_X (8)//横
#define MESHCYLINDERVTX_Z (2)//縦

#define MAXCYLINDER_VTX ((MESHCYLINDERVTX_X + 1) * (MESHCYLINDERVTX_Z + 1))//頂点数

#define CYLINDERPOLYGON_NO (MESHCYLINDERVTX_X * MESHCYLINDERVTX_Z * 2 + (MESHCYLINDERVTX_Z - 1) * 4)//ポリゴン数
#define CYLINDERINDEX_NO ((MESHCYLINDERVTX_X + 1) * 2 * MESHCYLINDERVTX_Z + (MESHCYLINDERVTX_Z - 1) * 2)//インデックス数

#define MESHCYLINDER_SIZE (150.0f)

class CMeshCylinder :public CObject
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


	CMeshCylinder();
	~CMeshCylinder();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, D3DXCOLOR col, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeshCylinder* Create(const char* pFilename,D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, D3DXCOLOR col, TYPE type);
	void SetUse(bool bUse) { m_bUse = bUse; }

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