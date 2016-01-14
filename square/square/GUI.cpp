
#include "stdafx.h"
#include "GUI.h"
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

namespace GUI
{
	GUIData data;
}

const GUI::GUIData& GUI::GetData()
{
	 return data;
}

GUI::GUIData& GUI::MutableData()
{
	 return data;
}

void GUI::GUIData::clearMessage()
{
	for(int i = 0; i < 3; i++)
	{
		message[i] = 'w';
	}
}

void GUI::update()
{
	glutMainLoopEvent();
}

void GUI::special2(char key)
{
	switch(key)
	{
	case 'u':
		data.MoveUp(false);
		break;
	case 'd':
		data.MoveDown(false);
		break;
	}
	
	glutPostRedisplay();
}
void GUI::special(int key, int, int)
{
	if(!data._isStart)
	{
		switch(key)
		{
		case GLUT_KEY_UP:
			data.MoveUp(true);
			data.message[0] = 'u';
			break;
		case GLUT_KEY_DOWN:
			data.MoveDown(true);
			data.message[0] = 'd';
			break;
		}
	}
	glutPostRedisplay();
}

void GUI::moveBall()
{
	Paddle left;
	Paddle right;
	if(data._isP1)
	{
		left = data.myPaddle;
		right = data.theirPaddle;
	}
	else
	{
		left = data.theirPaddle;
		right = data.myPaddle;
	}


	if(data._ballUp)
	{
		data._ballH = data._ballH + data._ballSpeed;
		if(data._ballH >= 585)
		{
			data._ballUp = false;
		}	
	}
	else
	{
		data._ballH = data._ballH - data._ballSpeed;
		if(data._ballH <= 15)
		{
			data._ballUp = true;
		}
	}
	if(data._ballLeft)
	{
		data._ballW = data._ballW - data._ballSpeed;
		if(data._ballW <= 80 && data._ballW > 60 && data._ballH <= left._posH && data._ballH >= left._posH - left._height)
		{
			data._ballLeft = false;
		}
		if(data._ballW <= 15)
		{
			data._scoreP2++;
			data.checkIfWin();
			data._hitP1 = true;
			newBall();
		}
	}
	else
	{
		data._ballW = data._ballW + data._ballSpeed;
		if(data._ballW >= 720 && data._ballW < 740 && data._ballH <= right._posH && data._ballH >= right._posH - right._height)
		{
			data._ballLeft = true;
		}
		if(data._ballW >= 785)
		{
			data._scoreP1++;
			data.checkIfWin();
			data._hitP1 = false;
			newBall();
		}
	}
}

void GUI::GUIData::checkIfWin()
{
	if(_scoreP1 == _winScore || _scoreP2 == _winScore)
	{
		_isWon = true;
	}
}

void GUI::GUIData::drawCircle()
{
	glBegin(GL_POLYGON);
	for(int i = 0; i < _ballSeg; i++)
	{
		float theata = 2.0f * 3.1415928f * float(i) / float(_ballSeg);
		float x = _ballR * cosf(theata);
		float y = _ballR * sinf(theata);
		glVertex2f(x+_ballW, y+_ballH);
	}
	glEnd();
}

void GUI::GUIData::displayScore()
{
	if(data._isP1)
	{
		glColor3f(1.0f,0.0f,0.0f);
	}
	else
	{
		glColor3f(0.0f,0.0f,1.0f);
	}
	glRasterPos2f(300.0f,550.0f);
	string temp = to_string(_scoreP1);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)temp.c_str());

	glColor3f(0.0f,0.0f,0.0f);
	glRasterPos2f(400.0f,550.0f);
	temp = ":";
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)temp.c_str());

	if(data._isP1)
	{
		glColor3f(0.0f,0.0f,1.0f);
	}
	else
	{
		glColor3f(1.0f,0.0f,0.0f);
	}
	glRasterPos2f(500.0f,550.0f);
	temp = to_string(_scoreP2);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)temp.c_str());
}

void GUI::GUIData::displayWin()
{
	if(data._isP1 && data._scoreP1 == 10 || !data._isP1 && data._scoreP2 == 10)
	{
		glColor3f(1.0f,0.0f,0.0f);
	}
	else
	{
		glColor3f(0.0f,0.0f,1.0f);
	}
	if(data._scoreP1 == data._winScore && data._isP1 || data._scoreP2 == data._winScore && !data._isP1)
	{
		glRasterPos2f(300.0f,300.0f);
		string temp = "You Won Pong!";
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)temp.c_str());
	}
	else
	{
		glRasterPos2f(300.0f,300.0f);
		string temp = "You lost pong :(";
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)temp.c_str());
	}

}

void GUI::GUIData::displayCountDown()
{
	if(_time == 0)
	{
		_isStart = false;
	}
	glColor3f(1.0f,0.0f,0.0f);
	glRasterPos2f(300.0f,400.0f);
	string temp = "You are the red paddle!";
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)temp.c_str());

	glColor3f(0.0f,0.0f,0.0f);
	glRasterPos2f(400.0f,300.0f);
	temp = to_string(_time);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)temp.c_str());
	_time --;
	Sleep(1000);
}

