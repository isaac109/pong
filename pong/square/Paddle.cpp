#include "stdafx.h"
#include "Paddle.h"


Paddle::Paddle(){}

Paddle::Paddle(int height,int width, int posH, int posW, float r, float g, float b)
{
	_height = height;
	_width = width;
	_posH = posH;
	_posW = posW;
	_r = r;
	_g = g;
	_b = b;
}