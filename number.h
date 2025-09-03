//=====================
//
// ����[number.h]
// Author : Kaiti Aoto
//
//=====================

// ��d�C���N���[�h�h�~
#ifndef _NUMBER_H_
#define _NUMBER_H_

// �C���N���[�h
#include "main.h"
#include "object.h"

// �}�N����`
#define NUMBER_SIZE (25)

// �����N���X
class CNumber
{
public:

	// �����o�֐�
	CNumber();
	~CNumber();

	HRESULT Init(const char* pFilename, D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �擾����
	LPDIRECT3DVERTEXBUFFER9 GetBuff(void) { return m_pVtxBuff; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	// �ݒ菈��
	void SetBuff(LPDIRECT3DVERTEXBUFFER9 buff) { m_pVtxBuff = buff; }
	void SetPos(D3DXVECTOR3 pos);
	void SetTex(float U1, float U2, float V1, float V2);
	void SetColor(D3DCOLOR fColor);
	void SetIdxTex(int nIdx) { m_nIdxTex = nIdx; }

	// �ÓI�����o�֐�
	static CNumber* Create(const char* pFilename, D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	
	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; // ���_���
	D3DXVECTOR3 m_pos;					// �ʒu
	float m_fWidth;						// ����
	float m_fHeight;					// ����
	int m_nIdxTex;						// �e�N�X�`���̃C���f�b�N�X�ԍ�
};

#endif