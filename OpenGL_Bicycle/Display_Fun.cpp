#include <gl/glut.h>
#include "Display_Fun.h"

void drawSnowMan() {
	glColor3f(1.0f, 1.0f, 1.0f);
	//画身体
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);
	// 画头
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);	
	// 画眼睛
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();
	// 画鼻子
	glColor3f(1.0f, 0.5f, 0.5f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
	/*	
	glPushMatrix(); //后踏板
	glTranslatef(20.0, -35.0, 0.0);
	glRotatef(spin, 0.0, 0.0, 1.0);
	glCallList(Frame2);
	glPopMatrix();

	glPushMatrix();//前轮
	glTranslatef(-20.0, -35.0, 0.0);
	glRotatef(spin, 0.0, 0.0, 1.0);
	glCallList(Wheel1);
	glPopMatrix();
	
	glPushMatrix(); //后轮
	glTranslatef(64.0, -35.0, 0.0);
	glRotatef(spin, 0.0, 0.0, 1.0);
	glCallList(Wheel2);
	glPopMatrix();

	glPushMatrix(); //中间齿轮
	glTranslatef(18.0, -35.0, 0.0);
	glRotatef(spin, 0.0, 0.0, 1.0);
	glCallList(Wheel3);
	glPopMatrix();
	
	glPushMatrix(); //前踏板
	glTranslatef(20.0, -35.0, 0.0);
	glRotatef(spin, 0.0, 0.0, 1.0);
	glCallList(Frame1);
	glPopMatrix();

	//支架显示列表  不动
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, 0.0);
	glCallList(Frame);
	*/
}
void Display_Fun()
{
	drawSnowMan();
}