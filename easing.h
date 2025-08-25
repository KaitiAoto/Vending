//==============================
//
//  イージング処理[easing.h]
//  Author:kaiti
//
//==============================
#ifndef _EASING_H_
#define _EASING_H_

class CEasing
{
public:
	~CEasing();
	
	static float OutBounce(float fX);
private:
	CEasing() {};
};

#endif