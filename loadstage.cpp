//==============================
//
// �e�N�X�`��[texture.cpp]
// Author:kaiti
//
//==============================
#include "loadstage.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "vender.h"
#include "enemy_base.h"
#include "player.h"
#include "bullet.h"
#include "camera.h"
#include "object3D.h"
#include "gimmick.h"
#include "wall_invisible.h"
//==================
// �R���X�g���N�^
//==================
CLoadStage::CLoadStage()
{
	m_nCntStage = 0;
	m_nNumModel = 0;
}
//================
// �f�X�g���N�^
//================
CLoadStage::~CLoadStage()
{
}
//=======================
// �X�e�[�W�ǂݍ���
//=======================
void CLoadStage::Load(const char* pFilename)
{
	CCamera* pCamera = CManager::GetCamera();

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	int nNumTexture = 0;
	char aTextureName[NUM_STAGE_TEXTURE][MAX_WORD]; // NUM_STAGE_TEXTURE ��K�؂Ȓ萔��
	int nCntTexture = 0;

	int Index = 0;
	int nCntModel = 0;
	char aModelName[NUM_STAGE_MODEL][MAX_WORD];
	char aPlayer[MAX_WORD];

	CStage::TYPE type = CStage::TYPE_MODEL;
	float degX, degY, degZ;

	int textype = 0;
	D3DXVECTOR3 fieldPos, fieldRot;
	D3DXVECTOR2 fieldBlock, fieldSize;

	char equal[MAX_WORD];

	FILE* pFile;
	pFile = fopen(pFilename, "r");

	if (pFile != NULL)
	{//�t�@�C�����J������
		char aString[MAX_WORD];

		while (fscanf(pFile, "%s", aString) != EOF)
		{
			// �R�����g�s�̃X�L�b�v
			if (aString[0] == '#')
			{
				fgets(aString, MAX_WORD, pFile); // �s���܂œǂݔ�΂�
				continue;
			}

			//fscanf(pFile, "%s", &aString[0]);

			if (strcmp(aString, "SCRIPT") == 0)
			{
				while (fscanf(pFile, "%s", aString) != EOF)
				{
					// �R�����g�s�X�L�b�v
					if (aString[0] == '#')
					{
						fgets(aString, MAX_WORD, pFile);
						continue;
					}
					//---------------------------------------------------
					// �e�N�X�`�����
					//---------------------------------------------------
					// �e�N�X�`����
					else if (strcmp(aString, "NUM_TEXTURE") == 0)
					{
						fscanf(pFile, "%s %d", equal, &nNumTexture);
					}
					// �e�N�X�`���t�@�C����
					else if (strcmp(aString, "TEXTURE_FILENAME") == 0)
					{
						fscanf(pFile, "%s %s", equal, &aTextureName[nCntTexture][0]);

						nCntTexture++;
					}
					//---------------------------------------------------
					// ���f�����
					//---------------------------------------------------
					//���f����
					if (strcmp(aString, "NUM_MODEL") == 0)
					{
						fscanf(pFile, "%s %d", equal, &m_nNumModel);
					}
					//���f���t�@�C����
					else if (strcmp(aString, "MODEL_FILENAME") == 0)
					{
						fscanf(pFile, "%s %s", equal, &aModelName[nCntModel][0]);

						nCntModel++;
					}

					//----------------------------------------------------
					// �t�B�[���h����
					//----------------------------------------------------
					else if (strcmp(aString, "FIELDSET") == 0)
					{
						while (fscanf(pFile, "%s", aString) != EOF)
						{
							// �R�����g�s�X�L�b�v
							if (aString[0] == '#')
							{
								fgets(aString, MAX_WORD, pFile);
								continue;
							}

							if (strcmp(aString, "TEXTYPE") == 0)
							{
								fscanf(pFile, "%s %d", equal, &textype);
							}
							else if (strcmp(aString, "POS") == 0)
							{
								fscanf(pFile, "%s %f %f %f", equal, &fieldPos.x, &fieldPos.y, &fieldPos.z);
							}
							else if (strcmp(aString, "ROT") == 0)
							{
								float rx, ry, rz;
								fscanf(pFile, "%s %f %f %f", equal, &rx, &ry, &rz);
								fieldRot.x = D3DXToRadian(rx);
								fieldRot.y = D3DXToRadian(ry);
								fieldRot.z = D3DXToRadian(rz);
							}
							else if (strcmp(aString, "SIZE") == 0)
							{
								fscanf(pFile, "%s %f %f", equal, &fieldSize.x, &fieldSize.y);
							}
							else if (strcmp(aString, "END_FIELDSET") == 0)
							{
								// �t�B�[���h�����֐����Ăяo���i���j
								CObject3D::Create(&aTextureName[textype][0], fieldPos, fieldRot, fieldSize.x, fieldSize.y, CObject3D::TYPE_FIELD);
								//CreateField(textype, fieldPos, fieldRot, fieldBlock, fieldSize);
								break;
							}
						}
					}
					//----------------------------------------------------
					// �ǐ���
					//----------------------------------------------------
					else if (strcmp(aString, "WALLSET") == 0)
					{
						while (fscanf(pFile, "%s", aString) != EOF)
						{
							// �R�����g�s�X�L�b�v
							if (aString[0] == '#')
							{
								fgets(aString, MAX_WORD, pFile);
								continue;
							}

							if (strcmp(aString, "TEXTYPE") == 0)
							{
								fscanf(pFile, "%s %d", equal, &textype);
							}
							else if (strcmp(aString, "POS") == 0)
							{
								fscanf(pFile, "%s %f %f %f", equal, &fieldPos.x, &fieldPos.y, &fieldPos.z);
							}
							else if (strcmp(aString, "ROT") == 0)
							{
								float rx, ry, rz;
								fscanf(pFile, "%s %f %f %f", equal, &rx, &ry, &rz);
								fieldRot.x = D3DXToRadian(rx);
								fieldRot.y = D3DXToRadian(ry);
								fieldRot.z = D3DXToRadian(rz);
							}
							else if (strcmp(aString, "SIZE") == 0)
							{
								fscanf(pFile, "%s %f %f", equal, &fieldSize.x, &fieldSize.y);
							}
							else if (strcmp(aString, "END_WALLSET") == 0)
							{
								CInvisibleWall::Create(fieldPos, fieldRot, fieldSize.x, fieldSize.y);
								//CreateField(textype, fieldPos, fieldRot, fieldBlock, fieldSize);
								break;
							}
						}
					}

					//----------------------------------------------------
					// ���f���z�u
					//----------------------------------------------------
					else if (strcmp(aString, "MODELSET") == 0)
					{
						while (fscanf(pFile, "%s", aString) != EOF)
						{
							// �R�����g�s�X�L�b�v
							if (aString[0] == '#')
							{
								fgets(aString, MAX_WORD, pFile);
								continue;
							}

							//���f���ԍ�
							if (strcmp(aString, "TYPE") == 0)
							{
								fscanf(pFile, "%s %d", equal, &Index);
							}
							//�ʒu
							else if (strcmp(aString, "POS") == 0)
							{
								fscanf(pFile, "%s %f %f %f", equal, &pos.x, &pos.y, &pos.z);
							}
							//����
							else if (strcmp(aString, "ROT") == 0)
							{
								fscanf(pFile, "%s %f %f %f", equal, &degX, &degY, &degZ);

								rot.x = degX * (D3DX_PI / 180.0f);
								rot.y = degY * (D3DX_PI / 180.0f);
								rot.z = degZ * (D3DX_PI / 180.0f);
							}
							//���
							else if (strcmp(aString, "OBJECT") == 0)
							{
								fscanf(pFile, "%s %d", equal, &type);
							}
							else if (strcmp(aString, "END_MODELSET") == 0)
							{
								Create(&aModelName[Index][0], pos, rot, type);
								m_nCntStage++;
								break;
							}
						}
					}

					//------------------------------------------------------
					// �v���C���[�z�u
					//------------------------------------------------------
					else if (strcmp(aString, "PLAYERSET") == 0)
					{
						while (fscanf(pFile, "%s", aString) != EOF)
						{
							// �R�����g�s�X�L�b�v
							if (aString[0] == '#')
							{
								fgets(aString, MAX_WORD, pFile);
								continue;
							}

							//���f���t�@�C����
							if (strcmp(aString, "MOTION_FILENAME") == 0)
							{
								fscanf(pFile, "%s %s", equal, &aPlayer[0]);
							}
							//�ʒu
							else if (strcmp(aString, "POS") == 0)
							{
								fscanf(pFile, "%s %f %f %f", equal, &pos.x, &pos.y, &pos.z);
							}
							//����
							else if (strcmp(aString, "ROT") == 0)
							{
								fscanf(pFile, "%s %f %f %f", equal, &degX, &degY, &degZ);

								rot.x = degX * (D3DX_PI / 180.0f);
								rot.y = degY * (D3DX_PI / 180.0f);
								rot.z = degZ * (D3DX_PI / 180.0f);
							}
							else if (strcmp(aString, "END_PLAYERSET") == 0)
							{
								if (CManager::GetScene()->GetMode() == CScene::MODE_GAME)
								{
									//�v���C���[���擾
									CPlayer* pPlayer = CGame::GetPlayer();

									pPlayer = CPlayer::Create(aPlayer, pos, rot);
									CGame::SetPlayer(pPlayer);
								}
								break;
							}
						}
					}

					//------------------------------------------------------
					// �J�����z�u
					//------------------------------------------------------
					else if (strcmp(aString, "CAMERASET") == 0)
					{
						while (fscanf(pFile, "%s", aString) != EOF)
						{
							// �R�����g�s�X�L�b�v
							if (aString[0] == '#')
							{
								fgets(aString, MAX_WORD, pFile);
								continue;
							}

							//���_
							if (strcmp(aString, "POS") == 0)
							{
								fscanf(pFile, "%s %f %f %f", equal, &pos.x, &pos.y, &pos.z);
								pCamera->SetPosV(pos);
							}
							//�����_
							else if (strcmp(aString, "REF") == 0)
							{
								fscanf(pFile, "%s %f %f %f", equal, &pos.x, &pos.y, &pos.z);
								pCamera->SetPosR(pos);
							}
							else if (strcmp(aString, "END_CAMERASET") == 0)
							{
								break;
							}
						}
					}

					else if (strcmp(aString, "END_SCRIPT") == 0)
					{
						break;
					}
				}
			}
		}
		fclose(pFile);//�t�@�C�������
	}
	else
	{
		// ��O
		return;
	}
}
//=======================
// �S�e�N�X�`���j��
//=======================
void CLoadStage::Unload(void)
{

}
//==============
// ���f������
//==============
void CLoadStage::Create(const char* pFilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot, CStage::TYPE type)
{
	switch (type)
	{
	case CStage::TYPE_MODEL:
		CStage::Create(pFilename, pos, rot);
		break;
	case CStage::TYPE_VENDER:
	{
		CBullet::TYPE Type = CVender::SetType(pFilename);
		CVender::Create(pos, rot, Type);
		break;
	}
	case CStage::TYPE_ENEMY_BASE:
		CEnemyBase::Create(pos, rot);
		break;

	case CStage::TYPE_GIMMICK:
	{
		CGimmick::TYPE Gimmicktype = CGimmick::SetType(pFilename);
		CGimmick::Create(pos, rot, Gimmicktype);
		break;
	}
	default:
		break;
	}
}