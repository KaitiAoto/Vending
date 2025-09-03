//==============================
//
//  �C�[�W���O����[easing.h]
//  Author : Kaiti Aoto
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _EASING_H_
#define _EASING_H_

// �C�[�W���O�N���X
class CEasing
{
public:
	// �����o�֐�
	~CEasing();
	
	// �ÓI�����o�֐�
	static float OutBounce(float fX);
	static float OutElastic(float fX);
	static float OutExpo(float fX);

private:
	CEasing() {};
};

#endif