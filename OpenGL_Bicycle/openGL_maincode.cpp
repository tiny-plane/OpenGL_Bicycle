#include <windows.h>
#include <gl/glew.h>  
#include <gl/freeglut.h>
#include <stdio.h>
#include "Keybord_Fun.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Display_Fun.h"
#include "Mouse_Fun.h"
#include "openGL_maincode.h"
#include <time.h>

using namespace std;


int power_of_two(int n)
{
	// 用于判断一个整数是不是2的整数次幂
	if (n <= 0)
		return 0;
	return (n & (n - 1)) == 0;
}
void spinDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除深度缓冲区
	glPushMatrix(); //保存当前模型视图矩阵
	glRotatef(angle, 0.0, 1.0, 0.0);
	glColor3f(v.red, v.green, v.blue);
	//glColor3f(red, green, blue);
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(0.0, 0.5, 0.0);
	glEnd();
	glPopMatrix(); // 弹出堆栈
	glutSwapBuffers();  // 交换缓冲区
	angle += v.deltaAngle;
}
void processNormalKeys(unsigned char key, int x, int y)
{
	//cout << int(key) << endl;
	//cout << x << endl;
	if (key == 27)
		exit(0);
}
void processSpecialKeys(int key, int x, int y)
{
	Keybord_Fun(key, x, y, v);
}
void processMouse(int button, int state, int x, int y)
{
	M.processMouse_Clicks(button, state, x, y, v);
}
void processMouseActiveMotion(int x, int y)
{
	M.processMouse_ActiveMotion(x, y, v);
}
void processMousePassiveMotion(int x, int y)
{
	M.processMouse_PassiveMotion(x, y, v);
}
void processMouseEntry(int state)
{
	M.processMouse_Entry(state, v);
}
void ChangeSize(int w, int h)
{
	if (h == 0) h = 1;
	v.ratio = (float)w / (float)h;
	glViewport(0, 0, w, h);
}
void createGLUTMenus(var& v)
{
	int menu_rotate, menu_color, menu_drawkind, menu_speed, menu,menu_set;
	// 创建菜单并告诉GLUT，processMenuEvents处理菜单事件。
	void(*ptr)(int) = &processMenuEvents_rotate;
	void(*ptr2)(int) = &processMenuEvents_color;
	void(*ptr3)(int) = &processMenuEvents_drawkind;
	void(*ptr4)(int) = &processMenuEvents_void;
	void(*ptr5)(int) = &processMenuEvents_speed;
	void(*ptr6)(int) = &processMenuEvents_set;

	menu_color = glutCreateMenu(ptr2);
	glutAddMenuEntry("Black", -1);
	glutAddMenuEntry("White", 0);
	glutAddMenuEntry("Blue", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Red", 3);
	glutAddMenuEntry("Random", 99);
	glutAddMenuEntry("Auto Random", 100);

	menu_rotate = glutCreateMenu(ptr);
	glutAddMenuEntry("Stop", 0);
	glutAddMenuEntry("Slowly", 1);
	glutAddMenuEntry("Middle speed", 2);
	glutAddMenuEntry("Faster", 3);
	glutAddMenuEntry("Crazy!!", 4);

	menu_drawkind = glutCreateMenu(ptr3);
	glutAddMenuEntry("Fill", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Point", 3);

	menu_speed = glutCreateMenu(ptr5);
	glutAddMenuEntry("Stop", 0);
	glutAddMenuEntry("Slowly", 1);
	glutAddMenuEntry("Middle speed", 2);
	glutAddMenuEntry("Faster", 3);
	glutAddMenuEntry("Crazy!!", 4);

	menu_set = glutCreateMenu(ptr6);
	glutAddMenuEntry("Enable depth test", 1);
	glutAddMenuEntry("Disable depth test", 2);
	glutAddMenuEntry("Enable smooth", 3);
	glutAddMenuEntry("Disable smooth", 4);

	menu = glutCreateMenu(ptr4);
	glutAddSubMenu("Velocity", menu_speed);
	glutAddSubMenu("Backgroud Color", menu_color);
	glutAddSubMenu("Auto Rotate", menu_rotate);
	glutAddSubMenu("Rendering mode", menu_drawkind);
	glutAddSubMenu("Other setting", menu_set);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	//cout << "done with menu build" << endl;
}
void processMenuEvents_rotate(int option)
{

	//option，就是传递过来的value的值。
	//cout << option << endl;
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
}
void processMenuEvents_color(int option)
{
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
	case 100:
		v.auto_changecolor = true;
		break;
	}
}
void processMenuEvents_drawkind(int option)
{
	switch (option)
	{
	case 1:
		v.mode = 1;
		break;
	case 2:
		v.mode = 2;
		break;
	case 3:
		v.mode = 3;
		break;
	}
}
void processMenuEvents_void(int option)
{
	return;
}
void processMenuEvents_speed(int option)
{
	switch (option)
	{
	case 0:
		v.speed = 0.0f;
		break;
	case 1:
		v.speed = 0.3f;
		break;
	case 2:
		v.speed = 1.0f;
		break;
	case 3:
		v.speed = 2.0f;
		break;
	case 4:
		v.speed = 5.0f;
		break;
	}
	//cout << v.speed << endl;
}
void processMenuEvents_set(int option)
{
	switch (option)
	{
	case 1:
		v.enable_DEPTH = true;
		break;
	case 2:
		v.enable_DEPTH = false;
		break;
	case 3:
		v.enable_SMOOTH = true;
		break;
	case 4:
		v.enable_SMOOTH = false;
		break;
	}
}
void Circle()
{
	glBegin(GL_TRIANGLE_FAN);//扇形连续填充三角形串  
	glVertex3f(0.0f, 0.0f, 0.0f);
	int i = 0;
	for (i = 0; i <= 390; i += 15)
	{
		float p = i * 3.14f / 180.0f;
		glVertex3f(sin(p), cos(p), 0.0f);
	}
	glEnd();
}
void centreline(float length, float xo, float yo, float zo, bool xd, bool yd, bool zd)
{
	if (xd)
	{
		glBegin(GL_LINES);
		glVertex3f(length + xo, yo, zo);
		glVertex3f(-length + xo, yo, zo);
		glEnd();
	}
	if (yd)
	{
		glBegin(GL_LINES);
		glVertex3f(xo, length + yo, zo);
		glVertex3f(xo, -length + yo, zo);
		glEnd();
	}
	if (zd)
	{
		glBegin(GL_LINES);
		glVertex3f(xo, yo, length + zo);
		glVertex3f(xo, yo, -length + zo);
		glEnd();
	}
}
void cyLinder(float x0, float y0, float z0, float x1, float y1, float z1, double radius, GLuint tex, GLint slices, GLint stack)
{   //如果要在AB两点间画一个圆柱体，其可以
	//先在y轴上画一个同长度的圆柱，然后
	 //求出旋转矩阵，将其移至AB
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	GLdouble dir_x = x1 - x0,
		dir_y = y1 - y0,
		dir_z = z1 - z0;
	GLdouble cy_length = sqrt(dir_x*dir_x + dir_y*dir_y + dir_z*dir_z);    //获得圆柱的长度
	static GLUquadricObj* quad_obj = NULL;
	if (quad_obj == NULL)
		quad_obj = gluNewQuadric();
	gluQuadricDrawStyle(quad_obj, GLU_FILL);
	gluQuadricNormals(quad_obj, GLU_SMOOTH);
	glPushMatrix();             //将当前矩阵压入矩阵堆栈
	glTranslated(x0, y0, z0);  //平移到起点，即A点												 
	double length;//获得AB的长度
	length = sqrt(dir_x*dir_x + dir_y*dir_y + dir_z*dir_z);
	dir_x /= length; dir_y /= length; dir_z /= length;
	GLdouble up_x = 0.0,
		up_y = 1.0,
		up_z = 0.0;
	GLdouble side_x, side_y, side_z;
	//实现向量的叉乘
	side_x = up_y*dir_z - up_z*dir_y;
	side_y = up_z*dir_x - up_x*dir_z;
	side_z = up_x*dir_y - up_y*dir_x;
	length = sqrt(dir_x*dir_x + dir_y*dir_y + dir_z*dir_z);
	side_x /= length; side_y /= length; side_z /= length;
	up_x = dir_y*side_z - dir_z*side_y;
	up_y = dir_z*side_x - dir_x*side_z;
	up_z = dir_x*side_y - dir_y*side_x;
	//得到变换矩阵
	GLdouble m[] = { side_x,side_y,side_z,0.0,
		up_x,up_y,up_z,0.0,
		dir_x,dir_y,dir_z,0.0,
		0.0,0.0,0.0,1.0 };
	glMultMatrixd(m);                //用m矩阵乘以当前矩阵
	gluCylinder(quad_obj, radius, radius, cy_length, slices, stack);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void cyLinder(float x0, float y0, float z0, float x1, float y1, float z1, double radius)
{   //如果要在AB两点间画一个圆柱体，其可以
	//先在y轴上画一个同长度的圆柱，然后
	//求出旋转矩阵，将其移至AB
	GLdouble dir_x = x1 - x0,
		dir_y = y1 - y0,
		dir_z = z1 - z0;
	GLdouble cy_length = sqrt(dir_x*dir_x + dir_y*dir_y + dir_z*dir_z);    //获得圆柱的长度
	static GLUquadricObj* quad_obj = NULL;
	if (quad_obj == NULL)
		quad_obj = gluNewQuadric();
	gluQuadricDrawStyle(quad_obj, GLU_FILL);
	gluQuadricNormals(quad_obj, GLU_SMOOTH);
	glPushMatrix();             //将当前矩阵压入矩阵堆栈
	glTranslated(x0, y0, z0);  //平移到起点，即A点												 
	double length;//获得AB的长度
	length = sqrt(dir_x*dir_x + dir_y*dir_y + dir_z*dir_z);
	dir_x /= length; dir_y /= length; dir_z /= length;
	GLdouble up_x = 0.0,
		up_y = 1.0,
		up_z = 0.0;
	GLdouble side_x, side_y, side_z;
	//实现向量的叉乘
	side_x = up_y*dir_z - up_z*dir_y;
	side_y = up_z*dir_x - up_x*dir_z;
	side_z = up_x*dir_y - up_y*dir_x;
	length = sqrt(dir_x*dir_x + dir_y*dir_y + dir_z*dir_z);
	side_x /= length; side_y /= length; side_z /= length;
	up_x = dir_y*side_z - dir_z*side_y;
	up_y = dir_z*side_x - dir_x*side_z;
	up_z = dir_x*side_y - dir_y*side_x;
	//得到变换矩阵
	GLdouble m[] = { side_x,side_y,side_z,0.0,
		up_x,up_y,up_z,0.0,
		dir_x,dir_y,dir_z,0.0,
		0.0,0.0,0.0,1.0 };
	glMultMatrixd(m);                //用m矩阵乘以当前矩阵
	GLint slices = 5;
	GLint stack = 1;
	gluCylinder(quad_obj, radius, radius, cy_length, slices, stack);
	glPopMatrix();
}
void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glClearColor(v.red, v.green, v.blue, 0.0f);
	glRotatef(angle + v.angle_x, 0.0f, 1.0f, 0.0f);
	glRotatef(v.angle_y, 1.0f, 0.0f, 0.0f);
	centreline(100.0f, 0.0f, 0.0f, 0.0f, true, true, true);
	//地面
	glBindTexture(GL_TEXTURE_2D, texGround);
	if (v.dis_road <= -200.0f)
	{
		v.dis_road = 0.0f;
	}
	for (int i = -2; i <= 2; i++)
	{
		for (int j = -5; j <= 5; j++)
		{
			glEnable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-100.0f + v.dis_road + 200.0f*(float)j, -35.5f, 100.0f + 200.0f*(float)i);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(100.0f + v.dis_road + 200.0f*(float)j, -35.5f, 100.0f + 200.0f*(float)i);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(100.0f + v.dis_road + 200.0f*(float)j, -35.5f, -100.0f + 200.0f*(float)i);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-100.0f + v.dis_road + 200.0f*(float)j, -35.5f, -100.0f + 200.0f*(float)i);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
	}
	//车架	
	//glColor3f(1.0f, 1.0f, 1.0f);
	cyLinder(17.5f, 46.3f, v.zall, 30.3f, 4.5f, v.zall, 5.0); //qianjia
	cyLinder(30.3f, 4.5f, v.zall, 38.36f, -7.38f, v.zall, 2.0); //qianjia2
	cyLinder(20.7f, 35.9f, v.zall, -30.2f, 29.6f, v.zall, 3.0); //zhongshang
	cyLinder(-30.2f, 29.6f, v.zall, -19.0f, -13.1f, v.zall, 8.0); //zhongshu
	cyLinder(-19.0f, -13.1f, v.zall, 20.7f, 35.9f, v.zall, 3.0); //zuoshang
	cyLinder(-30.2f, 29.6f, v.zall, -56.3f, -6.8f, v.zall, 5.0); //youxia
	cyLinder(-56.3f, -6.8f, v.zall, -19.0f, -13.1f, v.zall, 3.0); //zuoxia
	cyLinder(-30.2f, 29.6f, v.zall, -36.3f, 49.3f, v.zall, 3.0); //chejiaxia
	cyLinder(17.5f, 46.3f, v.zall, 26.4f, 48.0f, v.zall, 2.0); //bashouqiangan
	cyLinder(26.4f, 48.0f, v.zall - 20.0f, 26.4f, 48.0f, v.zall, 2.0); //bashouganzuo
	cyLinder(26.4f, 48.0f, v.zall + 20.0f, 26.4f, 48.0f, v.zall, 2.0); //bashouganyou
	cyLinder(26.4f, 48.0f,  v.zall - 20.0f, 48.3f, 49.5f, v.zall - 20.0f, 2.0); //bashouzuowo
	cyLinder(26.4f, 48.0f, v.zall + 20.0f, 48.3f, 49.5f, v.zall + 20.0f, 2.0); //bashouyouwo
	cyLinder(39.3f, 35.5f, v.zall - 20.0f, 48.3f, 49.5f, v.zall - 20.0f, 2.0); //bashouzuoxiabashou
	cyLinder(39.3f, 35.5f, v.zall + 20.0f, 48.3f, 49.5f, v.zall + 20.0f, 2.0); //bashouyouxiabashou
	//车座
	glPushMatrix();
	glTranslatef(-30.0f, 50.0f, v.zall);
	glRotated(90.0f, 1.0, 0.0, 0.0);
	gluBeginSurface(theNurb); // 开始曲面绘制 
	gluNurbsSurface(theNurb, 8, knots, 8, knots, 4 * 3, 3, &ctrlpoints[0][0][0], 4, 4, GL_MAP2_VERTEX_3);
	// 定义曲面的数学模型，确定其形状  
	gluEndSurface(theNurb); // 结束曲面绘制  
	glPopMatrix();
	//前轮
	//glColor3f(1.0f,0.0f,0.0f);
	glPushMatrix();
	glTranslatef(-56.3f, -6.8f, v.zall);
	glutSolidTorus(3, 28, 10, 20);
	glPopMatrix();
	//后轮
	glPushMatrix();
	glTranslatef(38.36f, -7.38f, v.zall);
	glutSolidTorus(3, 28, 10, 20);
	glPopMatrix();
	
	//前轮辐条
	glPushMatrix();
	glTranslatef(-56.3f, -6.8f, v.zall);
	glBegin(GL_LINES);
	float i = 0;
	for (i = v.angr; i < v.angr + 360; i += 18)
	{
		glVertex3f(28.0f * sinf(i), 28.0f * cos(i), 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
	}
	glEnd();
	glPopMatrix();
	//后轮辐条
	glPushMatrix();
	glTranslatef(38.36f, -7.38f, v.zall);
	glBegin(GL_LINES);

	for (i = v.angr; i < v.angr + 360; i += 18)
	{
		glVertex3f(28.0f * sinf(i), 28.0f * cos(i), 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
	}
	glEnd();
	glPopMatrix();
	//斑马线
	float len = 30.0f;
	float dis = 20.0f;
	if (v.dis < -len - dis)
	{
		v.dis = 0.0f;
	}
	for (i = 1; i <= 20; i++)
	{
		glBegin(GL_POLYGON);
		glVertex3f(-500.0f + v.dis + (float)i * (dis + len), -35.0f, -3.0f);
		glVertex3f(-500.0f + v.dis + (float)i * (dis + len), -35.0f, 3.0f);
		glVertex3f(-500.0f + v.dis + (float)i * (dis + len) + len, -35.0f, 3.0f);
		glVertex3f(-500.0f + v.dis + (float)i * (dis + len) + len, -35.0f, -3.0f);
		glEnd();
	}
	//牙盘
	glPushMatrix();
	glTranslatef(-19.0f, -13.1f, v.zall + 3.0f);
	glutSolidTorus(1, 10, 10, 8);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-56.3f, -6.8f, v.zall + 3.0f);
	glutSolidTorus(1, 5, 10, 6);
	glPopMatrix();
	//脚踏板
	cyLinder(-19.0f, -13.1f, v.zall + 5.0f, -19.0f, -13.1f, v.zall - 5.0f, 2.0); //zhou
	cyLinder(-19.0f, -13.1f, v.zall + 5.0f, -19.0f + cosf(-v.angr * 0.02f)* 17.6f,
		-13.1f + sinf(-v.angr * 0.02f)* 17.6f, v.zall + 5.0f, 2.0); //zhou
	cyLinder(-19.0f, -13.1f, v.zall - 5.0f, -19.0f - cosf(-v.angr * 0.02f)* 17.6f,
		-13.1f - sinf(-v.angr * 0.02f)* 17.6f, v.zall - 5.0f, 2.0); //zhou
	//链条
	glBegin(GL_LINES);
	glVertex3f(-19.0f, -3.1f, v.zall + 3.0f);
	glVertex3f(-56.3f, -1.8f, v.zall + 3.0f);
	glVertex3f(-19.0f, -23.1f, v.zall + 3.0f);
	glVertex3f(-56.3f, -11.8f, v.zall + 3.0f);
	glEnd();
	//树

	len = 150.0f;
	dis = 100.0f;
	float z1 = -150.0f;
	if (v.dis_tree < -len - dis)
	{
		v.dis_tree = 0.0f;
	}
	int j = 1;
	for (j = 1; j <= 8; j++)
	{
		cyLinder(-1000.0f + v.dis_tree + (float)j * (dis + len), -35.0f,
			z1, -1000.0f + v.dis_tree + 1.0f + (float)j * (dis + len), 81.0f, z1, 500.0f, texWood, 4, 1); //shugan
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texTree1);
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1000.0f + v.dis_tree + (float)j * (dis + len), 150.0f, z1);
		int num = 8;
		/*for (i = 1; i <= num; i++)
		{

			glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
				sinf(360.0f / (float)num * (float)i), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i) + z1);
		}*/
		i = 1;
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
			sinf(360.0f / (float)num * (float)i / 57.3f), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i / 57.3f) + z1);
		i = 2;
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
			sinf(360.0f / (float)num * (float)i / 57.3f), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i / 57.3f) + z1);
		i = 3;
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
			sinf(360.0f / (float)num * (float)i / 57.3f), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i / 57.3f) + z1);
		i = 4;
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
			sinf(360.0f / (float)num * (float)i / 57.3f), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i / 57.3f) + z1);
		i = 5;
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
			sinf(360.0f / (float)num * (float)i / 57.3f), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i / 57.3f) + z1);
		i = 6;
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
			sinf(360.0f / (float)num * (float)i / 57.3f), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i / 57.3f) + z1);
		i = 7;
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
			sinf(360.0f / (float)num * (float)i / 57.3f), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i / 57.3f) + z1);
		i = 8;
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
			sinf(360.0f / (float)num * (float)i / 57.3f), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i / 57.3f) + z1);
		i = 1;
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
			sinf(360.0f / (float)num * (float)i / 57.3f), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i / 57.3f) + z1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	z1 = -z1;

	for (j = 1; j <= 8; j++)
	{
		cyLinder(-1000.0f + v.dis_tree + (float)j * (dis + len), -35.0f, z1, -1000.0f
			+ v.dis_tree + 1.0f + (float)j * (dis + len), 81.0f, z1, 500.0f, texWood, 4, 1); //shugan
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texTree1);
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1000.0f + v.dis_tree + (float)j * (dis + len), 150.0f, z1);
		int num = 8;
		/*	for (i = 1; i <= num; i++)
			{
				glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
					sinf(360.0f / (float)num * (float)i), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i) + z1);
			}*/
		i = 1;
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
			sinf(360.0f / (float)num * (float)i / 57.3f), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i / 57.3f) + z1);
		i = 2;
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
			sinf(360.0f / (float)num * (float)i / 57.3f), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i / 57.3f) + z1);
		i = 3;
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
			sinf(360.0f / (float)num * (float)i / 57.3f), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i / 57.3f) + z1);
		i = 4;
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
			sinf(360.0f / (float)num * (float)i / 57.3f), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i / 57.3f) + z1);
		i = 5;
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
			sinf(360.0f / (float)num * (float)i / 57.3f), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i / 57.3f) + z1);
		i = 6;
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
			sinf(360.0f / (float)num * (float)i / 57.3f), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i / 57.3f) + z1);
		i = 7;
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
			sinf(360.0f / (float)num * (float)i / 57.3f), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i / 57.3f) + z1);
		i = 8;
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
			sinf(360.0f / (float)num * (float)i / 57.3f), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i / 57.3f) + z1);
		i = 1;
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1000.0f + (float)j * (dis + len) + v.dis_tree + 40.0f *
			sinf(360.0f / (float)num * (float)i / 57.3f), 50.0f, 40.0f * cosf(360.0f / (float)num * (float)i / 57.3f) + z1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	glDisable(GL_TEXTURE_2D);
}
void Display(void)
{
	renderScene();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(v.dep, v.ratio, 0, 20); //设置可视空间
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x11, y11, z11, x22, y22, z22, 0.0f, 1.0f, 0.0f);
	glutSwapBuffers();
}
void idleDisplay(void)
{
		switch (v.mode)
	{
	case 1:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 2:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 3:
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	}
	if (v.auto_changecolor)
	{
		srand((unsigned)time(NULL));
		v.ChangeColor(0.1f * float(rand() % 11), 0.1f * float(rand() % 11), 0.1f * float(rand() % 11));
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(v.dep, v.ratio, 0, 20); //设置可视空间	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x11, y11, z11, x22, y22, z22, 0.0f, 1.0f, 0.0f);

	renderScene();
	glDepthFunc(GL_LEQUAL);

	if (v.enable_DEPTH)
	{
		glEnable(GL_DEPTH_TEST);
			}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (v.enable_SMOOTH)
	{
		glEnable(GL_LINE_SMOOTH);  //允许直线反走样
		glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);  // Antialias the lines
		
	}
	else
	{
		glDisable(GL_LINE_SMOOTH);  //允许直线反走样
	}
	glutSwapBuffers();
	angle += v.rotate_speed * v.rotate_speed;
	v.angr += v.speed * 1.5f;
	v.dis -= v.speed * 2.0f;
	v.dis_tree -= v.speed * 2.0f;
	v.dis_road -= v.speed * 2.0f;
}
GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID = 0, texture_ID = 0;

	// 打开文件，如果失败，返回
	FILE* pFile = fopen(file_name, "rb");
	if (pFile == 0)
		return 0;

	// 读取文件中图象的宽度和高度
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// 计算每行像素所占字节数，并根据此数据计算总像素字节数
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// 根据总像素字节数分配内存
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	// 读取像素数据
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 对就旧版本的兼容，如果图象的宽度和高度不是的整数次方，则需要进行缩放
	// 若图像宽高超过了OpenGL规定的最大值，也缩放
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if (!power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max)
		{
			const GLint new_width = 256;
			const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			// 计算每行需要的字节数和总字节数
			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0)
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			// 分配内存
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if (new_pixels == 0)
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			// 进行像素缩放
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	// 分配一个新的纹理编号
	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 绑定新的纹理，载入纹理并设置纹理参数
	// 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
	GLint lastTextureID = last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, lastTextureID);  //恢复之前的纹理绑定
	free(pixels);
	return texture_ID;
}
void Init(void)
{
	//打开自动法矢量开关
	glEnable(GL_AUTO_NORMAL);
	//允许正则化法矢量
	glEnable(GL_NORMALIZE);	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	theNurb = gluNewNurbsRenderer(); // 创建一个NURBS曲面对象  
									 //修改NURBS曲面对象的属性——glu库函数
									 //采样sampling容错torerance
	gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 20.0);
	gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
}
void main(int argc, char* argv[])
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);  //设置格式
	glutInitWindowSize(800, 600);      //窗口大小	
	glutInitWindowPosition(200, 200);  // 初始窗口位置
	glutCreateWindow("自行车");   //创建窗口，命名

	//glEnable(GL_DEPTH_TEST);    //开启深度测试，实现前后遮挡显示
	glutIdleFunc(idleDisplay);   //空闲时调用	                    
	glutDisplayFunc(Display);    //显示的画面
	
	glutReshapeFunc(ChangeSize);    //如果改变窗口大小，运行ChangeSize 
	glutSpecialFunc(processSpecialKeys); //
	glutKeyboardFunc(processNormalKeys); //ESC退出，关闭程序
	glutMouseFunc(processMouse);   // 检测鼠标点击
	glutMotionFunc(processMouseActiveMotion); // 鼠标按下且移动调用
	glutPassiveMotionFunc(processMousePassiveMotion); //鼠标移动且没有按键，每一帧调用
	//glutEntryFunc(processMouseEntry);   //鼠标进出程序
	createGLUTMenus(v);
	v.speed = 1.0f;

	Init();

	texTree1 = load_texture("tree1.bmp"); //加载纹理
	texWood = load_texture("Wood.bmp");
	texGround = load_texture("Ground.bmp");
	glutMainLoop();                   //进入循环
	return;
}