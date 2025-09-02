//==============================
//
// �X�e�[�W�ǂݍ���[loadstage.h]
// Author:kaiti
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef LOADSTAGE_H_
#define LOADSTAGE_H_

// �C���N���[�h
#include "main.h"
#include "stage.h"

// �}�N����`
#define NUM_STAGE_MODEL (64)
#define MAX_STAGE_MODEL (512)
#define NUM_STAGE_TEXTURE (16)

// �X�e�[�W�ǂݍ��݃N���X
class CLoadStage
{
public:
	// �����o�֐�
	CLoadStage();
	~CLoadStage();
	void Load(const char* pFilename);
	void Unload(void);

private:
	void Create(const char* pFilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot, CStage::TYPE type);

	// �����o�ϐ�
	int m_nNumModel;	// �ő僂�f����
	int m_nCntStage;	// �X�e�[�W���f���J�E���g
};

#endif