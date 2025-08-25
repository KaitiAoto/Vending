//==============================
//
//  ���[�V��������[motion.h]
//  Author:kaiti
//
//==============================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"
#include "model.h"

#define MAX_KEY (300)//�L�[�̍ő吔

//�N���X
class CMotion
{
public:
	//���[�V�����̎��
	typedef enum
	{
		TYPE_NEUTRAL = 0,
		TYPE_MOVE,
		TYPE_ACTION,
		TYPE_JUMP,
		TYPE_LANDING,

		TYPE_MAX,
	}TYPE;

	//�L�[�̍\����
	typedef struct
	{
		float fPosX;
		float fPosY;
		float fPosZ;

		float fRotX;
		float fRotY;
		float fRotZ;
	}KEY;

	//�L�[���̍\����
	typedef struct
	{
		int nFrame;
		KEY aKey[MAX_PARTS];
	}KEY_INFO;

	//���[�V�������̍\����
	typedef struct
	{
		bool bLoop;
		int nNumKey;
		KEY_INFO aKeyInfo[MAX_KEY];
	}MOTION_INFO;

	//�����o�֐�
	CMotion();
	//���z�֐�
	~CMotion();

	void StartBlend(TYPE from, TYPE to, int nBlendFrame);

	void Update(const int nMaxPart, CModel** pModel);

	static CMotion* Load(const char* pFilename);

	D3DXVECTOR3 LerpVec3(const D3DXVECTOR3& a, const D3DXVECTOR3& b, float t);
	D3DXVECTOR3 LerpKey(TYPE type, int part, int keyA, int keyB, float t, bool isPos);

	void SetType(TYPE type) { m_type = type; }
	TYPE GetType(void) { return m_type; }
private:
	MOTION_INFO m_aMotionInfo[TYPE_MAX];//���[�V�������
	int m_nNumMotion;					//���[�V�����̑���
	TYPE m_type;						//���[�V�����̎��
	bool m_bLoop;						//���[�v���邩�ǂ���
	int m_nKey;							//���݂̃L�[No
	int m_nCntMotion;					//���[�V�����̃J�E���^�[

	bool m_bBlend;						// �u�����h����
	float m_fBlendRate;					// �u�����h�i�s (0.0�`1.0)
	int m_nBlendFrame;					// �u�����h�ɂ�����t���[����
	TYPE m_typeFrom;					// ���̃��[�V����
	TYPE m_typeTo;						// �ڍs�惂�[�V����

	int m_nKeyFrom;
	int m_nKeyTo;
	int m_nCntFrom;
	int m_nCntTo;
};

#endif 