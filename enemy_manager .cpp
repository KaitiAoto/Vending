//=====================================
//
// �G�}�l�[�W���[[enemy_manager.cpp]
// Author:kaiti
//
//=====================================
#include "enemy_manager.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
//�ÓI�����o�ϐ�
CEnemyMana* CEnemyMana::m_pEnemyMane = NULL;
int CEnemyMana::m_nCntEnemy = 0;
//==================
// �R���X�g���N�^
//==================
CEnemyMana::CEnemyMana()
{
	m_nCntSpan = 0;
}
//================
// �f�X�g���N�^
//================
CEnemyMana::~CEnemyMana()
{
}
//===========
// ��������
//===========
CEnemyMana* CEnemyMana::Create()
{
	////�G
	//CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 150.0f, SCREEN_HEIGHT / 5, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::TYPE_A);
	//CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::TYPE_B);
	//CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 150.0f, SCREEN_HEIGHT / 5, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::TYPE_C);

	return m_pEnemyMane;
}
//===============
// ����������
//===============
HRESULT CEnemyMana::Init(void)
{
	//������
	//m_nCntSpan = ENEMY_SPAN;

	return S_OK;
}
//============
// �I������
//============
void CEnemyMana::Uninit(void)
{

}
//============
// �X�V����
//============
void CEnemyMana::Update(void)
{

	m_nCntSpan--;

	if (m_nCntSpan <= 0)
	{
		//m_nCntSpan = ENEMY_SPAN;

		//CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 150.0f, SCREEN_HEIGHT / 5, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::TYPE_A);
	}
}
//============
// �`�揈��
//============
void CEnemyMana::Draw(void)
{
}
//=============
// �ݒ菈��
//=============
void CEnemyMana::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{

}