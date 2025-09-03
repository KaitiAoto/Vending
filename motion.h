//==============================
//
//  ���[�V��������[motion.h]
//  Author : Kaiti Aoto
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _MOTION_H_
#define _MOTION_H_

// �C���N���[�h
#include "main.h"
#include "model.h"

// �}�N����`
#define MAX_KEY (300)//�L�[�̍ő吔

// ���[�V�����N���X
class CMotion
{
public:
	// ���
	typedef enum
	{
		TYPE_NEUTRAL = 0,
		TYPE_MOVE,
		TYPE_ACTION,
		TYPE_JUMP,
		TYPE_LANDING,

		TYPE_MAX,
	}TYPE;

	// �L�[�̍\����
	typedef struct
	{
		float fPosX;	// X�ʒu
		float fPosY;	// Y�ʒu
		float fPosZ;	// Z�ʒu

		float fRotX;	// X����
		float fRotY;	// Y����
		float fRotZ;	// Z����
	}KEY;

	// �L�[���̍\����
	typedef struct
	{
		int nFrame;				// �t���[����
		KEY aKey[MAX_PARTS];	//�L�[�̍\����
	}KEY_INFO;

	// �\����
	typedef struct
	{
		bool bLoop;					// ���[�v���邩
		int nNumKey;				// �ő�L�[��
		KEY_INFO aKeyInfo[MAX_KEY];	// �L�[���̍\����
	}MOTION_INFO;

	// �����o�֐�
	CMotion();
	// ���z�֐�
	~CMotion();
	void Update(const int nMaxPart, CModel** pModel);
	void StartBlend(TYPE from, TYPE to, int nBlendFrame);
	D3DXVECTOR3 LerpVec3(const D3DXVECTOR3& a, const D3DXVECTOR3& b, float t);
	D3DXVECTOR3 LerpKey(TYPE type, int part, int keyA, int keyB, float t, bool isPos);

	// �ݒ�
	void SetType(TYPE type) { m_type = type; }

	// �擾
	TYPE GetType(void) { return m_type; }

	// �ÓI�����o�֐�
	static CMotion* Load(const char* pFilename);

private:
	// �����o�ϐ�
	MOTION_INFO m_aMotionInfo[TYPE_MAX];// ���
	TYPE m_type;						// ���
	bool m_bLoop;						// ���[�v���邩�ǂ���
	int m_nNumMotion;					// ����
	int m_nKey;							// ���݂̃L�[No
	int m_nCntMotion;					// ���[�V�����̃J�E���^�[
	// ���[�V�����u�����h
	bool m_bBlend;						// �u�����h����
	float m_fBlendRate;					// �u�����h�i�s (0.0�`1.0)
	TYPE m_typeFrom;					// ���̃��[�V����
	TYPE m_typeTo;						// �ڍs�惂�[�V����
	int m_nBlendFrame;					// �u�����h�ɂ�����t���[����
	int m_nKeyFrom;						// ���̃L�[
	int m_nKeyTo;						// �ڍs��̂��[
	int m_nCntFrom;						// ���̃J�E���g
	int m_nCntTo;						// �ڍs��̃J�E���g
};

#endif 