//==============================
//
// ï‚è[èàóù[restock.h]
// Author:kaiti
//
//==============================
#ifndef _BUFF_H_
#define _BUFF_H_


class CBuff
{
public:
	enum TYPE
	{
		TYPE_NONE,
		TYPE_SPEED,
		TYPE_MAX
	};

	CBuff();
	~CBuff();
	void Update(float deltaTime);

	void AddSpeed(float fSpeed, float fDuration);

	TYPE GetType(void) { return m_type; }
private:

	float m_fSpeed;
	float m_fDuration;
	bool m_bActive;
	TYPE m_type;
};

#endif