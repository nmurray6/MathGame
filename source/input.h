#if !defined(_INPUT_H)
#define _INPUT_H

#include "s3ePointer.h"


class Input {
public:
	int m_X, m_Y;
	bool touched;
	bool prevTouched;

public:
	Input();
	void Update();
	void Reset();

	static void TouchButtonCB(s3ePointerEvent* event);
	static void TouchMotionCB(s3ePointerMotionEvent* event);
	static void MultiTouchButtonCB(s3ePointerTouchEvent* event);
	static void MultiTouchMotionCB(s3ePointerMotionEvent* event);

};

extern Input* g_pInput;

#endif