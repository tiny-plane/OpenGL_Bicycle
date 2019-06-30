#pragma once
#include <gl/glut.h>
#include "var.h"
#include <iostream>
#include "base.h"

using namespace std;
#define  GLUT_WHEEL_UP 3           //¶¨Òå¹öÂÖ²Ù×÷
#define  GLUT_WHEEL_DOWN 4

class Mouse_Fun : public base
{
public:
	Mouse_Fun(void);
	void processMouse_Clicks(int button, int state, int x, int y, var& v);
	void processMouse_ActiveMotion(int x, int y, var& v);
	void processMouse_PassiveMotion(int x, int y, var& v);
	void processMouse_Entry(int state, var& v);
};