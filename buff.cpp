#include "buff.h"
#include "game.h"
#include "buff_icon.h"

CBuff::CBuff()
{
    m_type = TYPE_NONE;
}

CBuff::~CBuff()
{
}

void CBuff::Update(float deltaTime)
{
    if (!m_bActive) return;

    m_fDuration -= deltaTime;
    if (m_fDuration <= 0.0f)
    {
        if (m_type == TYPE_SPEED)
        {
            // 元の速度に戻す
            CGame::GetPlayer()->AddSpeed(-m_fSpeed);
            m_bActive = false;
            m_fSpeed = 0.0f;
            m_type = TYPE_NONE;
        }
    }
}

void CBuff::AddSpeed(float fSpeed, float fDuration)
{
    if (m_bActive && m_type == TYPE_SPEED)
    {
        m_fDuration = fDuration;
        return; // 何もせず終了
    }

    m_fSpeed = fSpeed;
    m_fDuration = fDuration;
    m_bActive = true;

    // プレイヤーに速度上昇を反映
    CGame::GetPlayer()->AddSpeed(m_fSpeed);

    m_type = TYPE_SPEED;

    CBuffIcon::Create({ BUFF_X  / 1.5f,SCREEN_HEIGHT / 2 + 100.0f,0.0f }, BUFF_X, BUFF_Y);
}