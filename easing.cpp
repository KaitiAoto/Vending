//==============================
//
//  �C�[�W���O����[easing.cpp]
//  Author:kaiti
//
//==============================
#include "easing.h"

//==================
// �f�X�g���N�^
//==================
CEasing::~CEasing()
{
}
//==================
// �A�E�g�o�E���X
//==================
float CEasing::OutBounce(float t)
{
    const float n1 = 7.5625f;
    const float d1 = 2.75f;

    if (t < 1.0f / d1) {
        return n1 * t * t;
    }
    else if (t < 2.0f / d1) {
        return n1 * (t -= 1.5f / d1) * t + 0.75f;
    }
    else if (t < 2.5f / d1) {
        return n1 * (t -= 2.25f / d1) * t + 0.9375f;
    }
    else {
        return n1 * (t -= 2.625f / d1) * t + 0.984375f;
    }
}
