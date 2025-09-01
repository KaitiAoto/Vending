//=================================
//
// �|���S���\������[object3D.h]
// Author:kaiti
//
//=================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "main.h"
#include "object.h"

#define OBJECT3D_SIZE (500)

//�N���X
class CObject3D:public CObject
{
public:
	typedef enum
	{
		TYPE_FIELD= 0,
		TYPE_WALL,
		TYPE_SHADOW,
		TYPE_MAX
	}TYPE;


	//�����o�֐�
	CObject3D(int nPriority = 1);
	//���z�֐�
	~CObject3D();
	HRESULT Init(const char* pTexName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObject3D* Create(const char* pTexName,D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, TYPE type);
	void SetIdxTex(const int nIdxTex) { m_nIdxTex = nIdxTex; }
	float GetHeight(D3DXVECTOR3 pos);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetColor(D3DXCOLOR col);
	
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//����
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X

	int m_nIdxTex;
};

#endif
