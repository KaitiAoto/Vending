//==============================================
//
// ���b�V���~�\������[meshcircle.h]
// Author : Kaiti Aoto
//
//==============================================

// ��d�C���N���[�h�h�~
#ifndef _MESHCIRCLE_H_
#define _MESHCIRCLE_H_

// �C���N���[�h
#include "main.h"
#include "object.h"

// �}�N����`
#define MESHCIRCLEVTX_X (15)	// ��
#define MESHCIRCLEVTX_Z (2)		// �c
#define MAXCIRCLE_VTX ((MESHCIRCLEVTX_X + 1) * (MESHCIRCLEVTX_Z + 1))							// ���_��
#define CIRCLEPOLYGON_NO (MESHCIRCLEVTX_X * MESHCIRCLEVTX_Z * 2 + (MESHCIRCLEVTX_Z - 1) * 4)	// �|���S����
#define CIRCLEINDEX_NO ((MESHCIRCLEVTX_X + 1) * 2 * MESHCIRCLEVTX_Z + (MESHCIRCLEVTX_Z - 1) * 2)// �C���f�b�N�X��
#define MESHCIRCLE_SIZE (150.0f)

// ���b�V���~�N���X
class CMeshCircle :public CObject
{
public:
	// ���
	typedef enum
	{
		TYPE_IN = 0,
		TYPE_OUT,
		TYPE_BOTHSIDES,
		TYPE_MAX
	}TYPE;

	// �����o�֐�
	CMeshCircle(int nPriority = 4);
	~CMeshCircle();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, D3DXCOLOR col, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	// �擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	// �ݒ�
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetUse(bool bUse) { m_bUse = bUse; }

	// �ÓI�����o�֐�
	static CMeshCircle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, D3DXCOLOR col, TYPE type);

private:
	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// �o�b�t�@
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	TYPE m_type;						// ���
	bool m_bUse;						// �g�p���Ă��邩
	int m_nIdxTex;						// �e�N�X�`���̃C���f�b�N�X�ԍ�
};

#endif