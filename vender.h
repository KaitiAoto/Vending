//==============================
//
// ���̋@[vender.h]
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

//�N���X
class CVender:public CObject
{
public:
	//�����o�֐�
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

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;			//�ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_size;			//�T�C�Y

	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X

	CModel* m_pModel;			//���f���ւ̃|�C���^
	int m_nPriority;
	bool m_bUse;				//�g�p���Ă��邩
	bool m_bUseRestock;			//��[�ł��邩
	int m_nCntReuse;			//�Ďg�p�ł���܂ł̎���
	int m_nRestock;				//��[��

	CBullet::TYPE m_type;		//��[���钆�g�̎��

	CMeshCylinder* m_pCylinder;
	CRestock* m_pRestock;
};

#endif