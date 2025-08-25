//==============================
//
// �e[bullet.h]
// Author:kaiti
//
//==============================
#ifndef BULET_H_
#define BULET_H_

#include "main.h"
#include "object.h"
#include "model.h"

#define BULET_SIZE (30)
#define BULLET_LIFE (200)

//�I�u�W�F�N�g2D�N���X
class CBullet:public CObject
{
public:
	//���
	typedef enum
	{
		USER_PLAYER = 0,
		USER_ENEMY,
		USER_MAX
	}USER;
	typedef enum
	{
		TYPE_A = 0,
		TYPE_B,

		TYPE_MAX
	}TYPE;

	//�����o�֐�
	CBullet(int nPriority = 2);
	~CBullet();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, USER user);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBullet* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, USER user);

	void SetUser(USER user) { m_user = user; };
	int GetUser(void) { return m_user; }
private:
	void Move(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;					//�ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 m_rot;					//����
	D3DXVECTOR3 m_move;					//�ړ���
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_rotDest;				//�ڕW�̌���

	CModel* m_pModel;	//���f���ւ̃|�C���^

	int m_nLife;			//����
	TYPE m_type;			//���
	USER m_user;
	bool m_bUse;			//�g�p���Ă��邩
	int m_nPriority;
};

#endif