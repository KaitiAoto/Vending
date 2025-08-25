//==============================
//
// ���̋@[vender.h]
// Author:kaiti
//
//==============================
#ifndef STAGE_H_
#define STAGE_H_

#include "main.h"
#include "object.h"
#include "model.h"
//�N���X
class CStage:public CObject
{
public:
	//���
	typedef enum
	{
		TYPE_MODEL = 0,
		TYPE_VENDER,
		TYPE_ENEMY_BASE,
		TYPE_GIMMICK,
		TYPE_MAX
	}TYPE;

	//�����o�֐�
	CStage(int nPriority = PRIORITY_STAGE);
	~CStage();
	HRESULT Init(const char* pFilename, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CStage* Create(const char* pFilename, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }
private:
	//�����o�ϐ�
	D3DXVECTOR3 m_pos;			//�ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_size;			//�T�C�Y

	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X

	CModel* m_pModel;			//���f���ւ̃|�C���^
};

#endif