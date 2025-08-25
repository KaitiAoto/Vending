//==============================
//
// �e[shadow.cpp]
// Author:kaiti
//
//==============================
#include "shadowS.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "debugproc.h"

//==================
// �R���X�g���N�^
//==================
CShadowS::CShadowS(int nPriority) :CObjectX(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fLength = 0;
	m_fRadius = 0;

	m_bUse = true;
	m_nIdxTex = 0;
	m_pObj2D = nullptr;
}
//================
// �f�X�g���N�^
//================
CShadowS::~CShadowS()
{
}
//===========
// ��������
//===========
CShadowS* CShadowS::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius)
{
	CShadowS* pEffect;
	//
	pEffect = new CShadowS;
	//������
	if (FAILED(pEffect->Init(pos, rot, fRadius)))
	{
		delete pEffect;
		return nullptr;
	}

	return pEffect;
}
//===============
// ����������
//===============
HRESULT CShadowS::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius)
{
	m_pos = pos;
	m_rot = rot;
	m_fRadius = fRadius;
	m_fLength=(sqrtf(fRadius * fRadius + fRadius * fRadius) / 2.0f);

	m_pObj2D = CObject2D::Create("data\\TEXTURE\\shadow000.jpg", D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), m_rot, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (m_pObj2D)
	{
		m_pObj2D->SetColor(D3DCOLOR_RGBA(1, 1, 1, 255)); // ������
	}

	CObjectX::Init(m_pos, m_rot);

	SetObjType(CObject::TYPE_SHADOW);
	
	return S_OK;
}
//============
// �I������
//============
void CShadowS::Uninit(void)
{
	CObjectX::Uninit();
}
//============
// �X�V����
//============
void CShadowS::Update(void)
{
	CObjectX::Set(m_pos, m_rot);
}
//============
// �`�揈��
//============
void CShadowS::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	//�X�e���V���e�X�g��L����
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	//Z�o�b�t�@�ւ̏������ݖ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	
	//�J���[�o�b�t�@�ւ̏������ݖ���
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);
	//�X�e���V���o�b�t�@�̔�r�p�����[�^�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCRSAT);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

	//�\�ʃJ�����O
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//�e���f���`��
	CObjectX::Draw();

	//�X�e���V���o�b�t�@�̎Q�ƒl�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	//�X�e���V���o�b�t�@�̔�r�p�����[�^�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

	//���ʃJ�����O
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	//�e���f���`��
	CObjectX::Draw();

	//�J���[�o�b�t�@�ւ̏������ݗL��
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000F); // �J���[�`��ON
	//�X�e���V���o�b�t�@�̎Q�ƒl�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x02);
	//�X�e���V���o�b�t�@�̔�r�p�����[�^�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

	//���|���S���`��
	m_pObj2D->Draw();

	//�S�Č��ɖ߂�

	//Z�o�b�t�@�ւ̏������ݗL��
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//�X�e���V���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}