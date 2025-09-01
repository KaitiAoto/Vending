//==============================
//
//  イージング処理[easing.h]
//  Author:kaiti
//
//==============================
#ifndef _EASING_H_
#define _EASING_H_

// イージングクラス
class CEasing
{
public:
	// メンバ関数
	~CEasing();
	
	static float OutBounce(float fX);
	static float OutElastic(float fX);
	static float OutExpo(float fX);

private:
	CEasing() {};
};

#endif