//==============================
//
// �e�N�X�`��[texture.h]
// Author:kaiti
//
//==============================
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "main.h"

#define MAX_TEXTURE (128)

//�I�u�W�F�N�g�N���X
class CTexture
{
public:

	//�����o�֐�
	CTexture();
	//���z�֐�
	~CTexture();
	HRESULT Load(void);
	void Unload(void);
	int Register(const char* pFilename);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);

private:
	LPDIRECT3DTEXTURE9 m_apTex[MAX_TEXTURE];
	char m_apFileName[MAX_TEXTURE][MAX_PATH];
	static int m_nNumAll;
};

#endif