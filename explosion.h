//==============================
//
// ����[explosion.h]
// Author:kaiti
//
//==============================
#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "main.h"
#include "object2D.h"

#define EXPLOSION_SIZE (30)
#define EXPLOSION_LIFE (60)

//�I�u�W�F�N�g2D�N���X
class CExplosion:public CObject2D
{
public:
	//���
	typedef enum
	{
		TYPE_A = 0,
		TYPE_B,
		TYPE_MAX
	}TYPE;

	//�����o�֐�
	CExplosion(int nPriority = 3);
	~CExplosion();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CExplosion* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);

	static HRESULT Load(void);
	static void Unload(void);
	void SetType(TYPE type) { m_type = type; };

private:
	void Animation(void);

	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`��

	D3DXVECTOR3 m_move; //�ړ���

	float m_fLength;		//�Ίp���̒���
	const float m_fAngle;	//�Ίp���̊p�x
	int m_nCntAnim;			//�A�j���[�V�����J�E���^�[
	int m_nPattermAnim;		//�A�j���[�V�����p�^�[��
	int m_nLife;			//����
	bool m_bUse;			//�g�p���Ă��邩
	TYPE m_type;			//���

};

#endif