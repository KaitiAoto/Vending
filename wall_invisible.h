//==============================
//
// �e[shadow.h]
// Author:kaiti
//
//==============================
#ifndef _WALL_INVISIBLE_H_
#define _WALL_INVISIBLE_H_

#include "main.h"
#include "object3D.h"

//�I�u�W�F�N�g2D�N���X
class CInvisibleWall:public CObject3D
{
public:

	//�����o�֐�
	CInvisibleWall(int nPriority = 1);
	~CInvisibleWall();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CInvisibleWall* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	D3DXVECTOR3 GetSize();
private:

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//�p�x
	float m_fWidth;
	float m_fHeight;
	bool m_bUse;			//�g�p���Ă��邩
	D3DXMATRIX m_mtxWorld;//���[���h�}�g���b�N�X
	int m_nIdxTex;
	D3DXCOLOR m_col;
	bool m_bDraw;
};

#endif