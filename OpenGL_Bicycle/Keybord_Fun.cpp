#include <windows.h>
#include <gl/glut.h>
#include <stdio.h>
#include "var.h"
#include "Keybord_Fun.h"
#include <iostream>
#include <math.h>
using namespace std;

Keybord_Fun::Keybord_Fun(int key, int x, int y, var& v)
{
	//用键盘控制视线距离
	//cout << "1" << endl;
	switch (key) {
	case GLUT_KEY_LEFT:
		v.dep += 1.0f;
		//gluPerspective(v.dep, v.ratio, 0, 20); //设置可视空间
		break;
	case GLUT_KEY_RIGHT:
		v.dep -= 1.0f;
		//gluPerspective(v.dep, v.ratio, 0, 20); //设置可视空间
		break;
	case GLUT_KEY_F5:
		v.last_x = (float)x;
		v.last_y = (float)y;
		break;

	}
}
void Keybord_Fun::orientMe(float ang, var& v)
{
	v.lx = sin(ang);
	v.lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(v.x, v.y, v.z, v.x + v.lx, v.y + v.ly, v.z + v.lz, 0.0f, 1.0f, 0.0f);
}
void Keybord_Fun::moveMeFlat(float direction, var& v)
{
	v.x = v.x + direction*(v.lx) * 0.1f;
	v.z = v.z + direction*(v.lz) * 0.1f;
	glLoadIdentity();
	gluLookAt(v.x, v.y, v.z, v.x + v.lx, v.y + v.ly, v.z + v.lz, 0.0f, 1.0f, 0.0f);
}
