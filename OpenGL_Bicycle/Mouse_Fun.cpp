#include "Mouse_Fun.h"

using namespace std;


Mouse_Fun::Mouse_Fun(void)
{}
void Mouse_Fun::processMouse_Clicks(int button, int state, int x, int y, var& v)
//改变视线的距离
{
	if (button == GLUT_WHEEL_UP)
	{
		v.dep += 1.0f;
		return;
	}
	else if (button == GLUT_WHEEL_DOWN)
	{
		v.dep -= 1.0f;
		return;
	}
	if (state == GLUT_DOWN)
	{
		v.specialKey = button;
	}
}
void Mouse_Fun::processMouse_ActiveMotion(int x, int y, var& v)
{
	//实现鼠标按下的旋转
	if (v.specialKey == GLUT_LEFT_BUTTON) {
		//	cout << x << y << endl;
		v.dif_x = (float)x - v.last_x;
		if ((float)x >= v.last_x) {

			if (v.dif_x >= 10)
			{
				v.last_x = (float)x;
			}
			else
			{
				v.last_x = (float)x;
				if (v.dif_x != 0)
				{
					v.angle_x += 0.4f * v.dif_x;
				}
			}
		}
		else
		{
			if (v.dif_x <= -10)
			{
				v.last_x = (float)x;
			}
			else
			{
				v.last_x = (float)x;
				if (v.dif_x != 0)
				{
					v.angle_x += 0.4f * v.dif_x;
				}
			}
		}

		v.dif_y = (float)y - v.last_y;
		if ((float)y > v.last_y)
		{
			if (v.dif_y >= 10)
			{
				v.last_y = (float)y;
			}
			else
			{
				v.last_y = (float)y;
				if (v.dif_y != 0)
				{
					v.angle_y += 0.4f * v.dif_y;
				}
			}
		}
		else
		{
			if (v.dif_y <= -10)
			{
				v.last_y = (float)y;
			}
			else
			{
				v.last_y = (float)y;
				if (v.dif_y != 0)
				{
					v.angle_y += 0.4f * v.dif_y;
				}
			}
		}

	}
}
void Mouse_Fun::processMouse_PassiveMotion(int x, int y, var& v)
{
	if (v.specialKey == GLUT_ACTIVE_SHIFT) {

	}
}
void Mouse_Fun::processMouse_Entry(int state, var& v)
{
	if (state == GLUT_LEFT)
		v.deltaAngle = 0.0;
	else
		v.deltaAngle = 1.0;
}
