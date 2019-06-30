#include "Menu_class.h"
#include "var.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


void createGLUTMenus(var& v)
{
	int menu_rotate, menu_color;
	// 创建菜单并告诉GLUT，processMenuEvents处理菜单事件。
	void (*ptr)(int) = &processMenuEvents_rotate;
	void(*ptr2)(int) = &processMenuEvents_color;
	menu_rotate = glutCreateMenu(ptr);
	//给菜单增加条目
	
	glutAddMenuEntry("Stop", 0);
	glutAddMenuEntry("Slowly", 1);
	glutAddMenuEntry("Middle speed", 2);
	glutAddMenuEntry("Faster", 3);
	glutAddMenuEntry("Crazy!!", 4);
	//glutAddSubMenu("Auto Rotate", menu_rotate);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	// 把菜单和鼠标右键关联起来。

	menu_color = glutCreateMenu(ptr2);
	glutAddMenuEntry("Black", -1);
	glutAddMenuEntry("White", 0);
	glutAddMenuEntry("Blue", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Red", 3);
	glutAddMenuEntry("Random", 99);
	//glutAddSubMenu("Backgroud Color", menu_color);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	cout << "done with menu build" << endl;
}
void processMenuEvents_rotate(int option)
{
	
	//option，就是传递过来的value的值。
	//cout << option << endl;
	/*
	switch (option)
	{
	case 0:
		v.rotate_speed = 0.0f;
		break;
	case 1:
		v.rotate_speed = 0.1f;
		break;
	case 2:
		v.rotate_speed = 0.5f;
		break;
	case 3:
		v.rotate_speed = 1.0f;
		break;
	case 4:
		v.rotate_speed = 5.0f;
		break;
	}
	*/
}
void processMenuEvents_color(int option)
{
	//cout << option << endl;
	/*
	switch (option)
	{
	case -1:
		v.ChangeColor(0.0f, 0.0f, 0.0f);
		break;
	case 0:
		v.ChangeColor(1.0f, 1.0f, 1.0f);
		break;
	case 1:
		v.ChangeColor(0.0f, 0.0f, 1.0f);
		break;
	case 2:
		v.ChangeColor(0.0f, 1.0f, 0.0f);
		break;
	case 3:
		v.ChangeColor(1.0f, 0.0f, 0.0f);
		break;
	case 99:
		srand((unsigned)time(NULL));
		v.ChangeColor(0.1f * float(rand() % 11), 0.1f * float(rand() % 11), 0.1f * float(rand() % 11));
		break;
	}
	*/
}