void GUI::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(!data._isWon)
	{
		
		glColor3f(data.myPaddle._r,data.myPaddle._g,data.myPaddle._b);
		glBegin(GL_QUADS);
		glVertex2d(data.myPaddle._posW - data.myPaddle._width,data.myPaddle._posH - data.myPaddle._height);
		glVertex2d(data.myPaddle._posW,data.myPaddle._posH - data.myPaddle._height);
		glVertex2d(data.myPaddle._posW,data.myPaddle._posH);
		glVertex2d(data.myPaddle._posW - data.myPaddle._width,data.myPaddle._posH);
		glEnd();

		glColor3f(data.theirPaddle._r,data.theirPaddle._g,data.theirPaddle._b);
		glBegin(GL_QUADS);
		glVertex2d(data.theirPaddle._posW - data.theirPaddle._width,data.theirPaddle._posH - data.theirPaddle._height);
		glVertex2d(data.theirPaddle._posW,data.theirPaddle._posH  - data.theirPaddle._height);
		glVertex2d(data.theirPaddle._posW,data.theirPaddle._posH );
		glVertex2d(data.theirPaddle._posW - data.theirPaddle._width,data.theirPaddle._posH );
		glEnd();
		if(data._isStart)
		{
			data.displayCountDown();
		}
		else
		{
			moveBall();
			glColor3f(0.0f,1.0f,0.0f);
			data.drawCircle();
		}
		data.displayScore();
	}
	else
	{
		data.displayWin();
	}
	glutSwapBuffers();
}



void GUI::changeViewport(int w, int h)
{
	GLfloat width = 800*16/9;
	GLfloat height = 800;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,width,0,height);
	glMatrixMode(GL_MODELVIEW);
}

void GUI::initialize(int argc, char* argv[], bool p1)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Move the Square!");
	glClearColor(1.0f,1.0f,1.0f,1.0f);
	glutReshapeFunc(&GUI::changeViewport);
	glutDisplayFunc(&GUI::render);
	glutSpecialFunc(&GUI::special);


	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW Error");
	}
	data.setP1(p1);
	data._isP1 = p1;
	data.setPaddles();
}

/*void GUI::GUIData::MoveLeft(bool isMine)
{
	if(isMine && _isP1 || !isMine && !_isP1)
	{
		_widthp1 -= 100;
		if(_widthp1 <= 100)
		{
			_widthp1 = 100;
		}
	}
	else if(isMine && !_isP1 || !isMine && _isP1)
	{
		_widthp2 -= 100;
		if(_widthp2 <= 100)
		{
			_widthp2 = 100;
		}
	}
}
void GUI::GUIData::MoveRight(bool isMine)
{
	if(isMine && _isP1 || !isMine && !_isP1)
	{
		_widthp1 += 100;
		if(_widthp1 >= 800)
		{
			_widthp1 = 800;
		}
	}
	else if(isMine && !_isP1 || !isMine && _isP1)
	{
		_widthp2 += 100;
		if(_widthp2 >= 800)
		{
			_widthp2 = 800;
		}
	}
}*/
void GUI::GUIData::MoveUp(bool isMine)
{
	if(isMine)
	{
		myPaddle._posH += _paddleSpeed;
		if(myPaddle._posH >= _maxHeight)
		{
			myPaddle._posH = _maxHeight;
		}
	}
	else
	{
		theirPaddle._posH += _paddleSpeed;
		if(theirPaddle._posH >= _maxHeight)
		{
			theirPaddle._posH = _maxHeight;
		}
	}
}

void GUI::GUIData::MoveDown(bool isMine)
{
	if(isMine)
	{
		myPaddle._posH -= _paddleSpeed;
		if(myPaddle._posH <= _minHeight)
		{
			myPaddle._posH = _minHeight;
		}
	}
	else
	{
		theirPaddle._posH -=_paddleSpeed;
		if(theirPaddle._posH <= _minHeight)
		{
			theirPaddle._posH = _minHeight;
		}
	}
}

void GUI::newBall()
{
	if(data._hitP1)
	{
		int x = 300;
		int y = 300;
		data._ballW = (float)x;
		data._ballH = (float)y;
		data._ballUp = true;
		data._ballLeft = false;
	}
	else
	{
		int x = 500;
		int y = 300;
		data._ballW = (float)x;
		data._ballH = (float)y;
		data._ballUp = true;
		data._ballLeft = true;
	}
}

/*void GUI::newBall(char cx, char cy)
{
	if(data._hitP1)
	{
		int x = (int)cx;
		int y = (int)cy;
		x += 275;
		y += 275;
		data._ballW = (float)x;
		data._ballH = (float)y;
		data._ballUp = true;
		data._ballLeft = false;
	}
	else
	{
		int x = (int)cx;
		int y = (int)cy;
		int xSend = x;
		int ySend = y;
		x += 525;
		y += 275;
		data._ballW = (float)x;
		data._ballH = (float)y;
		data._ballUp = true;
		data._ballLeft = true;
	}
}*/

void GUI::GUIData::setP1(bool p1)
{
	_isP1 = p1;
}

void GUI::GUIData::setPaddles()
{
	if(_isP1)
	{
		myPaddle = Paddle(100,50,_heightp1,_widthp1, 1.0f,0.0f,0.0f);
		theirPaddle = Paddle(100,50,_heightp2,_widthp2, 0.0f,0.0f,1.0f);
	}
	else
	{
		theirPaddle = Paddle(100,50,_heightp1,_widthp1, 0.0f,0.0f,1.0f);
		myPaddle = Paddle(100,50,_heightp2,_widthp2, 1.0f,0.0f,0.0f);
	}
}