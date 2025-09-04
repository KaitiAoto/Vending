//============================================
//
// �e���J�E���^�[[bullet_counter.cpp]
// Author : Kaiti Aoto
//
//============================================

// �C���N���[�h
#include "bullet_counter.h"
#include "renderer.h"
#include "manager.h"
#include "timer_manager.h"

//==================
// �R���X�g���N�^
//==================
CBullerCounter::CBullerCounter(int nPriority) :CObject(nPriority)
{
	// �l���N���A
	m_pNumber = nullptr;
}
//================
// �f�X�g���N�^
//================
CBullerCounter::~CBullerCounter()
{
}
//===========
// ��������
//===========
CBullerCounter* CBullerCounter::Create(D3DXVECTOR3 pos)
{
	// ����
	CBullerCounter* pBullerCounter = new CBullerCounter;
	// ������
	if (FAILED(pBullerCounter->Init(pos, BULLET_COUNT_SIZE, BULLET_COUNT_SIZE)))
	{// NULL�`�F�b�N
		delete pBullerCounter;
		return nullptr;
	}

	return pBullerCounter;	// �|�C���^��Ԃ�
}
//===============
// ����������
//===============
HRESULT CBullerCounter::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �����̏�����
	m_pNumber = CNumber::Create("data\\TEXTURE\\number002.png", pos, fWidth, fHeight);

	// �I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_BULLETCNT);

	return S_OK;
}
//============
// �I������
//============
void CBullerCounter::Uninit(void)
{
	if (m_pNumber != nullptr)
	{// NULL�`�F�b�N
		// �����̏I���������j��
		m_pNumber->Uninit();
		delete m_pNumber;
		m_pNumber = nullptr;
	}

	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}
//============
// �X�V����
//============
void CBullerCounter::Update(void)
{
}
//============
// �`�揈��
//============
void CBullerCounter::Draw(void)
{
	if (m_pNumber != nullptr)
	{// NULL�`�F�b�N
		// �����̕`��
		m_pNumber->Draw();
	}
}