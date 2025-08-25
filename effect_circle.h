//==============================
//
// �p�[�e�B�N��[particle.h]
// Author:kaiti
//
//==============================
#ifndef _EFFECT_CIRCLE_H_
#define _EFFECT_CIRCLE_H_

#include "main.h"
#include "object.h"
#include "meshcircle.h"


//�I�u�W�F�N�g2D�N���X
class CEffectCircle:public CObject
{
public:
	//���
	typedef enum
	{
		TYPE_UPDOWN = 0,
		TYPE_MAX
	}TYPE;

	//�����o�֐�
	CEffectCircle(int nPriority = 4);
	~CEffectCircle();

	static CEffectCircle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, D3DXCOLOR col, CMeshCircle::TYPE circle, TYPE type);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, D3DXCOLOR col, CMeshCircle::TYPE circle, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	//�ݒ菈��


private:

	void UpDown(void);
	//�����o�ϐ�

	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_posOff;	//�ʒu
	D3DXVECTOR3 m_rot;	//�p�x
	D3DXCOLOR m_col;
	float m_fRadius;
	int m_nLife;

	bool m_bUse;

	TYPE m_type;

	CMeshCircle* m_pCircle;

	bool m_bUp;
};

#endif