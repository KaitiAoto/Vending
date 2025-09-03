//==================================
//
// �o�t[buff.cpp]
// Author : Kaiti Aoto
//
//==================================

// �C���N���[�h
#include "buff.h"
#include "game.h"
#include "buff_icon.h"

//==================
// �R���X�g���N�^
//==================
CBuff::CBuff()
{
    // �l���N���A
    m_type = TYPE_NONE;
}
//================
// �f�X�g���N�^
//================
CBuff::~CBuff()
{
}
//============
// �X�V����
//============
void CBuff::Update(float deltaTime)
{
    if (m_bActive != true)
    {// �o�t���������Ă��Ȃ����
        return; // ���������I��
    }

    // ���ʎ��Ԃ����炷
    m_fDuration -= deltaTime;
    
    if (m_fDuration <= 0.0f)
    {// ���Ԃ�0�ȉ��Ȃ�
        if (m_type == TYPE_SPEED)
        {// �X�s�[�h�o�t�Ȃ�
            
            CGame::GetPlayer()->AddSpeed(-m_fSpeed);    // ���̑��x�ɖ߂�
            m_bActive = false;                          // �o�t���������Ă��Ȃ���Ԃɂ���
            m_fSpeed = 0.0f;                            // �X�s�[�h��0��
            m_type = TYPE_NONE;                         // ��ނ�������
        }
    }
}
//======================
// �X�s�[�h�A�b�v����
//======================
void CBuff::AddSpeed(float fSpeed, float fDuration)
{
    if (m_bActive && m_type == TYPE_SPEED)
    {// ���łɃX�s�[�h�o�t���������Ă�����
        m_fDuration = fDuration;    // ���Ԃ��ő�ɂ���
        return;                     // ���������I��
    }

    // �l����
    m_fSpeed = fSpeed;
    m_fDuration = fDuration;
    m_type = TYPE_SPEED;    // ��ނ��X�s�[�h�ɂ���
    m_bActive = true;       // �o�t���������Ă����Ԃɂ���

    // �v���C���[�ɑ��x�㏸�𔽉f
    CGame::GetPlayer()->AddSpeed(m_fSpeed);

    // �A�C�R���𐶐�
    CBuffIcon::Create({ BUFF_X / 2, SCREEN_HEIGHT / 2 + 100.0f,0.0f }, BUFF_X, BUFF_Y);

    // ��ʃt���b�V���̐F��ς���
    CGame::GetFlash()->SetColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f));
}