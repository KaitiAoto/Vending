//=================================
//
// �|���S���\������[object3D.h]
// Author : Kaiti Aoto
//
//=================================

// ��d�C���N���[�h�h�~
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

// �C���N���[�h
#include "main.h"
#include "object.h"

// �}�N����`
#define OBJECT3D_SIZE (500)

// �|���S���N���X
class CObject3D:public CObject
{
public:
	// ���
	typedef enum
	{
		TYPE_FIELD= 0,
		TYPE_WALL,
		TYPE_SHADOW,
		TYPE_MAX
	}TYPE;

	// �����o�֐�
	CObject3D(int nPriority = 1);
	// ���z�֐�
	~CObject3D();
	HRESULT Init(const char* pTexName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ݒ�
	void SetIdxTex(const int nIdxTex) { m_nIdxTex = nIdxTex; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetColor(D3DXCOLOR col);
	// �擾
	float GetHeight(D3DXVECTOR3 pos);
	
	// �ÓI�����o�֐�
	static CObject3D* Create(const char* pTexName,D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, TYPE type);

private:
	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// �o�b�t�@
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	int m_nIdxTex;						// �e�N�X�`���̃C���f�b�N�X�ԍ�
};

#endif
