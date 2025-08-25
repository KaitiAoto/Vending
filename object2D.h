//==============================
//
// �I�u�W�F�N�g2D[object2D.h]
// Author:kaiti
//
//==============================
#ifndef OBJECT2D_H_
#define OBJECT2D_H_

#include "main.h"
#include "object.h"

#define OBJECT2D_SIZE (50)

//�I�u�W�F�N�g2D�N���X
class CObject2D:public CObject
{
public:

	//�����o�֐�
	//CObject2D();
	CObject2D(int nPriority = 6);
	~CObject2D();

	static CObject2D* Create(const char* pTexName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);
	static CObject2D* Create(const char* pTexName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, int nPriority);
	HRESULT Init(const char* pTexName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	virtual void Draw(void);
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; Set(m_pos, m_rot);}

	//�擾����
	LPDIRECT3DVERTEXBUFFER9 GetBuff(void) { return m_pVtxBuff; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	//�ݒ菈��
	void SetBuff(LPDIRECT3DVERTEXBUFFER9 buff) { m_pVtxBuff = buff; }
	void SetTex(float U1, float U2, float V1, float V2);
	void SetColor(D3DCOLOR fColor);
	void SetColor(D3DXCOLOR fColor);
	void SetSize(float fWidth, float fHeight);

	void SetIdxTex(const int nIdxTex) { m_nIdxTex = nIdxTex; }

	void SetUse(bool bUse) { m_bUse = bUse; }
private:
	
	//�����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_���

	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//�p�x

	float m_fLength; //�Ίp���̒���
	float m_fAngle;  //�Ίp���̊p�x

	int m_nIdxTex;

	bool m_bUse;
};

#endif