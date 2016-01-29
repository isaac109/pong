#pragma once

// basic information to be held by each paddle
class Paddle
{
public:
	Paddle();
	Paddle(int height,int width, int posH, int posW, float r, float g, float b);
	int _height;
	int _width;
	int _posH;
	int _posW;
	float _r;
	float _g;
	float _b;

};