//==============================
//
// �e�N�X�`��[texture.cpp]
// Author:kaiti
//
//==============================
#include "texture.h"
#include "manager.h"
#include "renderer.h"
//�ÓI�����o�ϐ�
int CTexture::m_nNumAll = 0;
//==================
// �R���X�g���N�^
//==================
CTexture::CTexture()
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		m_apTex[nCnt] = NULL;
		m_apFileName[nCnt][0] = NULL;
	}
}
//================
// �f�X�g���N�^
//================
CTexture::~CTexture()
{
}
//=======================
// �S�e�N�X�`���ǂݍ���
//=======================
HRESULT CTexture::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//
	const char* apFileName[MAX_TEXTURE] = 
	{
		"data\\TEXTURE\\build007.png",
		"data\\TEXTURE\\build008.png",
		
		"data\\TEXTURE\\bullet00.png",
		"data\\TEXTURE\\bullet01.png",
		"data\\TEXTURE\\bullet02.png",
		"data\\TEXTURE\\bullet03.png",
		"data\\TEXTURE\\bullet04.png",
		"data\\TEXTURE\\bullet05.png",
		"data\\TEXTURE\\bullet06.png",

		"data\\TEXTURE\\can00.jpg",	

		"data\\TEXTURE\\city00.png",
		
		"data\\TEXTURE\\conveni00.png",
		"data\\TEXTURE\\conveni01.jpg",
		"data\\TEXTURE\\conveni02.jpg",	
		
		"data\\TEXTURE\\dust00.png",
		
		"data\\TEXTURE\\effect000.png",
		
		"data\\TEXTURE\\gauge00.jpeg",

		"data\\TEXTURE\\ice00.jpg",
		"data\\TEXTURE\\ice01.jpg",

		"data\\TEXTURE\\isi.jpg",
		
		"data\\TEXTURE\\money00.jpg",
		"data\\TEXTURE\\money01.png",
		
		"data\\TEXTURE\\number000.png",
		"data\\TEXTURE\\number003.png",
		"data\\TEXTURE\\number004.png",

		"data\\TEXTURE\\rank01.png",
		"data\\TEXTURE\\rank02.png",
		"data\\TEXTURE\\rank03.png",
		"data\\TEXTURE\\rank04.png",
		"data\\TEXTURE\\rank05.png",

		"data\\TEXTURE\\restock00.png",
		
		"data\\TEXTURE\\shadow000.jpg",

		"data\\TEXTURE\\sky001.jpg",

		"data\\TEXTURE\\vending01.jpg",

		"data\\TEXTURE\\vending03.jpg",

		"data\\TEXTURE\\vending04.jpg",
		"data\\TEXTURE\\vending04_1.jpg",

		"data\\TEXTURE\\vending05.jpg",
		
		"data\\TEXTURE\\vending06.jpg",

	};
	
	//�e�N�X�`���̓ǂݍ���
	for (int nCnt = 0; apFileName[nCnt] != nullptr && nCnt < MAX_TEXTURE; nCnt++)
	{
		HRESULT hr = D3DXCreateTextureFromFile(pDevice,
			apFileName[nCnt],
			&m_apTex[nCnt]);

		if (FAILED(hr))
		{//�G���[�`�F�b�N
			return hr;
		}
		else
		{
			//�e�N�X�`�����ۑ�
			strcpy(m_apFileName[nCnt], apFileName[nCnt]);

			m_nNumAll++;//�������Z
		}
	}

	return S_OK;
}
//=======================
// �S�e�N�X�`���j��
//=======================
void CTexture::Unload(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (m_apTex[nCnt] != NULL)
		{
			m_apTex[nCnt]->Release();
			m_apTex[nCnt] = NULL;
		}
	}
}
//=======================
// �e�N�X�`���w��
//=======================
int CTexture::Register(const char* pFilename)
{
	if (this == NULL) return 0;
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (pFilename == NULL)
	{
		return -1;
	}

	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (strcmp(pFilename, m_apFileName[nCnt]) == 0)
		{
			return nCnt;//Index�ԍ���Ԃ�
		}
	}

	// ���o�^�̏ꍇ�A�V�����ǂݍ���
	if (m_nNumAll < MAX_TEXTURE)
	{
		HRESULT hr = D3DXCreateTextureFromFile(pDevice, pFilename, &m_apTex[m_nNumAll]);
		if (SUCCEEDED(hr))
		{
			strcpy(m_apFileName[m_nNumAll], pFilename);
			return m_nNumAll++;
		}
		else
		{//�G���[�`�F�b�N
			char buf[256];
			sprintf(buf, "�e�N�X�`���ǂݍ��ݎ��s: %s\n", pFilename);
			OutputDebugStringA(buf);
		}
	}

	return -1;
}
//==========================
// �e�N�X�`���A�h���X�擾
//==========================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	if (this == NULL) return 0;

	if (nIdx < 0 || nIdx >= MAX_TEXTURE)
	{//�G���[�`�F�b�N
		//OutputDebugStringA("�s���ȃe�N�X�`���C���f�b�N�X\n");
		return NULL;
	}
	return m_apTex[nIdx];
}