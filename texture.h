//==============================
//
// �e�N�X�`��[texture.h]
// Author:kaiti
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

// �C���N���[�h
#include "main.h"

// �}�N����`
#define MAX_TEXTURE (128)

// �e�N�X�`���N���X
class CTexture
{
public:

	// �����o�֐�
	CTexture();
	// ���z�֐�
	~CTexture();
	HRESULT Load(void);
	void Unload(void);
	int Register(const char* pFilename);
	// �擾
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);

private:

	// �����o�ϐ�
	LPDIRECT3DTEXTURE9 m_apTex[MAX_TEXTURE];	// �e�N�X�`��
	char m_apFileName[MAX_TEXTURE][MAX_PATH];	// �e�N�X�`����

	// �ÓI�����o�֐�
	static int m_nNumAll;						// �ő吔
};

#endif