#include <gl/glut.h>
#include <stdio.h>
#include "var.h"
#include "base.h"
#pragma once
using namespace std;

class Keybord_Fun : public base
{
public:
	Keybord_Fun(int key, int x, int y, var& v);
	void orientMe(float ang, var& v);
	void moveMeFlat(float direction, var& v);
};