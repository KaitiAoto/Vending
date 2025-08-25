//==============================
//
// �p�[�e�B�N��[particle.h]
// Author:kaiti
//
//==============================
#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "main.h"
#include "object.h"
#include "effect.h"

//�I�u�W�F�N�g2D�N���X
class CParticle:public CObject
{
public:
	//���
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_SMOKE,
		TYPE_SPRAY,
		TYPE_MAX
	}TYPE;

	//�����o�֐�
	CParticle();
	~CParticle();

	static CParticle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int nLife, float fRadius, TYPE type);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	//�ݒ菈��


private:
	void SetElse(D3DXCOLOR col, int nLife, float fRadius);

	void None(void);
	void Smoke(void);
	void Spray(void);
	//�����o�ϐ�

	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//�p�x

	float m_fLength; //�Ίp���̒���
	float m_fAngle;  //�Ίp���̊p�x

	D3DXCOLOR m_col;
	float m_fRadius;
	int m_nLife;

	bool m_bUse;

	TYPE m_type;
};

#endif