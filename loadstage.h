//==============================
//
// �e�N�X�`��[texture.h]
// Author:kaiti
//
//==============================
#ifndef LOADSTAGE_H_
#define LOADSTAGE_H_

#include "main.h"
#include "stage.h"

#define NUM_STAGE_MODEL (64)
#define MAX_STAGE_MODEL (512)
#define NUM_STAGE_TEXTURE (16)

//�I�u�W�F�N�g�N���X
class CLoadStage
{
public:
	//�����o�֐�
	CLoadStage();
	~CLoadStage();
	void Load(const char* pFilename);
	void Unload(void);

private:
	void Create(const char* pFilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot, CStage::TYPE type);

	//
	int m_nNumModel;

	int m_nCntStage;
};

#endif