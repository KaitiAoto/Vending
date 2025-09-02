//==============================
//
// �o�t[buff.h]
// Author:kaiti
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _BUFF_H_
#define _BUFF_H_

// �o�t�N���X
class CBuff
{
public:
	// ���
	enum TYPE
	{
		TYPE_NONE,
		TYPE_SPEED,
		TYPE_MAX
	};

	// �����o�֐�
	CBuff();
	~CBuff();

	void Update(float deltaTime);
	void AddSpeed(float fSpeed, float fDuration);

	// �擾
	TYPE GetType(void) { return m_type; }
private:
	//�����o�ϐ�
	float m_fSpeed;		// �X�s�[�h
	float m_fDuration;	// ���ʎ���
	bool m_bActive;		// �o�t���������Ă��邩
	TYPE m_type;		// ���
};

#endif