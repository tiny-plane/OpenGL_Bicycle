#include "var.h"
#include <iostream>
using namespace std;

var::var(void)
{
	//cout << "Object is being created" << endl;

}
void var::ChangeColor(float red, float green, float blue)
{
	this->color_changed = true;
	this->red = red;
	this->green = green;
	this->blue = blue;
}
