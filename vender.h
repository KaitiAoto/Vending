//==============================
//
// ���̋@[vender.h]
// Author : Kaiti Aoto
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef VENDER_H_
#define VENDER_H_

// �C���N���[�h
#include "main.h"
#include "object.h"
#include "model.h"
#include "bullet.h"
#include "meshcylinder.h"

// �O���錾
class CRestock;

// �}�N����`
#define MAX_RESTOCK (25)
#define NUM_REUSETIME (600)

// ���̋@�N���X
class CVender:public CObject
{
public:
	// �����o�֐�
	CVender(int nPriority = PRIORITY_VENDER);
	~CVender();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CBullet::TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	// �ݒ�
	void SetUseRestock(bool bUse) { m_bUseRestock = bUse; }

	// �擾
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }
	CRestock* GetpRestock(void) { return m_pRestock; }
	CBullet::TYPE GetType(void) { return m_type; }
	bool GetUse(void) { return m_bUseRestock; }
	int GetRestock(void) { return m_nRestock; }


	// �ÓI�����o�֐�
	static CVender* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, CBullet::TYPE type);
	// �ݒ�
	static CBullet::TYPE SetType(const char* pFileName);

private:
	const char* SetModelName(void);

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_rot;			// ����
	D3DXVECTOR3 m_size;			// �T�C�Y
	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	CModel* m_pModel;			// ���f���ւ̃|�C���^
	CMeshCylinder* m_pCylinder;	// �V�����_�[�ւ̃|�C���^
	CRestock* m_pRestock;		// ��[�t�h�ւ̃|�C���^
	CBullet::TYPE m_type;		// ��[���钆�g�̎��
	bool m_bUse;				// �g�p���Ă��邩
	bool m_bUseRestock;			// ��[�ł��邩
	int m_nCntReuse;			// �Ďg�p�ł���܂ł̎���
	int m_nRestock;				// ��[��


};

#endif