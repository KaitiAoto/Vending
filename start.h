//==============================
//
// �X�^�[�g[start.h]
// Author:kaiti
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _START_H_
#define _START_H_

// �C���N���[�h
#include "main.h"
#include "object.h"
#include "model.h"

//�X�^�[�g�N���X
class CStart:public CObject
{
public:
	// ���
	typedef enum
	{
		TYPE_MODEL = 0,
		TYPE_VENDER,
		TYPE_ENEMY_BASE,
		TYPE_GIMMICK,
		TYPE_MAX
	}TYPE;

	// �����o�֐�
	CStart(int nPriority = PRIORITY_START);
	~CStart();

	HRESULT Init(const char* pFilename, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	// �擾
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }
	bool GetStart(void) { return m_bDraw; }
	// �ݒ�
	void SetDraw(bool bDraw) { m_bDraw = bDraw; }

	// �ÓI�����o�֐�
	static CStart* Create(const char* pFilename, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

private:
	// �����o�ϐ�
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_rot;			// ����
	D3DXVECTOR3 m_size;			// �T�C�Y
	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	CModel* m_pModel;			// ���f���ւ̃|�C���^
	bool m_bDraw;				// �`�悷�邩�ǂ���
};

#endif