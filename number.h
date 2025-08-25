//=====================
//
// ����[number.h]
// Author:kaiti
//
//=====================
#ifndef NUMBER_H_
#define NUMBER_H_

#include "main.h"
#include "object.h"

#define NUMBER_SIZE (25)

//�I�u�W�F�N�g2D�N���X
class CNumber
{
public:

	//�����o�֐�
	CNumber();
	~CNumber();

	static CNumber* Create(const char* pFilename, D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(const char* pFilename, D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�擾����
	LPDIRECT3DVERTEXBUFFER9 GetBuff(void) { return m_pVtxBuff; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	//�ݒ菈��
	void SetBuff(LPDIRECT3DVERTEXBUFFER9 buff) { m_pVtxBuff = buff; }
	void SetPos(D3DXVECTOR3 pos);
	void SetTex(float U1, float U2, float V1, float V2);
	void SetColor(D3DCOLOR fColor);
	void SetIdxTex(int nIdx) { m_nIdxTex = nIdx; }

private:
	
	//�����o�ϐ�
	int m_nIdxTex;				//�e�N�X�`���C���f�b�N�X�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_���

	D3DXVECTOR3 m_pos;	//�ʒu
	float m_fWidth;
	float m_fHeight;
};

#endif